using Microsoft.EntityFrameworkCore.SqlServer.Query.Internal;

namespace backend_asp.Models.DTOs
{
    public class RecipeDTO
    {
        public int UserId { get; set; }
        public String Title { get; set; } = String.Empty;
        public int TotalCalories { get; set; }
        public List<RecipeStepDTO> RecipeSteps { get; set; } = [];
    }
}
