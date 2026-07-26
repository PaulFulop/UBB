using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace backend_asp.Models;

public partial class HotelDbContext : DbContext
{
    public HotelDbContext()
    {
    }

    public HotelDbContext(DbContextOptions<HotelDbContext> options)
        : base(options)
    {
    }

    public virtual DbSet<HotelRoom> HotelRooms { get; set; }

    public virtual DbSet<Reservation> Reservations { get; set; }

    public virtual DbSet<User> Users { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        => optionsBuilder.UseSqlServer("Name=ConnectionStrings:Default");

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<HotelRoom>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__HotelRoo__3213E83F5B136F52");

            entity.ToTable("HotelRoom");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.BasePrice).HasColumnName("basePrice");
            entity.Property(e => e.Capacity).HasColumnName("capacity");
            entity.Property(e => e.RoomNumber)
                .HasMaxLength(10)
                .HasColumnName("roomNumber");
        });

        modelBuilder.Entity<Reservation>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__Reservat__3213E83F83C8613B");

            entity.ToTable("Reservation");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.CheckInDate)
                .HasColumnType("datetime")
                .HasColumnName("checkInDate");
            entity.Property(e => e.CheckOutDate)
                .HasColumnType("datetime")
                .HasColumnName("checkOutDate");
            entity.Property(e => e.NumberOfGuests).HasColumnName("numberOfGuests");
            entity.Property(e => e.RoomId).HasColumnName("roomId");
            entity.Property(e => e.TotalPrice).HasColumnName("totalPrice");
            entity.Property(e => e.UserId).HasColumnName("userId");

            entity.HasOne(d => d.Room).WithMany(p => p.Reservations)
                .HasForeignKey(d => d.RoomId)
                .HasConstraintName("FK__Reservati__roomI__3C69FB99");

            entity.HasOne(d => d.User).WithMany(p => p.Reservations)
                .HasForeignKey(d => d.UserId)
                .HasConstraintName("FK__Reservati__userI__3B75D760");
        });

        modelBuilder.Entity<User>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__User__3213E83FF3025FD1");

            entity.ToTable("User");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Password)
                .HasMaxLength(50)
                .HasColumnName("password");
            entity.Property(e => e.Username)
                .HasMaxLength(50)
                .HasColumnName("username");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
