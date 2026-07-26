using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class User
{
    public int Id { get; set; }

    public string Username { get; set; } = null!;

    public string FitnessGoal { get; set; } = null!;

    [JsonIgnore]
    public virtual ICollection<Session> Sessions { get; set; } = new List<Session>();
}
