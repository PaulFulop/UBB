using Microsoft.Data.SqlClient;
using System.Data;

namespace Tournament
{
    public partial class Form1 : Form
    {
        private String connString = "Data Source=localhost;Initial Catalog=Tournaments;Integrated Security=True;TrustServerCertificate=True";
        private SqlConnection connection;
        private SqlDataAdapter matchesAdapter, courtsAdapter;
        private DataSet dataset = new DataSet();
        private BindingSource matchesBindingSource = new BindingSource(),
            courtsBindingSource = new BindingSource();

        public Form1()
        {
            InitializeComponent();

            connection = new SqlConnection(connString);
            matchesAdapter = new SqlDataAdapter("SELECT * FROM Matches", connection);
            courtsAdapter = new SqlDataAdapter("SELECT * FROM Courts", connection);

            matchesAdapter.Fill(dataset, "Matches");
            courtsAdapter.Fill(dataset, "Courts");
            dataset.Relations.Add("Courts_Matches",
                dataset.Tables["Courts"].Columns["cid"], dataset.Tables["Matches"].Columns["cid"]);

            new SqlCommandBuilder(matchesAdapter);

            courtsBindingSource.DataSource = dataset;
            courtsBindingSource.DataMember = "Courts";
            matchesBindingSource.DataSource = courtsBindingSource;
            matchesBindingSource.DataMember = "Courts_Matches";
            dgvCourts.DataSource = courtsBindingSource;
            dgvMatches.DataSource = matchesBindingSource;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            courtsBindingSource.EndEdit();
            matchesBindingSource.EndEdit();

            try {
                matchesAdapter.Update(dataset.Tables["Matches"]);
                dataset.AcceptChanges();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

        }
    }
}
