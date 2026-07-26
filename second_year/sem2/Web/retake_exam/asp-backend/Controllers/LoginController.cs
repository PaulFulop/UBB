using asp_backend.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace asp_backend.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class LoginController : Controller
    {
        private RetakeDbContext _db = new RetakeDbContext();

        public LoginController(RetakeDbContext db) => _db = db;

        [HttpGet("{username}")]
        public async Task<IActionResult> Login(string username)
        {
            var user = await _db.Users.FirstOrDefaultAsync(u => u.Username == username);
            if (user == null) return NotFound("User not found!");
            return Ok(user);
        }

        [HttpGet("activecount")]
        public async Task<IActionResult> GetActiveUserCount()
        {
            var cutoff = DateTime.Now.AddSeconds(-60);
            var count = await _db.Users.CountAsync(u => u.LastSeen >= cutoff);
            return Ok(count);
        }

        [HttpPost("heartbeat/{userId}")]
        public async Task<IActionResult> Heartbeat(int userId)
        {
            var user = await _db.Users.FindAsync(userId);
            if (user != null)
            {
                user.LastSeen = DateTime.Now;
                await _db.SaveChangesAsync();
            }
            return Ok();
        }
    }
}
