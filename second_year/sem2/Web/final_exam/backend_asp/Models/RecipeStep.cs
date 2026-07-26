using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class RecipeStep
{
    public int Id { get; set; }

    public int RecipeId { get; set; }

    public int StepNumber { get; set; }

    public string Description { get; set; } = null!;

    public string IngredientIds { get; set; } = null!;

    [JsonIgnore]
    public virtual Recipe Recipe { get; set; } = null!;
}
