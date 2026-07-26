using backend_asp.Models;
using backend_asp.Models.DTOs;
using Microsoft.AspNetCore.Mvc;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class LoginController : Controller
    {
        public HotelDbContext _db = new HotelDbContext();
        public LoginController(HotelDbContext db) => _db = db;

        [HttpPost]
        public async Task<IActionResult> Login([FromBody] LoginDTO request)
        {
            var user = _db.Users.Where(u => u.Username == request.Username && u.Password == request.Password).FirstOrDefault();

            if (user == null) return NotFound("User not found");
            return Ok(user);
        }
    }
}
