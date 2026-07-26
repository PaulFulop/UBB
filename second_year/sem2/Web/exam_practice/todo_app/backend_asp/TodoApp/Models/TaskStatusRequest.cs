namespace TodoApp.Models
{
    public class TaskStatusRequest
    {
        public int UserId { get; set; }
        public int TaskId { get; set; }
        public DateTime TimeStamp { get; set; } = DateTime.Now;
        public string Status { get; set; } = "todo";
    }
}
