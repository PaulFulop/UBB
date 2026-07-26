using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class HotelRoom
{
    public int Id { get; set; }

    public string? RoomNumber { get; set; }

    public int Capacity { get; set; }

    public int BasePrice { get; set; }

    [JsonIgnore]
    public virtual ICollection<Reservation> Reservations { get; set; } = new List<Reservation>();
}
