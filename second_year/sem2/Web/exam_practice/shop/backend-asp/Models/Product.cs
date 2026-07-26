using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class Product
{
    public int Id { get; set; }

    public string? Name { get; set; }

    public decimal Price { get; set; }

    [JsonIgnore]
    public virtual ICollection<OrderItem> OrderItems { get; set; } = new List<OrderItem>();
}
