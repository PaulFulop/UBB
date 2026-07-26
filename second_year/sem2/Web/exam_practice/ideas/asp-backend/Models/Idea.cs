using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace asp_backend.Models;

public partial class Idea
{
    public int Id { get; set; }

    public int UserId { get; set; }

    public string Title { get; set; } = null!;

    public string Body { get; set; } = null!;

    public DateTime PostedAt { get; set; }

    public string Votes { get; set; } = null!;

    [JsonIgnore]
    public virtual ICollection<Comment> Comments { get; set; } = new List<Comment>();

    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
