using backend_asp.Models;
using backend_asp.Models.DTOs;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class RoomsController : Controller
    {
        public HotelDbContext _db = new HotelDbContext();
        public RoomsController(HotelDbContext db) => _db = db;

        [HttpPost]
        public async Task<IActionResult> GetRooms([FromBody] DateIntervalDTO request)
        {
            var reservationsInInterval = _db.Reservations
                .Where(r => r.CheckInDate >= request.EarliestDate
                && r.CheckOutDate <= request.LatestDate);

            var freeRoomsInInterval = await _db.HotelRooms.Where(h => reservationsInInterval.Count(r => r.RoomId == h.Id) == 0).ToListAsync();
            int totalGuests = 0;

            foreach (var reservation in reservationsInInterval)
                totalGuests += reservation.NumberOfGuests;

            var result = new { freeRooms = freeRoomsInInterval, totalGuests };
            return Ok(result);
        }

        [HttpPost("reserve")]
        public async Task<IActionResult> ReserveRoom([FromBody]ReserveRoomDTO request)
        {
            var reservationsForUser = _db.Reservations.Where(r => r.UserId == request.UserId);

            if (reservationsForUser
                .Any(r => r.CheckInDate < request.LatestDate && r.CheckOutDate > request.EarliestDate))
                return BadRequest("Overlapping reservation");

            var room = await _db.HotelRooms.FindAsync(request.RoomId);
            if (room == null) return NotFound("Room not found");

            int totalPrice = GetTotalReservationPriceForInterval(room.BasePrice, request.EarliestDate, request.LatestDate);
            await _db.Reservations.AddAsync(new Reservation
            {
                UserId = request.UserId,
                RoomId = request.RoomId,
                CheckInDate = request.EarliestDate,
                CheckOutDate = request.LatestDate,
                NumberOfGuests = request.NumberOfGuests,
                TotalPrice = totalPrice
            });
            await _db.SaveChangesAsync();
            return Ok("Room has been reserved");
        }

        int GetTotalReservationPriceForInterval(int basePrice, DateTime earliest, DateTime latest)
        {
            int totalRooms = _db.HotelRooms.Count();
            int bookedRooms = totalRooms - GetAvailableRoomsForInterval(earliest, latest);

            if (bookedRooms <= totalRooms / 2)
                return basePrice;
            else if (bookedRooms > totalRooms / 2 && bookedRooms <= 4 * totalRooms / 5)
                return basePrice + basePrice / 5;

            return basePrice + basePrice / 2;
        }

        int GetAvailableRoomsForInterval(DateTime earliest, DateTime latest)
        {
            return _db.Reservations
                .Where(r => r.CheckInDate >= earliest && r.CheckOutDate <= latest)
                .Count();
        }
    }
}