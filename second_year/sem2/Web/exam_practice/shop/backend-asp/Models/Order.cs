using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class Order
{
    public int Id { get; set; }

    public int UserId { get; set; }

    public decimal? TotalPrice { get; set; }

    [JsonIgnore]
    public virtual ICollection<OrderItem> OrderItems { get; set; } = new List<OrderItem>();

    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
