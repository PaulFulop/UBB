namespace backend_asp.Models.DTOs
{
    public class ConfirmOrderDTO
    {
        public int UserId { get; set; }
        public List<Product> Products { get; set; } = [];
    }
}
