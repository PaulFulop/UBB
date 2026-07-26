using backend_asp.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class ReservationsController : Controller
    {
        public HotelDbContext _db = new HotelDbContext();
        public ReservationsController(HotelDbContext db) => _db = db;

        [HttpGet("{userId}")]
        public async Task<IActionResult> GetAllReservationsForUser(int userId)
        {
            var reservationsForUser = await _db.Reservations.Where(r => r.UserId == userId).ToListAsync();
            if (reservationsForUser == null) return NotFound("User not found"); 
            return Ok(reservationsForUser);
        }
    }
}
