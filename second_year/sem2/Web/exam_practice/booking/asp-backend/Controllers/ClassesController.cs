using asp_backend.Models;
using asp_backend.Models.DTOs;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace asp_backend.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class ClassesController : Controller
    {
        private BookingDbContext _db = new BookingDbContext();

        public ClassesController(BookingDbContext db) => _db = db;

        [HttpGet("bookings/{userId}")]
        public async Task<IActionResult> GetActiveBookings(int userId)
        {
            var activeBookings = await _db.Bookings.Where(b => b.UserId == userId && b.Cancelled == false).ToListAsync();
            return Ok(activeBookings);
        }

        [HttpGet]
        public async Task<IActionResult> GetClasses()
        {
            var response = new List<ClassResponse>();
            var upcomingClasses = await _db.Classes.Where(c => c.ClassDate >= DateTime.Now).ToListAsync();

            foreach(var upcomingClass in upcomingClasses)
            {
                int occupiedSpots = _db.Bookings.Where(b => b.ClassId == upcomingClass.Id && b.Cancelled == false).Count();
                int remainingSpots = upcomingClass.MaxCapacity - occupiedSpots;

                response.Add(new ClassResponse {
                    Id = upcomingClass.Id,
                    ClassName = upcomingClass.ClassName,
                    InstructorName = upcomingClass.InstructorName,
                    ClassDate = upcomingClass.ClassDate,
                    RemainingSpots = remainingSpots
                });
            }

            return Ok(response);
        }

        [HttpGet("intensity/{userId}")]
        public async Task<IActionResult> GetIntensity(int userId)
        {
            var activeBookings = await _db.Bookings
                .Where(b => b.UserId == userId && b.Cancelled == false)
                .ToListAsync();

            var intensities = activeBookings
                .Select(b => _db.Classes.FirstOrDefault(c => c.Id == b.ClassId)?.ClassName)
                .Where(name => name != null)
                .Select(name => name[(name.IndexOf('-') + 1)..])
                .ToList();

            var intensityCounts = new Dictionary<string, int>();
            foreach (var intensity in intensities)
            {
                if (intensityCounts.ContainsKey(intensity))
                    intensityCounts[intensity]++;
                else
                    intensityCounts[intensity] = 1;
            }

            foreach (var kvp in intensityCounts)
            {
                if (kvp.Value >= 3)
                    return Ok($"All your bookings this week are {kvp.Key}-intensity. Consider balancing your workout routine!");
            }

            return Ok("");
        }

        [HttpGet("history/{userId}")]
        public async Task<IActionResult> GetAllBookingsForUser(int userId)
        {
            var bookings = await _db.Bookings.Where(b => b.UserId == userId).ToListAsync();
            var result = bookings.Select(b => new BookingResponse
            {
                ClassName = _db.Classes.FirstOrDefault(c => c.Id == b.ClassId)?.ClassName ?? "",
                Date = b.BookedAt,
                Status = (bool)!b.Cancelled
            }).ToList();

            return Ok(result);
        }

        [HttpPost("{userId}/{classId}")]
        public async Task<IActionResult> Book(int userId, int classId)
        {
            if (BasicMemberOnPremiumClass(userId, classId) == true)
                return Ok("High-Intensity classes are available for Premium members only!");

            if (UserBookedClass(userId, classId) == true)
                return Ok("You've already booked this class!");

            if (NoSpotsAvailable(classId) == true)
            {
                await _db.WaitLists.AddAsync(new WaitList
                {
                    UserId = userId,
                    ClassId = classId,
                    AddedAt = DateTime.Now
                });

                await _db.SaveChangesAsync();
                return Ok("You've been added to the waitlist for " + _db.Classes.FirstOrDefault(c => c.Id == classId).ClassName);
            }

            await _db.Bookings.AddAsync(new Booking { UserId = userId, ClassId = classId, BookedAt = DateTime.Now, Cancelled = false });
            await _db.SaveChangesAsync();
            return Ok("Class was booked!");
        }

        [HttpPost("cancel/{userId}/{classId}")]
        public async Task<IActionResult> CancelBooking(int userId, int classId)
        {
            var booking =  await _db.Bookings.FirstOrDefaultAsync(b => b.ClassId == classId &&  b.UserId == userId);
            if (booking == null) return NotFound("Booking not found!");
            booking.Cancelled = true;
            await _db.SaveChangesAsync();

            var waitListForClass = await _db.WaitLists.Where(wl => wl.ClassId == classId).ToListAsync();
            if (waitListForClass.Count == 0 || waitListForClass == null) return Ok("No user in the wait list");

            waitListForClass.Sort((a, b) => a.AddedAt.CompareTo(b.AddedAt));
            var firstEntry = waitListForClass[0];
            string username = _db.Users.FirstOrDefault(u => u.Id == firstEntry.UserId).Username;

            await _db.Bookings.AddAsync(new Booking {
                UserId = firstEntry.UserId,
                ClassId = firstEntry.ClassId,
                BookedAt = DateTime.Now,
                Cancelled = false
            });

            _db.WaitLists.Remove(firstEntry);
            await _db.SaveChangesAsync();

            return Ok(username + " has been automatically moved from the waitlist to a confirmed booking");
        }

        private bool BasicMemberOnPremiumClass(int userId, int classId)
        {
            string userType = _db.Users.FirstOrDefault(u => u.Id == userId).MembershipType;
            string className = _db.Classes.FirstOrDefault(c => c.Id == classId).ClassName;
            string classIntensity = className[(className.IndexOf('-') + 1)..];

            if (userType.ToLower() == "basic" && classIntensity.ToLower() == "high")
                return true;

            return false;
        }

        private bool NoSpotsAvailable(int classId)
        {
            int occupiedSpots = _db.Bookings.Where(b => b.ClassId == classId && b.Cancelled == false).Count();
            int remainingSpots = _db.Classes.FirstOrDefault(c => c.Id == classId).MaxCapacity - occupiedSpots;

            if (remainingSpots > 0) return false;
            return true;
        }

        private bool UserBookedClass(int userId,  int classId)
        {
            var booking = _db.Bookings.FirstOrDefault(b => b.ClassId == classId && b.UserId == userId && b.Cancelled == false);
            if (booking != null) return true;

            var waitlisted = _db.WaitLists.FirstOrDefault(wl => wl.ClassId == classId && wl.UserId == userId);
            return waitlisted != null;
        }
    }
}
