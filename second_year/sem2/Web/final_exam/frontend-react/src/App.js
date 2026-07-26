import "./App.css";
import { useState, useEffect } from "react";
import { BrowserRouter, Routes, Route, useNavigate } from "react-router-dom";

const API = "https://localhost:7145";

function App() {
  const [userId, setUserId] = useState(0);
  const [loggedIn, setLoggedIn] = useState(false);
  const [calorieCount, setCalorieCount] = useState(0);
  const [steps, setSteps] = useState([]);
  const [recipeTitle, setRecipeTitle] = useState("");
  const [allIngredients, setAllIngredients] = useState([]);

  useEffect(() => {
    if (recipeTitle || steps.length > 0) {
      localStorage.setItem(
        "unfinishedRecipe",
        JSON.stringify({
          recipeTitle,
          steps,
          calorieCount,
        }),
      );
    }
  }, [recipeTitle, steps, calorieCount]);

  return (
    <BrowserRouter>
      <Routes>
        <Route
          path="/"
          element={
            <LoginPage
              setUserId={setUserId}
              setLoggedIn={setLoggedIn}
              setRecipeTitle={setRecipeTitle}
              setSteps={setSteps}
              setCalorieCount={setCalorieCount}
            />
          }
        />
        <Route
          path="/RecipeTitle"
          element={
            <RecipeTitlePage
              recipeTitle={recipeTitle}
              setRecipeTitle={setRecipeTitle}
            />
          }
        />
        <Route
          path="/StepBuilder"
          element={
            <StepBuilderPage
              allIngredients={allIngredients}
              setAllIngredients={setAllIngredients}
              calorieCount={calorieCount}
              setCalorieCount={setCalorieCount}
              recipeTitle={recipeTitle}
              loggedIn={loggedIn}
              setSteps={setSteps}
              steps={steps}
              userId={userId}
            />
          }
        />
        <Route
          path="/Review"
          element={
            <ReveiwPage
              userId={userId}
              recipeTitle={recipeTitle}
              steps={steps}
              setSteps={setSteps}
              allIngredients={allIngredients}
              calorieCount={calorieCount}
            />
          }
        />
        <Route path="/Recipes" element={<RecipesPage />} />
      </Routes>
    </BrowserRouter>
  );
}

function RecipesPage() {
  const [recipes, setRecipes] = useState([]);
  const navigate = useNavigate();

  useEffect(() => {
    fetch(`${API}/recipes`)
      .then((r) => r.json())
      .then((data) => setRecipes(data));
  }, [recipes]);

  function deleteRecipe(recipeId) {
    fetch(`${API}/recipes/${recipeId}`, {
      method: "DELETE",
      headers: { "Content-Type": "application/json" },
    })
      .then((r) => r.json())
      .then((data) => {
        alert("Recipe removed!");
      });
  }

  return (
    <div className="container">
      <h1> ALL RECIPES </h1>
      <br></br>
      <table>
        <thead>
          <tr>
            <th>Title</th>
            <th>Total Calories</th>
          </tr>
        </thead>
        <tbody>
          {recipes.map((r) => (
            <tr key={r.id}>
              <td>{r.title}</td>
              <td>{r.totalCalories}</td>
              <td>
                <button onClick={() => deleteRecipe(r.id)}>
                  Remove Recipe
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
      <br></br>
      <button onClick={() => navigate("/Review")}>Go Back</button>
    </div>
  );
}

function LoginPage({
  setUserId,
  setLoggedIn,
  setRecipeTitle,
  setSteps,
  setCalorieCount,
}) {
  const [username, setUsername] = useState("");
  const [error, setError] = useState("");
  const [unfinished, setUnfinished] = useState(null);
  const navigate = useNavigate();

  useEffect(() => {
    const saved = localStorage.getItem("unfinishedRecipe");
    if (saved) {
      setUnfinished(JSON.parse(saved));
    }
  }, []);

  function login() {
    if (username === "") {
      setError("Type a username first");
      return;
    }

    setError("");
    fetch(`${API}/login/${username}`)
      .then((r) => r.json())
      .then((user) => {
        setUserId(user.id);
        setLoggedIn(true);

        if (unfinished) {
          const confirmContinue = window.confirm(
            `You have an unfinished recipe "${unfinished.recipeTitle}". Would you like to continue?`,
          );

          if (confirmContinue) {
            setCalorieCount(unfinished.calorieCount);
            setSteps(unfinished.steps);
            setRecipeTitle(unfinished.recipeTitle);
            navigate("/StepBuilder");
            return;
          } else {
            localStorage.removeItem("unfinishedRecipe");
          }
        }

        navigate("/RecipeTitle");
      })
      .catch((err) => setError(err.message));
  }

  return (
    <div className="container">
      <h2>Enter your name</h2>
      <input value={username} onChange={(e) => setUsername(e.target.value)} />
      <button onClick={login}>Enter</button>

      {error && (
        <p className="error" color="red">
          {error}
        </p>
      )}
    </div>
  );
}

function RecipeTitlePage({ recipeTitle, setRecipeTitle }) {
  const navigate = useNavigate();

  return (
    <div className="container">
      <h2>Enter recipe title: </h2>
      <input
        value={recipeTitle}
        onChange={(e) => setRecipeTitle(e.target.value)}
      />
      <button onClick={() => navigate("/StepBuilder")}>Next</button>
    </div>
  );
}

function StepBuilderPage({
  allIngredients,
  setAllIngredients,
  calorieCount,
  setCalorieCount,
  recipeTitle,
  loggedIn,
  setSteps,
  steps,
  userId,
}) {
  const [description, setDescription] = useState("");
  const [stepNumber, setStepNumber] = useState(1);
  const [ingredientIds, setIngredientIds] = useState("");
  const navigate = useNavigate();

  useEffect(() => {
    if (!loggedIn) navigate("/");

    fetch(`${API}/ingredients`)
      .then((r) => r.json())
      .then((data) => setAllIngredients(data))
      .catch((err) => console.error(err));
  }, [loggedIn]);

  function addStep() {
    setSteps((prev) => [
      ...prev,
      {
        stepNumber: stepNumber,
        description: description,
        ingredientIds: ingredientIds,
      },
    ]);
    setDescription("");
    setIngredientIds("");
    setStepNumber(stepNumber + 1);
  }

  function addIngredient(ingredentId, calories) {
    setIngredientIds((prev) =>
      prev ? `${prev},${ingredentId}` : `${ingredentId}`,
    );
    setCalorieCount(calorieCount + calories);
  }

  function removeStep(id) {
    const newList = steps.filter((step) => step.stepNumber !== id);

    newList.forEach((element) => {
      if (element.stepNumber > id) element.stepNumber -= 1;
    });
    setStepNumber(stepNumber - 1);

    setSteps(newList);
  }

  return (
    <div className="container">
      <h1> RECIPE TITLE: {recipeTitle}</h1>
      <h1>Description: </h1>
      <input
        value={description}
        onChange={(e) => setDescription(e.target.value)}
      ></input>
      <h1>Ingredients: </h1>
      <table>
        <thead>
          <tr>
            <th>Name</th>
            <th>Unit</th>
            <th>Calories</th>
          </tr>
        </thead>
        <tbody>
          {allIngredients.map((i) => (
            <tr key={i.id}>
              <td>{i.name}</td>
              <td>{i.unit}</td>
              <td>{i.caloriesPer100g}</td>
              <td>
                <button onClick={() => addIngredient(i.id, i.caloriesPer100g)}>
                  Select
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
      <button onClick={() => addStep(description, ingredientIds)}>
        Add Step
      </button>
      <br></br>
      <h1>Steps: </h1>
      <table>
        <thead>
          <tr>
            <th>Step Number</th>
            <th>Description</th>
            <th>Ingredient Id's</th>
          </tr>
        </thead>
        <tbody>
          {steps.map((s) => (
            <tr key={s.stepNumber}>
              <td>{s.stepNumber}</td>
              <td>{s.description}</td>
              <td>{s.ingredientIds}</td>
              <td>
                <button onClick={() => removeStep(s.stepNumber)}>Remove</button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
      <br></br>
      <button onClick={() => navigate("/Review")}>Finish Building</button>
    </div>
  );
}

function ReveiwPage({
  userId,
  recipeTitle,
  steps,
  setSteps,
  allIngredients,
  calorieCount,
}) {
  const [proportion, setProportion] = useState("");
  const navigate = useNavigate();

  useEffect(() => {
    fetch(`${API}/recipes/calories/proportion`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(steps),
    })
      .then((r) => r.text())
      .then((data) => {
        setProportion(`This recipe is heavily ${data}-based`);
      });
  }, []);

  function addRecipe() {
    fetch(`${API}/recipes`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        userId: userId,
        title: recipeTitle,
        totalCalories: calorieCount,
        recipeSteps: steps,
      }),
    })
      .then((r) => r.text())
      .then((data) => {
        localStorage.removeItem("unfinishedRecipe");
        alert("Recipe added!");
      });
  }

  return (
    <div className="container">
      <h1> RECIPE TITLE: {recipeTitle}</h1>
      <h1> STEPS: </h1>
      <table>
        <thead>
          <tr>
            <th>Description</th>
            <th>Ingredient Id's</th>
          </tr>
        </thead>
        <tbody>
          {steps.map((s) => (
            <tr key={s.stepNumber}>
              <td>{s.description}</td>
              <td>{s.ingredientIds}</td>
            </tr>
          ))}
        </tbody>
      </table>
      <h2>Total calories: {calorieCount}</h2>
      <h2>{proportion}</h2>
      <button onClick={addRecipe}>Add Recipe</button>
      <button
        onClick={() => {
          navigate("/RecipeTitle");
          setSteps([]);
          localStorage.removeItem("unfinishedRecipe");
        }}
      >
        Discard
      </button>
      <br></br>
      <button onClick={() => navigate("/Recipes")}>See all recipes</button>
    </div>
  );
}

export default App;
