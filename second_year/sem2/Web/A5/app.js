function escapeHtml(value) {
  return String(value)
    .replace(/&/g, "&amp;")
    .replace(/</g, "&lt;")
    .replace(/>/g, "&gt;")
    .replace(/\"/g, "&quot;")
    .replace(/'/g, "&#039;");
}

function setMessage(element, text, isError = false) {
  if (!element) {
    return;
  }

  element.textContent = text;
  element.classList.toggle("error", isError);
}

async function fetchTypes() {
  const response = await fetch("api.php?action=types");
  if (!response.ok) {
    throw new Error("Could not load recipe types.");
  }

  const data = await response.json();
  return data.types || [];
}

async function fetchRecipes(typeValue) {
  const response = await fetch(
    `api.php?action=list&type=${encodeURIComponent(typeValue)}`,
  );

  if (!response.ok) {
    throw new Error("Could not load recipes.");
  }

  const data = await response.json();
  return data.recipes || [];
}

function initBrowsePage() {
  const typeFilter = document.getElementById("type-filter");
  const browseBtn = document.getElementById("browse-btn");
  const previousFilterValue = document.getElementById("previous-filter-value");
  const recipesBody = document.getElementById("browse-recipes-body");
  const browseMessage = document.getElementById("browse-message");

  if (!typeFilter || !browseBtn || !previousFilterValue || !recipesBody) {
    return;
  }

  let lastAppliedFilter = localStorage.getItem("lastRecipeFilter") || "none";

  function renderPreviousFilter() {
    previousFilterValue.textContent = lastAppliedFilter;
  }

  function renderRecipes(recipes) {
    if (recipes.length === 0) {
      recipesBody.innerHTML =
        '<tr><td colspan="4">No recipes found for this filter.</td></tr>';
      return;
    }

    recipesBody.innerHTML = recipes
      .map(
        (recipe) => `
      <tr>
        <td>${escapeHtml(recipe.name)}</td>
        <td>${escapeHtml(recipe.author)}</td>
        <td>${escapeHtml(recipe.type)}</td>
        <td>${escapeHtml(recipe.recipe)}</td>
      </tr>`,
      )
      .join("");
  }

  async function refreshTypeFilter() {
    const types = await fetchTypes();
    const selectedBeforeRefresh = typeFilter.value || "all";

    typeFilter.innerHTML = '<option value="all">all</option>';
    for (const type of types) {
      const option = document.createElement("option");
      option.value = type;
      option.textContent = type;
      typeFilter.append(option);
    }

    if (["all", ...types].includes(selectedBeforeRefresh)) {
      typeFilter.value = selectedBeforeRefresh;
    }
  }

  async function browseRecipes() {
    const selectedType = typeFilter.value || "all";
    const recipes = await fetchRecipes(selectedType);
    renderRecipes(recipes);

    lastAppliedFilter = selectedType;
    localStorage.setItem("lastRecipeFilter", lastAppliedFilter);
    renderPreviousFilter();

    setMessage(
      browseMessage,
      `Loaded ${recipes.length} recipe(s) for filter: ${selectedType}`,
    );
  }

  browseBtn.addEventListener("click", async () => {
    try {
      setMessage(browseMessage, "Loading recipes...");
      await browseRecipes();
    } catch (error) {
      setMessage(browseMessage, error.message, true);
    }
  });

  (async function init() {
    try {
      renderPreviousFilter();
      await refreshTypeFilter();
      await browseRecipes();
    } catch (error) {
      setMessage(browseMessage, error.message, true);
    }
  })();
}

function initDeleteConfirm() {
  const deleteForms = document.querySelectorAll(".js-delete-form");
  if (deleteForms.length === 0) {
    return;
  }

  for (const form of deleteForms) {
    form.addEventListener("submit", (event) => {
      const ok = window.confirm(
        "Delete this recipe? This action cannot be undone.",
      );
      if (!ok) {
        event.preventDefault();
      }
    });
  }
}

function initCancelConfirm() {
  const cancelLink = document.querySelector(".js-cancel-link");
  if (!cancelLink) {
    return;
  }

  cancelLink.addEventListener("click", (event) => {
    const ok = window.confirm("Cancel editing and discard unsaved changes?");
    if (!ok) {
      event.preventDefault();
    }
  });
}

initBrowsePage();
initDeleteConfirm();
initCancelConfirm();
