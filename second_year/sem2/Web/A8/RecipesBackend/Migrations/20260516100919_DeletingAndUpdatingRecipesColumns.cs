using System;
using Microsoft.EntityFrameworkCore.Metadata;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace RecipesBackend.Migrations
{
    /// <inheritdoc />
    public partial class DeletingAndUpdatingRecipesColumns : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "created_at",
                table: "recipes");

            migrationBuilder.DropColumn(
                name: "updated_at",
                table: "recipes");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<DateTime>(
                name: "created_at",
                table: "recipes",
                type: "timestamp",
                nullable: false,
                defaultValueSql: "current_timestamp()");

            migrationBuilder.AddColumn<DateTime>(
                name: "updated_at",
                table: "recipes",
                type: "timestamp",
                nullable: false,
                defaultValueSql: "current_timestamp()")
                .Annotation("MySql:ValueGenerationStrategy", MySqlValueGenerationStrategy.ComputedColumn);
        }
    }
}
