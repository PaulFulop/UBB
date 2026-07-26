namespace backend_asp.Models.DTOs
{
    public class DateIntervalDTO
    {
        public DateTime EarliestDate { get; set; } = DateTime.Now;
        public DateTime LatestDate { get; set; } = DateTime.Now;
    }
}
