using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace asp_backend.Models;

public partial class Bid
{
    public int Id { get; set; }

    public int ItemId { get; set; }

    public int UserId { get; set; }

    public int Amount { get; set; }

    public DateTime PlacedAt { get; set; }

    [JsonIgnore]
    public virtual Item Item { get; set; } = null!;

    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
