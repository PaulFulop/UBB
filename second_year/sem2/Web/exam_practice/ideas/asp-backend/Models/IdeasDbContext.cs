using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace asp_backend.Models;

public partial class IdeasDbContext : DbContext
{
    public IdeasDbContext()
    {
    }

    public IdeasDbContext(DbContextOptions<IdeasDbContext> options)
        : base(options)
    {
    }

    public virtual DbSet<Comment> Comments { get; set; }

    public virtual DbSet<Idea> Ideas { get; set; }

    public virtual DbSet<User> Users { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        => optionsBuilder.UseSqlServer("Name=ConnectionStrings:Default");

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Comment>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__Comment__3213E83F042BFCD0");

            entity.ToTable("Comment");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Body)
                .HasMaxLength(100)
                .HasColumnName("body");
            entity.Property(e => e.IdeaId).HasColumnName("ideaId");
            entity.Property(e => e.PostedAt)
                .HasColumnType("datetime")
                .HasColumnName("postedAt");
            entity.Property(e => e.UserId).HasColumnName("userId");

            entity.HasOne(d => d.Idea).WithMany(p => p.Comments)
                .HasForeignKey(d => d.IdeaId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__Comment__ideaId__3C69FB99");

            entity.HasOne(d => d.User).WithMany(p => p.Comments)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__Comment__userId__3D5E1FD2");
        });

        modelBuilder.Entity<Idea>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__Idea__3213E83FD5D96E81");

            entity.ToTable("Idea");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Body)
                .HasMaxLength(100)
                .HasColumnName("body");
            entity.Property(e => e.PostedAt)
                .HasColumnType("datetime")
                .HasColumnName("postedAt");
            entity.Property(e => e.Title)
                .HasMaxLength(50)
                .HasColumnName("title");
            entity.Property(e => e.UserId).HasColumnName("userId");
            entity.Property(e => e.Votes)
                .HasMaxLength(9)
                .HasColumnName("votes");

            entity.HasOne(d => d.User).WithMany(p => p.Ideas)
                .HasForeignKey(d => d.UserId)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK__Idea__userId__398D8EEE");
        });

        modelBuilder.Entity<User>(entity =>
        {
            entity.HasKey(e => e.Id).HasName("PK__User__3213E83F35C6EA15");

            entity.ToTable("User");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.LastSeen)
                .HasColumnType("datetime")
                .HasColumnName("lastSeen");
            entity.Property(e => e.Username)
                .HasMaxLength(50)
                .HasColumnName("username");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
