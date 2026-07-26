using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class OrderItem
{
    public int Id { get; set; }

    public int OrderId { get; set; }

    public int ProductId { get; set; }

    [JsonIgnore]
    public virtual Order Order { get; set; } = null!;

    [JsonIgnore]
    public virtual Product Product { get; set; } = null!;
}
