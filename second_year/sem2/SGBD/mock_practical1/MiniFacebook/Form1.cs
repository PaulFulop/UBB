using Microsoft.Data.SqlClient;
using System.Data;

namespace MiniFacebook
{
    public partial class Form1 : Form
    {
        private String connStr = "Data Source=localhost;Initial Catalog=MiniFacebook;Integrated Security=True;TrustServerCertificate=True";
        private readonly SqlConnection connection;
        private SqlDataAdapter usersDataAdapter, postsDataAdapter;
        private readonly DataSet dataSet = new DataSet();

        private readonly BindingSource usersBindingSource = new BindingSource();
        private readonly BindingSource postsBindingSource = new BindingSource();

        public Form1()
        {
            InitializeComponent();

            connection = new SqlConnection(connStr);

            // loading the tables and fill the dataset
            usersDataAdapter = new SqlDataAdapter("SELECT * FROM Users", connection);
            postsDataAdapter = new SqlDataAdapter("SELECT * FROM Posts", connection);

            usersDataAdapter.Fill(dataSet, "Users");
            postsDataAdapter.Fill(dataSet, "Posts");

            // set up the command builder for automatic recognition of commands on Update() of postsDataAdapter
            new SqlCommandBuilder(postsDataAdapter);

            // add the 1-n relation between the tables
            dataSet.Relations.Add("Users_Posts", dataSet.Tables["Users"].Columns["uid"],
                dataSet.Tables["Posts"].Columns["uid"]);

            // load the data on the grid views
            usersBindingSource.DataSource = dataSet;
            usersBindingSource.DataMember = "Users";
            dgvUsers.DataSource  = usersBindingSource;

            postsBindingSource.DataSource = usersBindingSource;
            postsBindingSource.DataMember = "Users_Posts";
            dgvPosts.DataSource = postsBindingSource;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            // important, say EndEdit() to save the changes even if they're not commited/pending still (user is still typing but presses save)
            usersBindingSource.EndEdit();
            postsBindingSource.EndEdit();

            postsDataAdapter.Update(dataSet.Tables["Posts"]);
            dataSet.Tables["Posts"].AcceptChanges(); // It clears the RowState flags on every row in that table.
        }
    }
}
