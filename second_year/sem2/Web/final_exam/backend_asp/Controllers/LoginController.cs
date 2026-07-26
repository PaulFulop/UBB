using backend_asp.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class LoginController : Controller
    {
        public ExamDbContext _db = new ExamDbContext();
        public LoginController(ExamDbContext db) => _db = db;

        [HttpGet("{username}")]
        public async Task<IActionResult> Login(string username)
        {
            var user = await _db.Users.Where(u => u.Username == username).FirstOrDefaultAsync();

            if (user == null) return NotFound("User not found");

            return Ok(user);
        }
    }
}
