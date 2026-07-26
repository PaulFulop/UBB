using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using TodoApp.Models;

namespace TodoApp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class LoginController : Controller
    {
        public TaskManagementContext _db = new TaskManagementContext();
        public LoginController(TaskManagementContext db) => _db = db;

        [HttpGet("{name}")]
        public async Task<IActionResult> Login(string name)
        {
            var user = await _db.Users.FirstOrDefaultAsync(u => u.Username == name);
            if (user == null) return NotFound("User not found");
            return Ok(user);
        }
    }
}
