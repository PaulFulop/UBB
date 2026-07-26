using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace asp_backend.Models;

public partial class WaitList
{
    public int Id { get; set; }

    public int UserId { get; set; }

    public int ClassId { get; set; }

    public DateTime AddedAt { get; set; }

    [JsonIgnore]
    public virtual Class Class { get; set; } = null!;

    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
