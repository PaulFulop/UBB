using System.Reflection.Metadata.Ecma335;

namespace WebExamProject1.Models
{
    public class AssignRequest
    {
        public string DeveloperName { get; set; } = string.Empty;
        public List<string> ProjectNames { get; set; } = [];
    }
}
