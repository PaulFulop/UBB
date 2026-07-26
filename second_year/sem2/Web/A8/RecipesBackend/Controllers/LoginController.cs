using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using RecipesBackend.Models;
using System.Text.Json;

namespace RecipesBackend.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class LoginController : ControllerBase
    {
        private AppDbContext _context;

        public LoginController(AppDbContext context)
        {
            _context = context;
        }

        [HttpPost]
        public async Task<IActionResult> Login([FromBody] JsonElement body)
        {
            var username = body.GetProperty("username").GetString();
            var password = body.GetProperty("password").GetString();

            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
                return BadRequest(new { message = "Username and password are required" });

            var user = await _context.Users.FirstOrDefaultAsync(u => u.Username == username && u.Password == password);
            if (user == null)
                return Unauthorized(new { message = "Invalid username or password" });

            return Ok(new { message = "Login successful" });
        }
    }
}
