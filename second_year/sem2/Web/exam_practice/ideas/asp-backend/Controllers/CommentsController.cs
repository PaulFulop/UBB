using asp_backend.Models;
using asp_backend.Models.DTOs;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;

namespace asp_backend.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class CommentsController : Controller
    {
        private IdeasDbContext _db = new IdeasDbContext();
        public CommentsController(IdeasDbContext db) => _db = db;

        [HttpGet("{ideaId}")]
        public async Task<IActionResult> GetComments(int ideaId)
        {
            var comments = await _db.Comments.Where(c => c.IdeaId == ideaId).Select(c => c.Body).ToListAsync();
            return Ok(comments);
        }

        [HttpPost("{userId}/{ideaId}")]
        public async Task<IActionResult> AddComment(int userId, int ideaId, [FromBody] string body)
        {
            _db.Comments.Add(new Comment
            {
                IdeaId = ideaId,
                UserId = userId,
                Body = body,
                PostedAt = DateTime.Now
            });


            await _db.SaveChangesAsync();
            return Ok("Idea added!");
        }
    }
}
