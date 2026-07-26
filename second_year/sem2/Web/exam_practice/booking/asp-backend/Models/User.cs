using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace asp_backend.Models;

public partial class User
{
    public int Id { get; set; }

    public string Username { get; set; } = null!;

    public string MembershipType { get; set; } = null!;

    [JsonIgnore]
    public virtual ICollection<Booking> Bookings { get; set; } = new List<Booking>();

    [JsonIgnore]
    public virtual ICollection<WaitList> WaitLists { get; set; } = new List<WaitList>();
}
