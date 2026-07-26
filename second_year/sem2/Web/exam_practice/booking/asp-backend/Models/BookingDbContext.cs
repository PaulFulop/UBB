using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace asp_backend.Models;

public partial class BookingDbContext : DbContext
{
    public BookingDbContext()
    {
    }

    public BookingDbContext(DbContextOptions<BookingDbContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Booking> Bookings { get; set; }

    public virtual DbSet<Class> Classes { get; set; }

    public virtual DbSet<User> Users { get; set; }

    public virtual DbSet<WaitList> WaitLists { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        => optionsBuilder.UseSqlServer("Name=ConnectionStrings:Default");

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Booking>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__Booking__3213E83F38023510");

            entity.ToTable("Booking");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.BookedAt)
                .HasColumnType("datetime")
                .HasColumnName("bookedAt");
            entity.Property(e => e.Cancelled).HasColumnName("cancelled");
            entity.Property(e => e.ClassId).HasColumnName("classId");
            entity.Property(e => e.UserId).HasColumnName("userId");

            entity.HasOne(d => d.Class).WithMany(p => p.Bookings)
                .HasForeignKey(d => d.ClassId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__Booking__classId__48CFD27E");

            entity.HasOne(d => d.User).WithMany(p => p.Bookings)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__Booking__userId__47DBAE45");
        });

        modelBuilder.Entity<Class>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__Class__3213E83F72373C58");

            entity.ToTable("Class");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.ClassDate)
                .HasColumnType("datetime")
                .HasColumnName("classDate");
            entity.Property(e => e.ClassName)
                .HasMaxLength(10)
                .HasColumnName("className");
            entity.Property(e => e.InstructorName)
                .HasMaxLength(20)
                .HasColumnName("instructorName");
            entity.Property(e => e.MaxCapacity).HasColumnName("maxCapacity");
        });

        modelBuilder.Entity<User>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__User__3213E83FB1A536C6");

            entity.ToTable("User");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.MembershipType)
                .HasMaxLength(20)
                .HasColumnName("membershipType");
            entity.Property(e => e.Username)
                .HasMaxLength(20)
                .HasColumnName("username");
        });

        modelBuilder.Entity<WaitList>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__WaitList__3213E83FF6446B3F");

            entity.ToTable("WaitList");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.AddedAt)
                .HasColumnType("datetime")
                .HasColumnName("addedAt");
            entity.Property(e => e.ClassId).HasColumnName("classId");
            entity.Property(e => e.UserId).HasColumnName("userId");

            entity.HasOne(d => d.Class).WithMany(p => p.WaitLists)
                .HasForeignKey(d => d.ClassId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__WaitList__classI__4CA06362");

            entity.HasOne(d => d.User).WithMany(p => p.WaitLists)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__WaitList__userId__4BAC3F29");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
