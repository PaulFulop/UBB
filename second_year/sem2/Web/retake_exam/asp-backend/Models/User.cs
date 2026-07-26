using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace asp_backend.Models;

public partial class User
{
    public int Id { get; set; }

    public string Username { get; set; } = null!;

    public DateTime LastSeen { get; set; }
    [JsonIgnore]
    public virtual ICollection<Bid> Bids { get; set; } = new List<Bid>();
    [JsonIgnore]
    public virtual ICollection<Item> Items { get; set; } = new List<Item>();
}
