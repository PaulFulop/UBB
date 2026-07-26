namespace backend_asp.Models.DTOs
{
    public class ReserveRoomDTO
    {
        public int UserId { get; set; }
        public int RoomId { get; set; }
        public DateTime EarliestDate { get; set; } = DateTime.Now;
        public DateTime LatestDate { get; set; } = DateTime.Now;

        public int NumberOfGuests { get; set; } = 1;
    }
}
