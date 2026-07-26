using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace asp_backend.Models;

public partial class Item
{
    public int Id { get; set; }

    public int UserId { get; set; }

    public string Title { get; set; } = null!;

    public string Description { get; set; } = null!;

    public int StartingPrice { get; set; }

    public int CurrentPrice { get; set; }
    [JsonIgnore]
    public virtual ICollection<Bid> Bids { get; set; } = new List<Bid>();
    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
