using System;
using System.Collections.Generic;
using Microsoft.EntityFrameworkCore;

namespace WebExamProject1.Models;

public partial class WebExam1Context : DbContext
{
    public WebExam1Context()
    {
    }

    public WebExam1Context(DbContextOptions<WebExam1Context> options)
        : base(options)
    {
    }

    public virtual DbSet<Project> Projects { get; set; }

    public virtual DbSet<SoftwareDeveloper> SoftwareDevelopers { get; set; }

    protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        => optionsBuilder.UseSqlServer("Name=ConnectionStrings:Default");

    protected override void OnModelCreating(ModelBuilder modelBuilder)
    {
        modelBuilder.Entity<Project>(entity =>
        {
            entity.ToTable("Project");

            entity.Property(e => e.Id)
                .ValueGeneratedOnAdd()
                .HasColumnName("id");
            entity.Property(e => e.Description)
                .HasMaxLength(50)
                .HasColumnName("description");
            entity.Property(e => e.Members)
                .HasMaxLength(100)
                .HasColumnName("members");
            entity.Property(e => e.Name)
                .HasMaxLength(50)
                .HasColumnName("name");
            entity.Property(e => e.ProjectManagerId).HasColumnName("ProjectManagerID");

            entity.HasOne(d => d.IdNavigation).WithOne(p => p.Project)
                .HasForeignKey<Project>(d => d.Id)
                .OnDelete(DeleteBehavior.ClientSetNull)
                .HasConstraintName("FK_Project_SoftwareDeveloper");
        });

        modelBuilder.Entity<SoftwareDeveloper>(entity =>
        {
            entity.ToTable("SoftwareDeveloper");

            entity.Property(e => e.Id).HasColumnName("id");
            entity.Property(e => e.Age).HasColumnName("age");
            entity.Property(e => e.Name)
                .HasMaxLength(50)
                .HasColumnName("name");
            entity.Property(e => e.Skills)
                .HasMaxLength(100)
                .HasColumnName("skills");
        });

        OnModelCreatingPartial(modelBuilder);
    }

    partial void OnModelCreatingPartial(ModelBuilder modelBuilder);
}
