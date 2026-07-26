using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace TodoApp.Models;

public partial class Task
{
    public int Id { get; set; }

    public string? Title { get; set; }

    public string? Status { get; set; }

    public int? AssignedTo { get; set; }

    public DateTime? LastUpdated { get; set; }

    [JsonIgnore]
    public virtual User? AssignedToNavigation { get; set; }
    [JsonIgnore]
    public virtual ICollection<TaskLog> TaskLogs { get; set; } = new List<TaskLog>();
}
