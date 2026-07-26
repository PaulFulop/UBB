using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using TodoApp.Models;

namespace TodoApp.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class TasksController : Controller
    {
        private TaskManagementContext _db = new TaskManagementContext();

        public TasksController(TaskManagementContext db) => _db = db;

        [HttpGet]
        public async Task<IActionResult> GetAllTasks()
        {
            var tasks = await _db.Tasks.ToListAsync();
            var taskLogs = await _db.TaskLogs.ToListAsync();
            var users = await _db.Users.ToListAsync();

            var result = tasks.Select(t =>
            {
                var lastLog = taskLogs
                    .Where(l => l.TaskId == t.Id)
                    .OrderByDescending(l => l.Timestamp)
                    .FirstOrDefault();

                var lastUser = lastLog != null ? users.FirstOrDefault(u => u.Id == lastLog.UserId) : null;

                return new
                {
                    t.Id,
                    t.Title,
                    t.Status,
                    t.AssignedTo,
                    t.LastUpdated,
                    LastUpdatedByName = lastUser?.Username
                };
            });
            
            return Ok(result);
        }

        [HttpPut]
        public async Task<IActionResult> UpdateTaskStatus([FromBody] TaskStatusRequest request)
        {
            var task = await _db.Tasks.FindAsync(request.TaskId);
            if (task == null) return NotFound();


            var newTaskLog = new TaskLog
            {
                TaskId = request.TaskId,
                UserId = request.UserId,
                OldStatus = task.Status,
                NewStatus = request.Status,
                Timestamp = request.TimeStamp
            };
            _db.TaskLogs.Add(newTaskLog);
            task.Status = request.Status;

            await _db.SaveChangesAsync();
            return Ok("Task status updated successfully");
        }

    }
}
