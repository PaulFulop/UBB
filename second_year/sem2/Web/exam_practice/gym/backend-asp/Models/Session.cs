using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class Session
{
    public int Id { get; set; }

    public int UserId { get; set; }

    public int MoveId { get; set; }

    public bool Completed { get; set; }

    [JsonIgnore]
    public virtual Move Move { get; set; } = null!;

    [JsonIgnore]
    public virtual User User { get; set; } = null!;
}
