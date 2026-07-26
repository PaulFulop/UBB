using backend_asp.Models;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class LoginController : Controller
    {
        private GymDbContext _db = new GymDbContext();
        public LoginController(GymDbContext db)
        {
            _db = db;
        }


        [HttpGet("{username}")]
        public async Task<IActionResult> Login(string username)
        {
            var user = await _db.Users.FirstOrDefaultAsync(u => u.Username == username);
            if (user == null) return NotFound("user not found");

            var sessions = await _db.Sessions.Where(s => s.UserId == user.Id).ToListAsync();
            var moveIds = sessions.Select(s => s.MoveId).Distinct().ToList();
            var moves = await _db.Moves.Where(m => moveIds.Contains(m.Id)).ToListAsync();

            var scores = new Dictionary<string, double>();

            // initialize all muscle groups to a baseline (spec doesn't specify, 50 is reasonable middle ground)
            var allGroups = await _db.Moves.Select(m => m.Musclegroup).Distinct().ToListAsync();
            foreach (var group in allGroups)
                scores[group] = 50;

            foreach (var session in sessions)
            {
                var move = moves.FirstOrDefault(m => m.Id == session.MoveId);
                if (move == null) continue;

                if (session.Completed == true)
                    scores[move.Musclegroup] += 10;
                else
                    scores[move.Musclegroup] -= scores[move.Musclegroup] * 0.08;

                scores[move.Musclegroup] = Math.Clamp(scores[move.Musclegroup], 0, 100);
            }

            return Ok(new { user, scores });
        }
    }
}
