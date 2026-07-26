using backend_asp.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class LoginController : Controller
    {
        public ShopDbContext _db = new ShopDbContext();
        public LoginController(ShopDbContext db) => _db = db;

        [HttpGet("{username}")]
        public async Task<IActionResult> Login(string username)
        {
            var user = await _db.Users.FirstOrDefaultAsync(u => u.Username == username);
            if (user == null) return NotFound("User not found");

            return Ok(user);
        }
    }
}
