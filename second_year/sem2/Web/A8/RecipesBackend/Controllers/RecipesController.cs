using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using RecipesBackend.Models;
using System.Text.Json;

namespace RecipesBackend.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class RecipesController : ControllerBase
    {
        private AppDbContext _context;
        public RecipesController(AppDbContext appDbContext)
        {
            _context = appDbContext;
        }

        [HttpGet("types")]
        public async Task<IActionResult> GetTypes()
        {
            var types = await _context.Recipes.Select(r => r.Type).Distinct().ToListAsync();
            return Ok(new { types = types });
        }

        [HttpGet]
        public async Task<IActionResult> GetRecipesOfType([FromQuery] string type)
        {
            if (string.IsNullOrEmpty(type))
                return BadRequest("Type query parameter is required");

            if (type == "all")
            {
                var allRecipes = await _context.Recipes.ToListAsync();
                return Ok(new {recipes = allRecipes});
            }

            var recipes = await _context.Recipes.Where(r => r.Type == type).ToListAsync();
            return Ok(new { recipes = recipes });
        }

        [HttpPost]
        public async Task<IActionResult> CreateRecipe(JsonElement body)
        {
            var author = body.GetProperty("author").GetString();
            var name = body.GetProperty("name").GetString();
            var type = body.GetProperty("type").GetString();
            var recipe = body.GetProperty("recipe").GetString();

            if (string.IsNullOrEmpty(author) || string.IsNullOrEmpty(name) || string.IsNullOrEmpty(type) || string.IsNullOrEmpty(recipe))
                return BadRequest(new { message = "Author, name, type, and recipe are required" });

            await _context.Recipes.AddAsync(new Recipe
            {
                Author = author,
                Name = name,
                Type = type,
                RecipeDescription = recipe
            });
            await _context.SaveChangesAsync();
            return Ok(new { message = "Recipe created successfully" });
        }

        [HttpPut("{id}")]
        public async Task<IActionResult> UpdateRecipe(int id, JsonElement body)
        {
            var recipe = await _context.Recipes.FindAsync(id);
            if (recipe == null) return NotFound();

            var author = body.GetProperty("author").GetString();
            if(string.IsNullOrEmpty(author)) return BadRequest(new { message = "Author is required" });

            var name = body.GetProperty("name").GetString();
            if (string.IsNullOrEmpty(name)) return BadRequest(new { message = "Name is required" });
            
            var type = body.GetProperty("type").GetString();
            if(string.IsNullOrEmpty(type)) return BadRequest(new { message = "Type is required" });

            var recipeDescription = body.GetProperty("recipe").GetString();
            if (string.IsNullOrEmpty(recipeDescription)) return BadRequest(new { message = "Recipe description is required" });

            recipe.Author = author;
            recipe.Name = name;
            recipe.Type = type;
            recipe.RecipeDescription = recipeDescription;

            await _context.SaveChangesAsync();
            return Ok(new { message = "Recipe updated successfully" });
        }

        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteRecipe(int id)
        {
            var recipe = await _context.Recipes.FindAsync(id);
            if (recipe == null) return NotFound();

            _context.Recipes.Remove(recipe);
            await _context.SaveChangesAsync();

            return NoContent();
        }
    }
}
