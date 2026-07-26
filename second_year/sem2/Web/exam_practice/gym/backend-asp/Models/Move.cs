using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class Move
{
    public int Id { get; set; }

    public string Name { get; set; } = null!;

    public int Difficulty { get; set; }

    public string Musclegroup { get; set; } = null!;

    [JsonIgnore]
    public virtual ICollection<Session> Sessions { get; set; } = new List<Session>();
}
