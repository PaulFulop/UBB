using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace RecipesBackend.Models;

public partial class Recipe
{
    public int Id { get; set; }

    public string Author { get; set; } = null!;

    public string Name { get; set; } = null!;

    public string Type { get; set; } = null!;

    [JsonPropertyName("recipe")]
    public string RecipeDescription { get; set; } = null!;
}
