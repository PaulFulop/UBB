namespace Tournament
{
    partial class Form1
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            dgvCourts = new DataGridView();
            dgvMatches = new DataGridView();
            btnSave = new Button();
            label1 = new Label();
            label2 = new Label();
            ((System.ComponentModel.ISupportInitialize)dgvCourts).BeginInit();
            ((System.ComponentModel.ISupportInitialize)dgvMatches).BeginInit();
            SuspendLayout();
            // 
            // dgvCourts
            // 
            dgvCourts.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvCourts.Location = new Point(12, 85);
            dgvCourts.Name = "dgvCourts";
            dgvCourts.Size = new Size(438, 253);
            dgvCourts.TabIndex = 0;
            // 
            // dgvMatches
            // 
            dgvMatches.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            dgvMatches.Location = new Point(514, 85);
            dgvMatches.Name = "dgvMatches";
            dgvMatches.Size = new Size(438, 253);
            dgvMatches.TabIndex = 1;
            // 
            // btnSave
            // 
            btnSave.Location = new Point(619, 358);
            btnSave.Name = "btnSave";
            btnSave.Size = new Size(202, 23);
            btnSave.TabIndex = 2;
            btnSave.Text = "Save";
            btnSave.UseVisualStyleBackColor = true;
            btnSave.Click += btnSave_Click;
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new Point(18, 51);
            label1.Name = "label1";
            label1.Size = new Size(42, 15);
            label1.TabIndex = 3;
            label1.Text = "Courts";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new Point(514, 51);
            label2.Name = "label2";
            label2.Size = new Size(52, 15);
            label2.TabIndex = 4;
            label2.Text = "Matches";
            // 
            // Form1
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(1011, 512);
            Controls.Add(label2);
            Controls.Add(label1);
            Controls.Add(btnSave);
            Controls.Add(dgvMatches);
            Controls.Add(dgvCourts);
            Name = "Form1";
            Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)dgvCourts).EndInit();
            ((System.ComponentModel.ISupportInitialize)dgvMatches).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private DataGridView dgvCourts;
        private DataGridView dgvMatches;
        private Button btnSave;
        private Label label1;
        private Label label2;
    }
}
