using asp_backend.Models;
using asp_backend.Models.DTOs;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Metadata.Conventions;

namespace asp_backend.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class IdeasController : Controller
    {
        private IdeasDbContext _db = new IdeasDbContext();
        public IdeasController(IdeasDbContext db) => _db = db;

        [HttpGet]
        public async Task<IActionResult> GetAllIdeas()
        {
            List<IdeaDTO> ideas = new List<IdeaDTO>();
            var ideaList = await _db.Ideas.ToListAsync();

            foreach (var idea in ideaList)
            {
                IdeaDTO ideaDTO = new IdeaDTO();
                ideaDTO.Id = idea.Id;
                ideaDTO.Title = idea.Title;
                ideaDTO.Author = _db.Users.FirstOrDefault(u => u.Id == idea.UserId).Username;
                ideaDTO.VoteCount = idea.Votes;

                int comments = _db.Comments.Where(c => c.IdeaId == idea.Id).Count();
                ideaDTO.NumberOfComments = comments;

                ideas.Add(ideaDTO);
            }


            return Ok(ideas);
        }

        [HttpPost("{userId}")]
        public async Task<IActionResult> AddIdea(int userId, [FromBody]IdeaRequestDTO request)
        {
            _db.Ideas.Add(new Idea
            {
                UserId = userId,
                Title = request.Title,
                Body = request.Body,
                PostedAt = DateTime.Now,
                Votes = "0"
            });

            await _db.SaveChangesAsync();
            return Ok("Idea added!");
        }

        [HttpPatch("{ideaId}")]
        public async Task<IActionResult> UpdateVotes(int ideaId, [FromBody] string newVotes)
        {
            var idea = await _db.Ideas.FirstOrDefaultAsync(i => i.Id == ideaId);
            if (idea == null) return NotFound("Idea not found!");

            idea.Votes = newVotes;
            await _db.SaveChangesAsync();
            return Ok();
        }
    }
}
