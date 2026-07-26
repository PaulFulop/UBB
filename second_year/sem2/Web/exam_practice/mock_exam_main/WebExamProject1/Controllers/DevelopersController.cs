using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using WebExamProject1.Models;

namespace WebExamProject1.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class DevelopersController : ControllerBase
    {
        private WebExam1Context _db = new WebExam1Context();
        public DevelopersController(WebExam1Context db) => _db = db;

        [HttpGet]
        public async Task<IActionResult> GetDevelopers()
        {
            var developers = await _db.SoftwareDevelopers.ToListAsync();
            return Ok(developers);
        }
    }
}
