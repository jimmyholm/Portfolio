namespace Picross
{
    partial class Form1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.label1 = new System.Windows.Forms.Label();
            this.columnUpDown = new System.Windows.Forms.NumericUpDown();
            this.rowUpDown = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.selectSolution = new System.Windows.Forms.RadioButton();
            this.selectColor = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.selectCol5 = new System.Windows.Forms.RadioButton();
            this.selectCol4 = new System.Windows.Forms.RadioButton();
            this.selectCol3 = new System.Windows.Forms.RadioButton();
            this.selectCol2 = new System.Windows.Forms.RadioButton();
            this.selectCol1 = new System.Windows.Forms.RadioButton();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.picrossDisplay1 = new Picross.PicrossDisplay();
            this.colorSelection5 = new Picross.ColorSelection();
            this.colorSelection4 = new Picross.ColorSelection();
            this.colorSelection3 = new Picross.ColorSelection();
            this.colorSelection2 = new Picross.ColorSelection();
            this.colorSelection1 = new Picross.ColorSelection();
            this.picrossGrid = new Picross.PicrossGrid();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.columnUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.rowUpDown)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(784, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newToolStripMenuItem,
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // newToolStripMenuItem
            // 
            this.newToolStripMenuItem.Name = "newToolStripMenuItem";
            this.newToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.newToolStripMenuItem.Text = "&New";
            this.newToolStripMenuItem.Click += new System.EventHandler(this.newToolStripMenuItem_Click);
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.openToolStripMenuItem.Text = "&Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.saveToolStripMenuItem.Text = "&Save";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(114, 22);
            this.exitToolStripMenuItem.Text = "&Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.aboutToolStripMenuItem.Text = "&About";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.aboutToolStripMenuItem_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 172);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(73, 13);
            this.label1.TabIndex = 3;
            this.label1.Text = "Column Count";
            // 
            // columnUpDown
            // 
            this.columnUpDown.Location = new System.Drawing.Point(9, 189);
            this.columnUpDown.Name = "columnUpDown";
            this.columnUpDown.Size = new System.Drawing.Size(70, 20);
            this.columnUpDown.TabIndex = 4;
            this.columnUpDown.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.columnUpDown.ValueChanged += new System.EventHandler(this.columnUpDown_ValueChanged);
            // 
            // rowUpDown
            // 
            this.rowUpDown.Location = new System.Drawing.Point(87, 189);
            this.rowUpDown.Name = "rowUpDown";
            this.rowUpDown.Size = new System.Drawing.Size(70, 20);
            this.rowUpDown.TabIndex = 6;
            this.rowUpDown.Value = new decimal(new int[] {
            5,
            0,
            0,
            0});
            this.rowUpDown.ValueChanged += new System.EventHandler(this.rowUpDown_ValueChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(91, 172);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(60, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Row Count";
            // 
            // selectSolution
            // 
            this.selectSolution.AutoSize = true;
            this.selectSolution.Checked = true;
            this.selectSolution.Location = new System.Drawing.Point(16, 215);
            this.selectSolution.Name = "selectSolution";
            this.selectSolution.Size = new System.Drawing.Size(63, 17);
            this.selectSolution.TabIndex = 7;
            this.selectSolution.TabStop = true;
            this.selectSolution.Text = "Solution";
            this.selectSolution.UseVisualStyleBackColor = true;
            // 
            // selectColor
            // 
            this.selectColor.AutoSize = true;
            this.selectColor.Location = new System.Drawing.Point(89, 215);
            this.selectColor.Name = "selectColor";
            this.selectColor.Size = new System.Drawing.Size(62, 17);
            this.selectColor.TabIndex = 8;
            this.selectColor.Text = "Colorize";
            this.selectColor.UseVisualStyleBackColor = true;
            this.selectColor.CheckedChanged += new System.EventHandler(this.selectColor_CheckedChanged);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.colorSelection5);
            this.groupBox1.Controls.Add(this.colorSelection4);
            this.groupBox1.Controls.Add(this.colorSelection3);
            this.groupBox1.Controls.Add(this.colorSelection2);
            this.groupBox1.Controls.Add(this.colorSelection1);
            this.groupBox1.Controls.Add(this.selectCol5);
            this.groupBox1.Controls.Add(this.selectCol4);
            this.groupBox1.Controls.Add(this.selectCol3);
            this.groupBox1.Controls.Add(this.selectCol2);
            this.groupBox1.Controls.Add(this.selectCol1);
            this.groupBox1.Location = new System.Drawing.Point(9, 252);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(148, 220);
            this.groupBox1.TabIndex = 9;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Color Selections";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(62, 33);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(65, 13);
            this.label3.TabIndex = 10;
            this.label3.Text = "Background";
            // 
            // selectCol5
            // 
            this.selectCol5.AutoSize = true;
            this.selectCol5.Enabled = false;
            this.selectCol5.Location = new System.Drawing.Point(7, 162);
            this.selectCol5.Name = "selectCol5";
            this.selectCol5.Size = new System.Drawing.Size(14, 13);
            this.selectCol5.TabIndex = 4;
            this.selectCol5.UseVisualStyleBackColor = true;
            // 
            // selectCol4
            // 
            this.selectCol4.AutoSize = true;
            this.selectCol4.Enabled = false;
            this.selectCol4.Location = new System.Drawing.Point(7, 129);
            this.selectCol4.Name = "selectCol4";
            this.selectCol4.Size = new System.Drawing.Size(14, 13);
            this.selectCol4.TabIndex = 3;
            this.selectCol4.UseVisualStyleBackColor = true;
            // 
            // selectCol3
            // 
            this.selectCol3.AutoSize = true;
            this.selectCol3.Enabled = false;
            this.selectCol3.Location = new System.Drawing.Point(7, 97);
            this.selectCol3.Name = "selectCol3";
            this.selectCol3.Size = new System.Drawing.Size(14, 13);
            this.selectCol3.TabIndex = 2;
            this.selectCol3.UseVisualStyleBackColor = true;
            // 
            // selectCol2
            // 
            this.selectCol2.AutoSize = true;
            this.selectCol2.Enabled = false;
            this.selectCol2.Location = new System.Drawing.Point(7, 65);
            this.selectCol2.Name = "selectCol2";
            this.selectCol2.Size = new System.Drawing.Size(14, 13);
            this.selectCol2.TabIndex = 1;
            this.selectCol2.UseVisualStyleBackColor = true;
            // 
            // selectCol1
            // 
            this.selectCol1.AutoSize = true;
            this.selectCol1.Checked = true;
            this.selectCol1.Enabled = false;
            this.selectCol1.Location = new System.Drawing.Point(7, 33);
            this.selectCol1.Name = "selectCol1";
            this.selectCol1.Size = new System.Drawing.Size(14, 13);
            this.selectCol1.TabIndex = 0;
            this.selectCol1.TabStop = true;
            this.selectCol1.UseVisualStyleBackColor = true;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 167F));
            this.tableLayoutPanel1.Controls.Add(this.groupBox2, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.picrossGrid, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 24);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(784, 538);
            this.tableLayoutPanel1.TabIndex = 11;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.picrossDisplay1);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.groupBox1);
            this.groupBox2.Controls.Add(this.columnUpDown);
            this.groupBox2.Controls.Add(this.selectColor);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.selectSolution);
            this.groupBox2.Controls.Add(this.rowUpDown);
            this.groupBox2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.groupBox2.Location = new System.Drawing.Point(620, 3);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(161, 532);
            this.groupBox2.TabIndex = 12;
            this.groupBox2.TabStop = false;
            // 
            // picrossDisplay1
            // 
            this.picrossDisplay1.Location = new System.Drawing.Point(1, 9);
            this.picrossDisplay1.Name = "picrossDisplay1";
            this.picrossDisplay1.Size = new System.Drawing.Size(150, 150);
            this.picrossDisplay1.TabIndex = 10;
            // 
            // colorSelection5
            // 
            this.colorSelection5.Color = System.Drawing.Color.White;
            this.colorSelection5.Enabled = false;
            this.colorSelection5.Location = new System.Drawing.Point(27, 152);
            this.colorSelection5.Name = "colorSelection5";
            this.colorSelection5.Size = new System.Drawing.Size(37, 32);
            this.colorSelection5.TabIndex = 9;
            this.colorSelection5.OnColorSelection += new Picross.ColorSelected(this.colorSelection5_OnColorSelection);
            // 
            // colorSelection4
            // 
            this.colorSelection4.Color = System.Drawing.Color.White;
            this.colorSelection4.Enabled = false;
            this.colorSelection4.Location = new System.Drawing.Point(27, 120);
            this.colorSelection4.Name = "colorSelection4";
            this.colorSelection4.Size = new System.Drawing.Size(37, 32);
            this.colorSelection4.TabIndex = 8;
            this.colorSelection4.OnColorSelection += new Picross.ColorSelected(this.colorSelection4_OnColorSelection);
            // 
            // colorSelection3
            // 
            this.colorSelection3.Color = System.Drawing.Color.White;
            this.colorSelection3.Enabled = false;
            this.colorSelection3.Location = new System.Drawing.Point(27, 88);
            this.colorSelection3.Name = "colorSelection3";
            this.colorSelection3.Size = new System.Drawing.Size(37, 32);
            this.colorSelection3.TabIndex = 7;
            this.colorSelection3.OnColorSelection += new Picross.ColorSelected(this.colorSelection3_OnColorSelection);
            // 
            // colorSelection2
            // 
            this.colorSelection2.Color = System.Drawing.Color.White;
            this.colorSelection2.Enabled = false;
            this.colorSelection2.Location = new System.Drawing.Point(27, 56);
            this.colorSelection2.Name = "colorSelection2";
            this.colorSelection2.Size = new System.Drawing.Size(37, 32);
            this.colorSelection2.TabIndex = 6;
            this.colorSelection2.OnColorSelection += new Picross.ColorSelected(this.colorSelection2_OnColorSelection);
            // 
            // colorSelection1
            // 
            this.colorSelection1.Color = System.Drawing.Color.White;
            this.colorSelection1.Enabled = false;
            this.colorSelection1.Location = new System.Drawing.Point(27, 24);
            this.colorSelection1.Name = "colorSelection1";
            this.colorSelection1.Size = new System.Drawing.Size(37, 32);
            this.colorSelection1.TabIndex = 5;
            this.colorSelection1.OnColorSelection += new Picross.ColorSelected(this.colorSelection1_OnColorSelection);
            // 
            // picrossGrid
            // 
            this.picrossGrid.ColumnCount = 5;
            this.picrossGrid.Dock = System.Windows.Forms.DockStyle.Fill;
            this.picrossGrid.Location = new System.Drawing.Point(3, 3);
            this.picrossGrid.Name = "picrossGrid";
            this.picrossGrid.RowCount = 5;
            this.picrossGrid.Size = new System.Drawing.Size(611, 532);
            this.picrossGrid.TabIndex = 2;
            this.picrossGrid.Click += new System.EventHandler(this.picrossGrid_Click);
            this.picrossGrid.MouseDown += new System.Windows.Forms.MouseEventHandler(this.picrossGrid_MouseDown);
            this.picrossGrid.MouseMove += new System.Windows.Forms.MouseEventHandler(this.picrossGrid_MouseMove);
            this.picrossGrid.MouseUp += new System.Windows.Forms.MouseEventHandler(this.picrossGrid_MouseUp);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 562);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.MinimumSize = new System.Drawing.Size(800, 600);
            this.Name = "Form1";
            this.Text = "Picross Editor";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.columnUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.rowUpDown)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuStrip1;
        private PicrossGrid picrossGrid;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown columnUpDown;
        private System.Windows.Forms.NumericUpDown rowUpDown;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.RadioButton selectSolution;
        private System.Windows.Forms.RadioButton selectColor;
        private System.Windows.Forms.GroupBox groupBox1;
        private ColorSelection colorSelection5;
        private ColorSelection colorSelection4;
        private ColorSelection colorSelection3;
        private ColorSelection colorSelection2;
        private ColorSelection colorSelection1;
        private System.Windows.Forms.RadioButton selectCol5;
        private System.Windows.Forms.RadioButton selectCol4;
        private System.Windows.Forms.RadioButton selectCol3;
        private System.Windows.Forms.RadioButton selectCol2;
        private System.Windows.Forms.RadioButton selectCol1;
        private System.Windows.Forms.Label label3;
        private PicrossDisplay picrossDisplay1;
        private System.Windows.Forms.ToolStripMenuItem newToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.GroupBox groupBox2;
    }
}

