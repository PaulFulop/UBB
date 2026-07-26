namespace backend_asp.Models.DTOs
{
    public class SessionDTO
    {
        public int UserId { get; set; }
        public int MoveId { get; set; }
        public bool Completed { get; set; }
    }
}
