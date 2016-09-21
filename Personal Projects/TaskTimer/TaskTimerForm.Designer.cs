namespace TaskTimer
{
    partial class TaskTimerForm
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
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.Label div1;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(TaskTimerForm));
            this.Notify = new System.Windows.Forms.NotifyIcon(this.components);
            this.taskList = new System.Windows.Forms.ListView();
            this.columnTaskName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnTaskTime = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.addTaskBtn = new System.Windows.Forms.Button();
            this.removeTaskButton = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveProjectToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveAsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.taskName = new System.Windows.Forms.TextBox();
            this.taskTimer = new System.Windows.Forms.Timer(this.components);
            this.label1 = new System.Windows.Forms.Label();
            this.timeLabel = new System.Windows.Forms.Label();
            this.secondsBar = new System.Windows.Forms.ProgressBar();
            this.timerStartBtn = new System.Windows.Forms.Button();
            this.timerStopBtn = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.projectName = new System.Windows.Forms.TextBox();
            this.taskNameLabel = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.totalTimeLabel = new System.Windows.Forms.Label();
            this.lockTaskBtn = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.taskCntLabel = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.completedTasksLabel = new System.Windows.Forms.Label();
            div1 = new System.Windows.Forms.Label();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // div1
            // 
            div1.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            div1.Location = new System.Drawing.Point(325, 25);
            div1.Name = "div1";
            div1.Size = new System.Drawing.Size(2, 470);
            div1.TabIndex = 3;
            // 
            // Notify
            // 
            this.Notify.BalloonTipIcon = System.Windows.Forms.ToolTipIcon.Info;
            this.Notify.BalloonTipText = "Running Task Timer";
            this.Notify.BalloonTipTitle = "Task Timer";
            this.Notify.Icon = ((System.Drawing.Icon)(resources.GetObject("Notify.Icon")));
            this.Notify.Text = "Task Timer";
            this.Notify.Visible = true;
            this.Notify.Click += new System.EventHandler(this.Notify_Click);
            // 
            // taskList
            // 
            this.taskList.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnTaskName,
            this.columnTaskTime});
            this.taskList.FullRowSelect = true;
            this.taskList.GridLines = true;
            this.taskList.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.taskList.Location = new System.Drawing.Point(333, 71);
            this.taskList.MultiSelect = false;
            this.taskList.Name = "taskList";
            this.taskList.Size = new System.Drawing.Size(252, 352);
            this.taskList.TabIndex = 0;
            this.taskList.UseCompatibleStateImageBehavior = false;
            this.taskList.View = System.Windows.Forms.View.Details;
            this.taskList.ColumnWidthChanging += new System.Windows.Forms.ColumnWidthChangingEventHandler(this.taskList_ColumnWidthChanging);
            this.taskList.MouseDoubleClick += new System.Windows.Forms.MouseEventHandler(this.taskList_MouseDoubleClick);
            // 
            // columnTaskName
            // 
            this.columnTaskName.Text = "Task Name";
            this.columnTaskName.Width = 153;
            // 
            // columnTaskTime
            // 
            this.columnTaskTime.Text = "Task Time";
            this.columnTaskTime.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.columnTaskTime.Width = 74;
            // 
            // addTaskBtn
            // 
            this.addTaskBtn.Location = new System.Drawing.Point(333, 465);
            this.addTaskBtn.Name = "addTaskBtn";
            this.addTaskBtn.Size = new System.Drawing.Size(75, 23);
            this.addTaskBtn.TabIndex = 1;
            this.addTaskBtn.Text = "Add Task";
            this.addTaskBtn.UseVisualStyleBackColor = true;
            this.addTaskBtn.Click += new System.EventHandler(this.addTaskBtn_Click);
            // 
            // removeTaskButton
            // 
            this.removeTaskButton.Location = new System.Drawing.Point(501, 465);
            this.removeTaskButton.Name = "removeTaskButton";
            this.removeTaskButton.Size = new System.Drawing.Size(84, 23);
            this.removeTaskButton.TabIndex = 2;
            this.removeTaskButton.Text = "Remove Task";
            this.removeTaskButton.UseVisualStyleBackColor = true;
            this.removeTaskButton.Click += new System.EventHandler(this.removeTaskButton_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(597, 24);
            this.menuStrip1.TabIndex = 4;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newProjectToolStripMenuItem,
            this.openProjectToolStripMenuItem,
            this.saveProjectToolStripMenuItem,
            this.saveAsToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newProjectToolStripMenuItem
            // 
            this.newProjectToolStripMenuItem.Name = "newProjectToolStripMenuItem";
            this.newProjectToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.N)));
            this.newProjectToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.newProjectToolStripMenuItem.Text = "&New Project";
            this.newProjectToolStripMenuItem.Click += new System.EventHandler(this.newProjectToolStripMenuItem_Click);
            // 
            // openProjectToolStripMenuItem
            // 
            this.openProjectToolStripMenuItem.Name = "openProjectToolStripMenuItem";
            this.openProjectToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.O)));
            this.openProjectToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.openProjectToolStripMenuItem.Text = "&Open Project";
            this.openProjectToolStripMenuItem.Click += new System.EventHandler(this.openProjectToolStripMenuItem_Click);
            // 
            // saveProjectToolStripMenuItem
            // 
            this.saveProjectToolStripMenuItem.Name = "saveProjectToolStripMenuItem";
            this.saveProjectToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Control | System.Windows.Forms.Keys.S)));
            this.saveProjectToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.saveProjectToolStripMenuItem.Text = "&Save Project";
            this.saveProjectToolStripMenuItem.Click += new System.EventHandler(this.saveProjectToolStripMenuItem_Click);
            // 
            // saveAsToolStripMenuItem
            // 
            this.saveAsToolStripMenuItem.Name = "saveAsToolStripMenuItem";
            this.saveAsToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.saveAsToolStripMenuItem.Text = "Save &As";
            this.saveAsToolStripMenuItem.Click += new System.EventHandler(this.saveAsToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F4)));
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(186, 22);
            this.exitToolStripMenuItem.Text = "&Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // taskName
            // 
            this.taskName.Location = new System.Drawing.Point(335, 45);
            this.taskName.Name = "taskName";
            this.taskName.Size = new System.Drawing.Size(250, 20);
            this.taskName.TabIndex = 5;
            this.taskName.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.taskName_KeyPress);
            // 
            // taskTimer
            // 
            this.taskTimer.Interval = 1000;
            this.taskTimer.Tick += new System.EventHandler(this.taskTimer_Tick);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(335, 28);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(64, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "Active Task";
            // 
            // timeLabel
            // 
            this.timeLabel.BackColor = System.Drawing.SystemColors.Control;
            this.timeLabel.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.timeLabel.Font = new System.Drawing.Font("Verdana", 45F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.timeLabel.Location = new System.Drawing.Point(15, 146);
            this.timeLabel.Name = "timeLabel";
            this.timeLabel.Size = new System.Drawing.Size(304, 75);
            this.timeLabel.TabIndex = 7;
            this.timeLabel.Text = "00:00";
            this.timeLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // secondsBar
            // 
            this.secondsBar.Location = new System.Drawing.Point(15, 238);
            this.secondsBar.Maximum = 60;
            this.secondsBar.Name = "secondsBar";
            this.secondsBar.Size = new System.Drawing.Size(304, 23);
            this.secondsBar.Step = 1;
            this.secondsBar.TabIndex = 8;
            // 
            // timerStartBtn
            // 
            this.timerStartBtn.Enabled = false;
            this.timerStartBtn.Location = new System.Drawing.Point(48, 298);
            this.timerStartBtn.Name = "timerStartBtn";
            this.timerStartBtn.Size = new System.Drawing.Size(75, 60);
            this.timerStartBtn.TabIndex = 9;
            this.timerStartBtn.Text = "Start Timer";
            this.timerStartBtn.UseVisualStyleBackColor = true;
            this.timerStartBtn.Click += new System.EventHandler(this.timerStartBtn_Click);
            // 
            // timerStopBtn
            // 
            this.timerStopBtn.Enabled = false;
            this.timerStopBtn.Location = new System.Drawing.Point(203, 298);
            this.timerStopBtn.Name = "timerStopBtn";
            this.timerStopBtn.Size = new System.Drawing.Size(75, 60);
            this.timerStopBtn.TabIndex = 9;
            this.timerStopBtn.Text = "Stop Timer";
            this.timerStopBtn.UseVisualStyleBackColor = true;
            this.timerStopBtn.Click += new System.EventHandler(this.timerStopBtn_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 28);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(71, 13);
            this.label2.TabIndex = 10;
            this.label2.Text = "Project Name";
            // 
            // projectName
            // 
            this.projectName.Location = new System.Drawing.Point(13, 45);
            this.projectName.Name = "projectName";
            this.projectName.Size = new System.Drawing.Size(306, 20);
            this.projectName.TabIndex = 11;
            // 
            // taskNameLabel
            // 
            this.taskNameLabel.AutoEllipsis = true;
            this.taskNameLabel.Font = new System.Drawing.Font("Cambria", 24F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.taskNameLabel.Location = new System.Drawing.Point(15, 101);
            this.taskNameLabel.Name = "taskNameLabel";
            this.taskNameLabel.Size = new System.Drawing.Size(304, 35);
            this.taskNameLabel.TabIndex = 12;
            this.taskNameLabel.Text = "No Active Task";
            this.taskNameLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(333, 425);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(60, 13);
            this.label3.TabIndex = 13;
            this.label3.Text = "Total Time:";
            this.label3.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // totalTimeLabel
            // 
            this.totalTimeLabel.AutoSize = true;
            this.totalTimeLabel.Location = new System.Drawing.Point(551, 428);
            this.totalTimeLabel.Name = "totalTimeLabel";
            this.totalTimeLabel.Size = new System.Drawing.Size(34, 13);
            this.totalTimeLabel.TabIndex = 14;
            this.totalTimeLabel.Text = "00:00";
            this.totalTimeLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // lockTaskBtn
            // 
            this.lockTaskBtn.Enabled = false;
            this.lockTaskBtn.Location = new System.Drawing.Point(412, 465);
            this.lockTaskBtn.Name = "lockTaskBtn";
            this.lockTaskBtn.Size = new System.Drawing.Size(83, 23);
            this.lockTaskBtn.TabIndex = 15;
            this.lockTaskBtn.Text = "Lock Task";
            this.lockTaskBtn.UseVisualStyleBackColor = true;
            this.lockTaskBtn.Click += new System.EventHandler(this.lockTaskBtn_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(335, 447);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 13);
            this.label4.TabIndex = 16;
            this.label4.Text = "Total Tasks:";
            // 
            // taskCntLabel
            // 
            this.taskCntLabel.AutoSize = true;
            this.taskCntLabel.Location = new System.Drawing.Point(401, 447);
            this.taskCntLabel.Name = "taskCntLabel";
            this.taskCntLabel.Size = new System.Drawing.Size(13, 13);
            this.taskCntLabel.TabIndex = 17;
            this.taskCntLabel.Text = "0";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(451, 447);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(92, 13);
            this.label5.TabIndex = 18;
            this.label5.Text = "Completed Tasks:";
            // 
            // completedTasksLabel
            // 
            this.completedTasksLabel.AutoSize = true;
            this.completedTasksLabel.Location = new System.Drawing.Point(572, 447);
            this.completedTasksLabel.Name = "completedTasksLabel";
            this.completedTasksLabel.Size = new System.Drawing.Size(13, 13);
            this.completedTasksLabel.TabIndex = 19;
            this.completedTasksLabel.Text = "0";
            this.completedTasksLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // TaskTimerForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(597, 493);
            this.Controls.Add(this.completedTasksLabel);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.taskCntLabel);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.lockTaskBtn);
            this.Controls.Add(this.totalTimeLabel);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.taskNameLabel);
            this.Controls.Add(this.projectName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.timerStopBtn);
            this.Controls.Add(this.timerStartBtn);
            this.Controls.Add(this.secondsBar);
            this.Controls.Add(this.timeLabel);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.taskName);
            this.Controls.Add(div1);
            this.Controls.Add(this.removeTaskButton);
            this.Controls.Add(this.addTaskBtn);
            this.Controls.Add(this.taskList);
            this.Controls.Add(this.menuStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "TaskTimerForm";
            this.Text = "Task Timer";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.TaskTimerForm_FormClosing);
            this.Load += new System.EventHandler(this.TaskTimerForm_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NotifyIcon Notify;
        private System.Windows.Forms.ListView taskList;
        private System.Windows.Forms.Button addTaskBtn;
        private System.Windows.Forms.Button removeTaskButton;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openProjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveProjectToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.TextBox taskName;
        private System.Windows.Forms.ColumnHeader columnTaskName;
        private System.Windows.Forms.ColumnHeader columnTaskTime;
        private System.Windows.Forms.Timer taskTimer;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label timeLabel;
        private System.Windows.Forms.ProgressBar secondsBar;
        private System.Windows.Forms.Button timerStartBtn;
        private System.Windows.Forms.Button timerStopBtn;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ToolStripMenuItem newProjectToolStripMenuItem;
        private System.Windows.Forms.TextBox projectName;
        private System.Windows.Forms.Label taskNameLabel;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label totalTimeLabel;
        private System.Windows.Forms.ToolStripMenuItem saveAsToolStripMenuItem;
        private System.Windows.Forms.Button lockTaskBtn;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label taskCntLabel;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label completedTasksLabel;
    }
}