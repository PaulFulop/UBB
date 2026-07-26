using Microsoft.AspNetCore.Mvc;
using RecipesBackend.Models;
using System.Text.Json;

namespace RecipesBackend.Controllers
{
    [Route("[controller]")]
    [ApiController]
    public class RegisterController : ControllerBase
    {
        private AppDbContext _context;

        public RegisterController(AppDbContext context)
        {
            _context = context;
        }

        [HttpPost]
        public async Task<IActionResult> Register([FromBody] JsonElement body)
        {
            var username = body.GetProperty("username").GetString();
            var password = body.GetProperty("password").GetString();

            if (string.IsNullOrEmpty(username) || string.IsNullOrEmpty(password))
                return BadRequest("Username and password are required");

            await _context.Users.AddAsync(new User { Username = username, Password = password });
            await _context.SaveChangesAsync();

            return Ok(new { message = "Account created!" });
        }
    }
}
