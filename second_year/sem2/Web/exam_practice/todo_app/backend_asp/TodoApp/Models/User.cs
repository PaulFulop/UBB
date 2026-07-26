using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace TodoApp.Models;

public partial class User
{
    public int Id { get; set; }

    public string? Username { get; set; }

    [JsonIgnore]
    public virtual ICollection<TaskLog> TaskLogs { get; set; } = new List<TaskLog>();

    [JsonIgnore]
    public virtual ICollection<Task> Tasks { get; set; } = new List<Task>();
}
