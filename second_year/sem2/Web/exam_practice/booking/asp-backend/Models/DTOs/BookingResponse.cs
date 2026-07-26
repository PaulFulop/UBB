namespace asp_backend.Models.DTOs
{
    public class BookingResponse
    {
        public String ClassName { get; set; } = null!;
        public DateTime Date { get; set; }

        public bool Status { get; set; }
    }
}
