using asp_backend.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace asp_backend.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class LoginController : Controller
    {
        private BookingDbContext _db = new BookingDbContext();

        public LoginController(BookingDbContext db) => _db = db;

        [HttpGet("{username}")]
        public async Task<IActionResult> Login(string username)
        {
            var user = await _db.Users.FirstOrDefaultAsync(u  => u.Username == username);
            if (user == null) return NotFound("User not found!");
            return Ok(user);
        }
    }
}
