using Microsoft.Data.SqlClient;
using System.Data;

namespace Hospital
{
    public partial class Form1 : Form
    {
        private String connStr = "Data Source=localhost;Initial Catalog=HospitalDB;Integrated Security=True;TrustServerCertificate=True";
        private SqlConnection connection;
        private SqlDataAdapter patientsAdapter, appointmentsAdapter;
        private DataSet dataSet = new DataSet();
        private BindingSource patientsBindingSource, appointmentsBindingSource;

        public Form1()
        {
            InitializeComponent();

            connection = new SqlConnection(connStr);
            patientsAdapter = new SqlDataAdapter("SELECT * FROM Patient", connection);
            patientsAdapter.Fill(dataSet, "Patient");

            appointmentsAdapter = new SqlDataAdapter("SELECT * FROM Appointment", connection);
            appointmentsAdapter.Fill(dataSet, "Appointment");
            new SqlCommandBuilder(appointmentsAdapter);

            dataSet.Relations.Add("Patient_Appointments",
                dataSet.Tables["Patient"].Columns["pid"],
                dataSet.Tables["Appointment"].Columns["pid"]);

            patientsBindingSource = new BindingSource { DataSource = dataSet, DataMember = "Patient" };
            appointmentsBindingSource = new BindingSource { DataSource = patientsBindingSource, DataMember = "Patient_Appointments" };

            dgvPatients.DataSource = patientsBindingSource;
            dgvAppointments.DataSource = appointmentsBindingSource;
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            patientsBindingSource.EndEdit();
            appointmentsBindingSource.EndEdit();
            appointmentsAdapter.Update(dataSet.Tables["Appointment"]);
            dataSet.AcceptChanges();
        }
    }
}
