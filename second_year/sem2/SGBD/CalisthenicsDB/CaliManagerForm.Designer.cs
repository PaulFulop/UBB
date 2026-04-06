namespace CalisthenicsDB
{
    partial class CalistenicsForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
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
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.dgvParentTable = new System.Windows.Forms.DataGridView();
            this.dgvChildTable = new System.Windows.Forms.DataGridView();
            this.btnPrevious = new System.Windows.Forms.Button();
            this.btnNext = new System.Windows.Forms.Button();
            this.btnSave = new System.Windows.Forms.Button();
            this.lblParentTable = new System.Windows.Forms.Label();
            this.lblChildTable = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dgvParentTable)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvChildTable)).BeginInit();
            this.SuspendLayout();
            // 
            // dgvParentTable
            // 
            this.dgvParentTable.BackgroundColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.dgvParentTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvParentTable.GridColor = System.Drawing.Color.Silver;
            this.dgvParentTable.Location = new System.Drawing.Point(29, 68);
            this.dgvParentTable.Name = "dgvParentTable";
            this.dgvParentTable.Size = new System.Drawing.Size(667, 495);
            this.dgvParentTable.TabIndex = 2;
            // 
            // dgvChildTable
            // 
            this.dgvChildTable.BackgroundColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.dgvChildTable.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgvChildTable.GridColor = System.Drawing.Color.Silver;
            this.dgvChildTable.Location = new System.Drawing.Point(702, 68);
            this.dgvChildTable.Name = "dgvChildTable";
            this.dgvChildTable.Size = new System.Drawing.Size(523, 456);
            this.dgvChildTable.TabIndex = 4;
            // 
            // btnPrevious
            // 
            this.btnPrevious.BackColor = System.Drawing.Color.DimGray;
            this.btnPrevious.FlatAppearance.BorderSize = 0;
            this.btnPrevious.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnPrevious.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.btnPrevious.Location = new System.Drawing.Point(702, 530);
            this.btnPrevious.Name = "btnPrevious";
            this.btnPrevious.Size = new System.Drawing.Size(100, 33);
            this.btnPrevious.TabIndex = 5;
            this.btnPrevious.Text = "Previous";
            this.btnPrevious.UseVisualStyleBackColor = false;
            this.btnPrevious.Click += new System.EventHandler(this.btnPrevious_Click);
            // 
            // btnNext
            // 
            this.btnNext.BackColor = System.Drawing.Color.DimGray;
            this.btnNext.FlatAppearance.BorderSize = 0;
            this.btnNext.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnNext.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.btnNext.Location = new System.Drawing.Point(808, 530);
            this.btnNext.Name = "btnNext";
            this.btnNext.Size = new System.Drawing.Size(104, 33);
            this.btnNext.TabIndex = 6;
            this.btnNext.Text = "Next";
            this.btnNext.UseVisualStyleBackColor = false;
            this.btnNext.Click += new System.EventHandler(this.btnNext_Click);
            // 
            // btnSave
            // 
            this.btnSave.BackColor = System.Drawing.Color.DimGray;
            this.btnSave.FlatAppearance.BorderSize = 0;
            this.btnSave.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.btnSave.ForeColor = System.Drawing.SystemColors.ButtonFace;
            this.btnSave.Location = new System.Drawing.Point(918, 530);
            this.btnSave.Name = "btnSave";
            this.btnSave.Size = new System.Drawing.Size(307, 33);
            this.btnSave.TabIndex = 25;
            this.btnSave.Text = "Save Changes";
            this.btnSave.UseVisualStyleBackColor = false;
            this.btnSave.Click += new System.EventHandler(this.btnSave_Click);
            // 
            // lblParentTable
            // 
            this.lblParentTable.AutoSize = true;
            this.lblParentTable.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblParentTable.Location = new System.Drawing.Point(29, 28);
            this.lblParentTable.Name = "lblParentTable";
            this.lblParentTable.Size = new System.Drawing.Size(70, 25);
            this.lblParentTable.TabIndex = 26;
            this.lblParentTable.Text = "label1";
            // 
            // lblChildTable
            // 
            this.lblChildTable.AutoSize = true;
            this.lblChildTable.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lblChildTable.Location = new System.Drawing.Point(697, 28);
            this.lblChildTable.Name = "lblChildTable";
            this.lblChildTable.Size = new System.Drawing.Size(70, 25);
            this.lblChildTable.TabIndex = 27;
            this.lblChildTable.Text = "label1";
            // 
            // CalistenicsForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(64)))), ((int)(((byte)(64)))), ((int)(((byte)(64)))));
            this.ClientSize = new System.Drawing.Size(1237, 575);
            this.Controls.Add(this.lblChildTable);
            this.Controls.Add(this.lblParentTable);
            this.Controls.Add(this.btnSave);
            this.Controls.Add(this.btnNext);
            this.Controls.Add(this.btnPrevious);
            this.Controls.Add(this.dgvChildTable);
            this.Controls.Add(this.dgvParentTable);
            this.Name = "CalistenicsForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Cali Manager";
            ((System.ComponentModel.ISupportInitialize)(this.dgvParentTable)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.dgvChildTable)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.DataGridView dgvParentTable;
        private System.Windows.Forms.DataGridView dgvChildTable;
        private System.Windows.Forms.Button btnPrevious;
        private System.Windows.Forms.Button btnNext;
        private System.Windows.Forms.Button btnSave;
        private System.Windows.Forms.Label lblParentTable;
        private System.Windows.Forms.Label lblChildTable;
    }
}

