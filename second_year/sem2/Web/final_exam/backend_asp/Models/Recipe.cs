using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class Recipe
{
    public int Id { get; set; }

    public int UserId { get; set; }

    public string Title { get; set; } = null!;

    public int TotalCalories { get; set; }

    [JsonIgnore]
    public virtual ICollection<RecipeStep> RecipeSteps { get; set; } = new List<RecipeStep>();

    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
