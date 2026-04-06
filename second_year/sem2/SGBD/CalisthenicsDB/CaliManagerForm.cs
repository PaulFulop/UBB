using Microsoft.Data.SqlClient;
using Microsoft.IdentityModel.Protocols;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Configuration;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CalisthenicsDB
{
    public partial class CalistenicsForm : Form
    {
        private readonly string PARENT_TABLE, CHILD_TABLE, PK_COLUMN, FK_COLUMN;
        private SqlDataAdapter parentDataAdapter, childDataAdapter;
        private readonly DataSet dataSet = new DataSet();
        private readonly SqlConnection connection;

        private readonly BindingSource parentBindingSource = new BindingSource();
        private readonly BindingSource childBindingSource = new BindingSource();

        // TODOdouble click / tab does not go directly into edit mode, fix this
        public CalistenicsForm()
        {
            ExeConfigurationFileMap configMap = new ExeConfigurationFileMap
            {
                ExeConfigFilename = "CalisthenicsDB.config"
            };

            Configuration customConfig = ConfigurationManager.OpenMappedExeConfiguration(configMap, ConfigurationUserLevel.None);

            PARENT_TABLE = customConfig.AppSettings.Settings["ParentTable"].Value;
            CHILD_TABLE = customConfig.AppSettings.Settings["ChildTable"].Value;
            PK_COLUMN = customConfig.AppSettings.Settings["ParentTablePK"].Value;
            FK_COLUMN = customConfig.AppSettings.Settings["ChildTableFK"].Value;

            string connString = customConfig.ConnectionStrings.ConnectionStrings["CalisthenicsShopConnection"].ConnectionString;
            connection = new SqlConnection(connString);

            // 3. Setup form
            InitializeComponent();
            InitializeDB();
            InitializeGridViews();
            InitializeTextLabels();
        }


        private void InitializeDB()
        {
            LoadParentTable(connection);
            LoadChildTable(connection);

            dataSet.Relations.Add(
                "ParentChild",
                dataSet.Tables[PARENT_TABLE].Columns[PK_COLUMN],
                dataSet.Tables[CHILD_TABLE].Columns[FK_COLUMN]
                );
        }

        private void LoadParentTable(SqlConnection connection)
        {
            parentDataAdapter = new SqlDataAdapter($"SELECT * FROM {PARENT_TABLE}", connection);
            parentDataAdapter.Fill(dataSet, PARENT_TABLE);
        }

        private void LoadChildTable(SqlConnection connection)
        {
            childDataAdapter = new SqlDataAdapter($"SELECT * FROM {CHILD_TABLE}", connection);
            childDataAdapter.MissingSchemaAction = MissingSchemaAction.AddWithKey; // TODO!
            childDataAdapter.Fill(dataSet, CHILD_TABLE);
            new SqlCommandBuilder(childDataAdapter); // sets up the command builder, nothing else to be done here
        }

        private void InitializeGridViews()
        {
            InitializeDGVParent();
            InitializeDGVChild();
        }

        private void InitializeDGVParent()
        {
            parentBindingSource.DataSource = dataSet;
            parentBindingSource.DataMember = PARENT_TABLE;
            dgvParentTable.DataSource = parentBindingSource;
        }

        private void InitializeDGVChild()
        {
            childBindingSource.DataSource = parentBindingSource;
            childBindingSource.DataMember = "ParentChild";
            dgvChildTable.DataSource = childBindingSource;
        }

        private void InitializeTextLabels()
        {
            lblParentTable.Text = PARENT_TABLE;
            lblChildTable.Text = CHILD_TABLE;
        }


        private void btnPrevious_Click(object sender, EventArgs e)
        {
            try
            {
                childBindingSource.MovePrevious();

                dgvChildTable.ClearSelection();
                dgvChildTable.Rows[childBindingSource.Position].Selected = true;
            }
            catch (Exception)
            {}
        }

        private void btnNext_Click(object sender, EventArgs e)
        {
            try
            {
                childBindingSource.MoveNext();

                dgvChildTable.ClearSelection();
                dgvChildTable.Rows[childBindingSource.Position].Selected = true;
            }
            catch (Exception)
            { }
        }

        private void btnSave_Click(object sender, EventArgs e)
        {
            parentBindingSource.EndEdit();
            childBindingSource.EndEdit();

            childDataAdapter.Update(dataSet.Tables[CHILD_TABLE]); // Syncs inserts, updates, deletes
            dataSet.Tables[CHILD_TABLE].AcceptChanges();
        }
    }
}
