using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace WebExamProject1.Models;

public partial class Project
{
    public int Id { get; set; }

    public int ProjectManagerId { get; set; }

    public string? Name { get; set; }

    public string? Description { get; set; }

    public string? Members { get; set; }

    [JsonIgnore]
    public virtual SoftwareDeveloper IdNavigation { get; set; } = null!;
}
