using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace asp_backend.Models;

public partial class Class
{
    public int Id { get; set; }

    public string ClassName { get; set; } = null!;

    public string InstructorName { get; set; } = null!;

    public DateTime ClassDate { get; set; }

    public int MaxCapacity { get; set; }

    [JsonIgnore]
    public virtual ICollection<Booking> Bookings { get; set; } = new List<Booking>();

    [JsonIgnore]
    public virtual ICollection<WaitList> WaitLists { get; set; } = new List<WaitList>();
}
