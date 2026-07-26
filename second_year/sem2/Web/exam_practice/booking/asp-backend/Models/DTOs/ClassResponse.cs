namespace asp_backend.Models.DTOs
{
    public class ClassResponse
    {
        public int Id { get; set; } 
        public string ClassName { get; set; } = null!;

        public string InstructorName { get; set; } = null!;

        public DateTime ClassDate { get; set; } = DateTime.Now;

        public int RemainingSpots { get; set; } = 0!;
    }
}
