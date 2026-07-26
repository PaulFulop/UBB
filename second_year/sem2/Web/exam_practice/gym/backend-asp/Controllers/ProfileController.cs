using backend_asp.Models;
using backend_asp.Models.DTOs;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;

namespace backend_asp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class ProfileController : Controller
    {
        private GymDbContext _db = new GymDbContext();
        public ProfileController(GymDbContext db)
        {
            _db = db;
        }

        [HttpGet("sessions/{userId}")]
        public async Task<IActionResult> GetAllSessions(int userId)
        {
            var sessions = await _db.Sessions
                .Where(s => s.UserId == userId)
                .ToListAsync();

            var moveIds = sessions.Select(s => s.MoveId).Distinct().ToList();
            var moves = await _db.Moves.Where(m => moveIds.Contains(m.Id)).ToListAsync();

            var result = sessions.Select(s => new
            {
                MoveName = moves.FirstOrDefault(m => m.Id == s.MoveId)?.Name,
                Outcome = s.Completed == true ? "completed" : "skipped"
            });

            return Ok(result);
        }

        [HttpPost("bestmove/{userId}")]
        public async Task<IActionResult> GetBestMove(int userId, [FromBody] Dictionary<string, double> perGroupScores)
        {
            var attemptedMoveIds = await _db.Sessions.Where(s => s.UserId == userId).Select(s => s.MoveId).ToListAsync();
            var allMoves = await _db.Moves.ToListAsync();
            var notAttemptedMoves = allMoves.Where(m => !attemptedMoveIds.Contains(m.Id)).ToList();
                
            var remainingScores = new Dictionary<string, double>(perGroupScores);

            while (remainingScores.Count > 0)
            {
                double minScore = double.MaxValue;
                string minGroup = "";

                foreach (var group in remainingScores)
                {
                    if (group.Value < minScore)
                    {
                        minScore = group.Value;
                        minGroup = group.Key;
                    }
                }

                int diff;
                if (minScore < 40) diff = 1;
                else if (minScore < 70) diff = 2;
                else diff = 3;

                var match = notAttemptedMoves.FirstOrDefault(m => m.Musclegroup == minGroup && m.Difficulty == diff);
                if (match != null)
                    return Ok(match);

                remainingScores.Remove(minGroup);
            }

            return NotFound("No suitable move found");
        }

        [HttpPost("outcome")]
        public async Task<IActionResult> SubmitOutcome([FromBody] SessionDTO request)
        {
            var newSession = new Session
            {
                UserId = request.UserId,
                MoveId = request.MoveId,
                Completed = request.Completed
            };

            await _db.Sessions.AddAsync(newSession);
            await _db.SaveChangesAsync();

            return Ok("Session recorded");
        }
    }
}