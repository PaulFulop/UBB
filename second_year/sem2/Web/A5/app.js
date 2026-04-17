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

async function apiJson(url, options = {}) {
  const response = await fetch(url, {
    headers: {
      "Content-Type": "application/json",
      ...(options.headers || {}),
    },
    ...options,
  });

  const payload = await response.json().catch(() => ({}));
  if (!response.ok) {
    throw new Error(payload.error || "Request failed.");
  }

  return payload;
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

function readRecipeForm(form) {
  return {
    author: form.author.value.trim(),
    name: form.name.value.trim(),
    type: form.type.value.trim(),
    recipe: form.recipe.value.trim(),
  };
}

function initAddPage() {
  const form = document.getElementById("recipe-create-form");
  const message = document.getElementById("create-message");

  if (!form || !message) {
    return;
  }

  form.addEventListener("submit", async (event) => {
    event.preventDefault();

    try {
      setMessage(message, "Saving recipe...");

      const payload = readRecipeForm(form);
      const data = await apiJson("api.php?action=create", {
        method: "POST",
        body: JSON.stringify(payload),
      });

      form.reset();
      setMessage(message, data.message || "Recipe added successfully.");
    } catch (error) {
      setMessage(message, error.message, true);
    }
  });
}

async function loadAllRecipes() {
  return fetchRecipes("all");
}

function renderManageRows(recipes, recipesBody) {
  if (recipes.length === 0) {
    recipesBody.innerHTML = '<tr><td colspan="5">No recipes found.</td></tr>';
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
        <td class="actions">
          <a class="button-link" href="edit.html?id=${encodeURIComponent(recipe.id)}">Edit</a>
          <button type="button" class="danger js-delete-recipe" data-recipe-id="${escapeHtml(String(recipe.id))}">Delete</button>
        </td>
      </tr>`,
    )
    .join("");
}

function initManagePage() {
  const recipesBody = document.getElementById("manage-recipes-body");
  const manageMessage = document.getElementById("manage-message");
  const refreshBtn = document.getElementById("manage-refresh-btn");

  if (!recipesBody || !manageMessage || !refreshBtn) {
    return;
  }

  async function refreshRecipes() {
    const recipes = await loadAllRecipes();
    renderManageRows(recipes, recipesBody);

    recipesBody.querySelectorAll(".js-delete-recipe").forEach((button) => {
      button.addEventListener("click", async () => {
        const recipeId = button.getAttribute("data-recipe-id");
        if (!recipeId) {
          return;
        }

        const ok = window.confirm(
          "Delete this recipe? This action cannot be undone.",
        );
        if (!ok) {
          return;
        }

        try {
          setMessage(manageMessage, "Deleting recipe...");
          await apiJson(
            `api.php?action=delete&id=${encodeURIComponent(recipeId)}`,
            {
              method: "DELETE",
            },
          );
          await refreshRecipes();
          setMessage(manageMessage, "Recipe deleted successfully.");
        } catch (error) {
          setMessage(manageMessage, error.message, true);
        }
      });
    });
  }

  refreshBtn.addEventListener("click", async () => {
    try {
      setMessage(manageMessage, "Loading recipes...");
      await refreshRecipes();
      setMessage(manageMessage, "Recipes loaded.");
    } catch (error) {
      setMessage(manageMessage, error.message, true);
    }
  });

  (async function init() {
    try {
      await refreshRecipes();
    } catch (error) {
      setMessage(manageMessage, error.message, true);
    }
  })();
}

function getRecipeIdFromUrl() {
  const params = new URLSearchParams(window.location.search);
  const id = Number(params.get("id"));
  return Number.isInteger(id) && id > 0 ? id : null;
}

async function loadRecipeForEdit(recipeId) {
  const recipes = await loadAllRecipes();
  return recipes.find((recipe) => Number(recipe.id) === recipeId) || null;
}

function initEditPage() {
  const form = document.getElementById("recipe-edit-form");
  const message = document.getElementById("edit-message");
  const formShell = document.getElementById("edit-form-shell");
  const recipeId = getRecipeIdFromUrl();

  if (!form || !message || !formShell) {
    return;
  }

  if (!recipeId) {
    setMessage(message, "No valid recipe selected.", true);
    formShell.classList.add("hidden");
    return;
  }

  form.addEventListener("submit", async (event) => {
    event.preventDefault();

    try {
      setMessage(message, "Updating recipe...");

      const payload = readRecipeForm(form);
      const data = await apiJson(
        `api.php?action=update&id=${encodeURIComponent(recipeId)}`,
        {
          method: "PUT",
          body: JSON.stringify(payload),
        },
      );

      setMessage(message, data.message || "Recipe updated successfully.");
    } catch (error) {
      setMessage(message, error.message, true);
    }
  });

  (async function init() {
    try {
      setMessage(message, "Loading recipe...");
      const recipe = await loadRecipeForEdit(recipeId);

      if (!recipe) {
        setMessage(message, "Recipe not found.", true);
        formShell.classList.add("hidden");
        return;
      }

      form.name.value = recipe.name;
      form.author.value = recipe.author;
      form.type.value = recipe.type;
      form.recipe.value = recipe.recipe;
      setMessage(message, "Recipe loaded.");
      formShell.classList.remove("hidden");
    } catch (error) {
      setMessage(message, error.message, true);
      formShell.classList.add("hidden");
    }
  })();
}

initBrowsePage();
initAddPage();
initManagePage();
initEditPage();
