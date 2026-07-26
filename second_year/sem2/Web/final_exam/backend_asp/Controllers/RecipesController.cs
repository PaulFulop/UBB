using backend_asp.Models;
using backend_asp.Models.DTOs;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.TagHelpers;
using Microsoft.EntityFrameworkCore;
using System.Reflection;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class RecipesController : Controller
    {
        public ExamDbContext _db = new ExamDbContext();
        public RecipesController(ExamDbContext db) => _db = db;

        [HttpGet]
        public async Task<IActionResult> GetRecipes()
        {
            var recipes = await _db.Recipes.ToListAsync();
            return Ok(recipes);
        }

        [HttpPost]
        public async Task<IActionResult> AddRecipe([FromBody] RecipeDTO request)
        {
            var newRecipe = new Recipe();
            newRecipe.Title = request.Title;
            newRecipe.UserId = request.UserId;
            newRecipe.TotalCalories = request.TotalCalories;

            await _db.Recipes.AddAsync(newRecipe);
            await _db.SaveChangesAsync();

            foreach (var rs in request.RecipeSteps)
            {
                var newRecipeStep = new RecipeStep();
                newRecipeStep.StepNumber = rs.StepNumber;
                newRecipeStep.IngredientIds = rs.IngredientIds;
                newRecipeStep.Description = rs.Description;
                newRecipeStep.RecipeId = newRecipe.Id;

                await _db.RecipeSteps.AddAsync(newRecipeStep);
            }


            await _db.SaveChangesAsync();
            return Ok("Recipe added");
        }

        [HttpGet("steps/{recipeId}")]
        public async Task<IActionResult> GetRecipeStepsForRecipe(int recipeId)
        {
            var recipeSteps = await _db.RecipeSteps.Where(rs => rs.RecipeId == recipeId).ToListAsync();
            return Ok(recipeSteps);
        }

        [HttpDelete("{recipeId}")]
        public async Task<IActionResult> DeleteRecipe(int recipeId)
        {
            var recipe = await _db.Recipes.Where(r => r.Id == recipeId).FirstOrDefaultAsync();
            if (recipe == null) return NotFound("Recipe not found");
            _db.Recipes.Remove(recipe);

            var recipeSteps = await _db.RecipeSteps.Where(rs => rs.RecipeId == recipeId).ToListAsync();
            foreach (var rs in recipeSteps)
                _db.RecipeSteps.Remove(rs);

            await _db.SaveChangesAsync();
            return Ok("Recipe deleted");
        }

        [HttpPost("calories/proportion")]
        public async Task<IActionResult> GetHeavilyInfluencedRecipe ([FromBody]List<RecipeStepDTO> recipeSteps)
        {
            Dictionary<String, int> recipeCategoryCounts = new();

            foreach (var rs in recipeSteps)
            {
                var ingredientIds = rs.IngredientIds.Split(",");
                foreach (var ingredientId in ingredientIds)
                {
                    int id = int.Parse(ingredientId.Trim());
                    var ingredient = await _db.Ingredients.FirstOrDefaultAsync(i => i.Id == id);
                    if (ingredient == null) continue;

                    var name = ingredient.Name;
                    if (name.Contains('-') == false)
                        continue;
                    var category = name.Substring(0, name.IndexOf('-')).Trim().ToUpper();
                    if (recipeCategoryCounts.ContainsKey(category))
                        ++recipeCategoryCounts[category];
                    else
                        recipeCategoryCounts[category] = 1;
                }

            }

            int totalIngredientUsages = 0;
            foreach (var recipeCategoryCountValue in recipeCategoryCounts.Values)
                totalIngredientUsages += recipeCategoryCountValue;

            foreach (var recipeCategoryCount in recipeCategoryCounts)
                if (recipeCategoryCount.Value > 0.6 * totalIngredientUsages)
                    return Ok(recipeCategoryCount.Key);

            return Ok("none");
        }
    }
}
