using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace backend_asp.Models;

public partial class GymDbContext : DbContext
{
    public GymDbContext()
    {
    }

    public GymDbContext(DbContextOptions<GymDbContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Move> Moves { get; set; }

    public virtual DbSet<Session> Sessions { get; set; }

    public virtual DbSet<User> Users { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        => optionsBuilder.UseSqlServer("Name=ConnectionStrings:Default");

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Move>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__Move__3213E83FF89ACE90");

            entity.ToTable("Move");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Difficulty).HasColumnName("difficulty");
            entity.Property(e => e.Musclegroup)
                .HasMaxLength(50)
                .HasColumnName("musclegroup");
            entity.Property(e => e.Name)
                .HasMaxLength(50)
                .HasColumnName("name");
        });

        modelBuilder.Entity<Session>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__Session__3213E83F679908B7");

            entity.ToTable("Session");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Completed).HasColumnName("completed");
            entity.Property(e => e.MoveId).HasColumnName("moveId");
            entity.Property(e => e.UserId).HasColumnName("userId");

            entity.HasOne(d => d.Move).WithMany(p => p.Sessions)
                .HasForeignKey(d => d.MoveId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__Session__moveId__3D5E1FD2");

            entity.HasOne(d => d.User).WithMany(p => p.Sessions)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__Session__userId__3C69FB99");
        });

        modelBuilder.Entity<User>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__User__3213E83F57E0BEDA");

            entity.ToTable("User");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.FitnessGoal)
                .HasMaxLength(50)
                .HasColumnName("fitnessGoal");
            entity.Property(e => e.Username)
                .HasMaxLength(50)
                .HasColumnName("username");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
