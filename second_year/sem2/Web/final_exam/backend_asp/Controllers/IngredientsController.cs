using backend_asp.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class IngredientsController : Controller
    {
        public ExamDbContext _db = new ExamDbContext();
        public IngredientsController(ExamDbContext db) => _db = db;

        [HttpGet]
        public async Task<IActionResult> GetAllIngredients()
        {
            var ingredients = await _db.Ingredients.ToListAsync();
            return Ok(ingredients);
        }
    }
}
