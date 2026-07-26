namespace asp_backend.Models.DTOs
{
    public class ItemResponse
    {
        public int Id { get; set; }
        public string Title { get; set; } = null!;
        public string Seller { get; set; } = null!;
        public int CurrentPrice { get; set; }
        public int NumOfBids { get; set; }
    }
}
