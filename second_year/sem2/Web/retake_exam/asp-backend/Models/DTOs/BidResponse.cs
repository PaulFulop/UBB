namespace asp_backend.Models.DTOs
{
    public class BidResponse
    {
        public int Id { get; set; } 
        public string ItemName { get; set; } = null!;
        public string UserName { get; set; } = null!;
        public int Amount { get; set; }
        public DateTime PlacedAt {  get; set; } = DateTime.Now;
    }
}
