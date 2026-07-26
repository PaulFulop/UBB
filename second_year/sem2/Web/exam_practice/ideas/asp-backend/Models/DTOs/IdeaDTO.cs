namespace asp_backend.Models.DTOs
{
    public class IdeaDTO
    {
        public int Id { get; set; } 
        public string Title { get; set; } = null!;
        public string Author { get; set; } = null!;
        public string VoteCount { get; set; } = null!;
        public int NumberOfComments { get; set; }

    }
}
