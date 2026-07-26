using Azure.Core;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Microsoft.IdentityModel.Tokens;
using WebExamProject1.Models;
using static System.Net.WebRequestMethods;

namespace WebExamProject1.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class ProjectsController : ControllerBase
    {
        private WebExam1Context _db = new WebExam1Context();

        public ProjectsController(WebExam1Context db) => _db = db;

        [HttpGet]
        public async Task<IActionResult> GetProjects()
        {
            var projects = await _db.Projects.ToListAsync();
            return Ok(projects);
        }

        [HttpGet("member/{name}")]
        public async Task<IActionResult> GetProject(string name)
        {
            var projects = await _db.Projects.Where(p => p.Members != null && p.Members.Contains(name)).Select(p => p.Name).ToListAsync();
            if (projects == null) return NotFound();
            return Ok(projects);
        }

        [HttpPost("assign")]
        public async Task<IActionResult> AssignDeveloperToProjects([FromBody] AssignRequest req)
        {
            var rawDeveloperName = await _db.SoftwareDevelopers.Select(d => d.Name).FirstOrDefaultAsync(sd => sd != null && sd.ToLower() == req.DeveloperName.ToLower());
            if (rawDeveloperName == null) return Ok("No developer has been found.");

            
            foreach(var projectName in req.ProjectNames)
            {
                // find the project by name,
                // assign a member (add the developers name to the members string) and save the changes to the db

                var project = await _db.Projects.FirstOrDefaultAsync(p => p.Name != null && p.Name.ToLower() == projectName.ToLower());
                
                if (project == null){
                    // create a new project 
                    project = new Project()
                    {
                        Name = projectName,
                        Members = rawDeveloperName
                    };
                    _db.Projects.Add(project);
                }
                else if (string.IsNullOrEmpty(project.Members))
                {
                    project.Members = rawDeveloperName;
                }
                else if (!project.Members.Split(',').Select(m => m.Trim()).Contains(rawDeveloperName))
                {
                    project.Members += "," + rawDeveloperName;
                }
            }
            
            await _db.SaveChangesAsync();
            return Ok("Developer assigned to projects successfully.");
        }

    }
}
