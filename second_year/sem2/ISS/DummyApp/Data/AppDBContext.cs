using Microsoft.EntityFrameworkCore;

namespace DummyApp.Data
{
    public class AppDBContext : DbContext
    {
        public AppDBContext(DbContextOptions<AppDBContext> options) : base(options)
        {
        }
        public DbSet<Model.Message> Messages { get; set; }
    }
}
