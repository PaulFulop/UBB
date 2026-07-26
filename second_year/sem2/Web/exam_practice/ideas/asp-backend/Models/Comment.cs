using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace asp_backend.Models;

public partial class Comment
{
    public int Id { get; set; }

    public int IdeaId { get; set; }

    public int UserId { get; set; }

    public string Body { get; set; } = null!;

    public DateTime PostedAt { get; set; }

    [JsonIgnore]
    public virtual Idea Idea { get; set; } = null!;

    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
