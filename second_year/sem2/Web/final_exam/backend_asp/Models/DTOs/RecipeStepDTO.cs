namespace backend_asp.Models.DTOs
{
    public class RecipeStepDTO
    {
        public int StepNumber { get; set; }
        public string Description { get; set; } = "";
        public string IngredientIds { get; set; } = "";
    }
}
