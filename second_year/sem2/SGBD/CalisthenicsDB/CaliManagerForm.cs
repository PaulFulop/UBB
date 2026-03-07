using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Data.SqlClient;

namespace CalisthenicsDB
{
    public partial class CalistenicsForm : Form
    {
        private readonly string connectionString = "Data Source=.;Initial Catalog=CalisthenicsShop;Integrated Security=True;Trust Server Certificate=True";
        private readonly string CUSTOMER_TABLE = "Customer",
                                REVIEW_TABLE = "Review";
        private SqlDataAdapter customersDataAdapter, reviewDataAdapter;
        private readonly DataSet dataSet = new DataSet();

        private readonly BindingSource customersBindingSource = new BindingSource();
        private readonly BindingSource reviewsBindingSource = new BindingSource();

        private void InitializeGridViews()
        {
            InitializeDGVCustomer();
            InitializeDGVReview();
        }

        private void InitializeDGVCustomer()
        {
            customersBindingSource.DataSource = dataSet;
            customersBindingSource.DataMember = CUSTOMER_TABLE;
            dgvCustomer.DataSource = customersBindingSource;
        }

        private void InitializeDGVReview()
        {
            reviewsBindingSource.DataSource = dataSet;
            reviewsBindingSource.DataMember = REVIEW_TABLE;
            dgvReviews.DataSource = reviewsBindingSource;
        }

        public CalistenicsForm()
        {
            InitializeComponent();
            InitializeDB();
            InitializeGridViews();
        }

        private void InitializeDB()
        {
            // close connection after using it
            using (SqlConnection connection = new SqlConnection(connectionString))
            {
                customersDataAdapter = new SqlDataAdapter($"SELECT * FROM {CUSTOMER_TABLE}", connection);
                customersDataAdapter.Fill(dataSet, CUSTOMER_TABLE);

                reviewDataAdapter = new SqlDataAdapter($"SELECT * FROM {REVIEW_TABLE}", connection);
                reviewDataAdapter.Fill(dataSet, REVIEW_TABLE);
            }
        }
    }
}
