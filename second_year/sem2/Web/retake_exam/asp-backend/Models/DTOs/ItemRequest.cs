namespace asp_backend.Models.DTOs
{
    public class ItemRequest
    {
        public string Title { get; set; } = null!;
        public string Description { get; set; } = null!;

        public int StartingPrice { get; set; }
    }
}
