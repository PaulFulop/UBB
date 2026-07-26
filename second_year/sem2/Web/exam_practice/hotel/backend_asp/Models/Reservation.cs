using System;
using System.Collections.Generic;
using System.Text.Json.Serialization;

namespace backend_asp.Models;

public partial class Reservation
{
    public int Id { get; set; }

    public int? UserId { get; set; }

    public int? RoomId { get; set; }

    public DateTime CheckInDate { get; set; }

    public DateTime CheckOutDate { get; set; }

    public int NumberOfGuests { get; set; }

    public int TotalPrice { get; set; }

    [JsonIgnore]
    public virtual HotelRoom? Room { get; set; }

    [JsonIgnore]
    public virtual User? User { get; set; }
}
