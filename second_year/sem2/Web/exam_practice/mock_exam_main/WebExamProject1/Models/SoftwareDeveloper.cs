using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace WebExamProject1.Models;

public partial class SoftwareDeveloper
{
    public int Id { get; set; }

    public string? Name { get; set; }

    public int? Age { get; set; }

    public string? Skills { get; set; }

    [JsonIgnore]
    public virtual Project? Project { get; set; }
}
