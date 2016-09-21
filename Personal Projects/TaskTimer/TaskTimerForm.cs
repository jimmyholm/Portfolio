using System;
using System.Drawing.Drawing2D;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Xml;

namespace TaskTimer
{
    public partial class TaskTimerForm : Form
    {
        private enum eStatus { STATUS_INACTIVE, STATUS_ACTIVE, STATUS_LOCKED };
        private int selectedIndex = -1;
        private bool dirty = false;
        private string filename = "";
        private ImageList il = new ImageList();
        private System.Resources.ResourceManager rm = Properties.Resources.ResourceManager;
        private void SumTime()
        {
            
            int hrs = 0;
            int mins = 0;
            foreach(ListViewItem Item in taskList.Items)
            {
                string str = Item.SubItems[1].Text;
                mins += GetMinutes(str);
                hrs += GetHours(str);
                while(mins > 60)
                {
                    hrs++;
                    mins -= 60;
                }
            }
            totalTimeLabel.Text = hrs.ToString("D2") + ":" + mins.ToString("D2");
        }

        private void ResizeColumns()
        {
            taskList.AutoResizeColumns(ColumnHeaderAutoResizeStyle.ColumnContent);
            taskList.AutoResizeColumns(ColumnHeaderAutoResizeStyle.HeaderSize);
            int w = taskList.Columns[0].Width + taskList.Columns[1].Width;
            if (w > taskList.Width)
            {
                taskList.Columns[0].Width = taskList.Columns[0].Width - (w - taskList.Width + 5);
            }
        }

        private int GetMinutes(string str)
        {
            str = str.Substring(str.IndexOf(':') + 1);
            return Convert.ToInt32(str);
        }
        private int GetHours(string str)
        {
            str = str.Substring(0, str.IndexOf(':'));

            return Convert.ToInt32(str); ;
        }

        private void AddMinute()
        {
            int mins = GetMinutes(timeLabel.Text);
            int hrs = GetHours(timeLabel.Text);
            mins += 1;
            if(mins == 60)
            {
                mins = 0;
                hrs += 1;
            }
            timeLabel.Text = hrs.ToString("D2") + ":" + mins.ToString("D2");
        }

        public DialogResult PopupInput(Control ctrl, int border, int length, ref string output)
        {

            //handle alignment
            Point ctrlpt = this.PointToScreen(ctrl.Location);
            ctrlpt.Y += 24;
            ctrlpt.X += 4;

            TextBox input = new TextBox { Height = 20, Width = length, Top = border / 2, Left = border / 2 };
            input.BorderStyle = BorderStyle.FixedSingle;
            //######## SetColor to your preference
            input.BackColor = Color.Azure;

            Button btnok = new Button { DialogResult = System.Windows.Forms.DialogResult.OK, Top = 25 };
            Button btncn = new Button { DialogResult = System.Windows.Forms.DialogResult.Cancel, Top = 25 };

            Form frm = new Form { ControlBox = false, AcceptButton = btnok, CancelButton = btncn, StartPosition = FormStartPosition.Manual, Location = ctrlpt };
            frm.FormBorderStyle = System.Windows.Forms.FormBorderStyle.None;
            //######## SetColor to your preference
            frm.BackColor = Color.Navy;

            RectangleF rec = new RectangleF(0, 0, (length + border), (20 + border));
            GraphicsPath GP = new GraphicsPath(); //GetRoundedRect(rec, 4.0F);
            float diameter = 8.0F;
            SizeF sizef = new SizeF(diameter, diameter);
            RectangleF arc = new RectangleF(rec.Location, sizef);
            GP.AddArc(arc, 180, 90);
            arc.X = rec.Right - diameter;
            GP.AddArc(arc, 270, 90);
            arc.Y = rec.Bottom - diameter;
            GP.AddArc(arc, 0, 90);
            arc.X = rec.Left;
            GP.AddArc(arc, 90, 90);
            GP.CloseFigure();

            frm.Region = new Region(GP);
            frm.Controls.AddRange(new Control[] { input, btncn, btnok });
            DialogResult rst = frm.ShowDialog();
            output = input.Text;
            return rst;
        }


        public TaskTimerForm()
        {
            InitializeComponent();
            il.Images.Add("Inactive",   (Image)rm.GetObject("inactive"  ));
            il.Images.Add("Active",     (Image)rm.GetObject("active"    ));
            il.Images.Add("Complete",   (Image)rm.GetObject("complete"  ));
            taskList.SmallImageList = il;
        }

        private void TaskTimerForm_Load(object sender, EventArgs e)
        {
            //ResizeColumns();
            Notify.Visible = true;
        }

        private void addTaskBtn_Click(object sender, EventArgs e)
        {
            string name = "";
            if(PopupInput(addTaskBtn, 4, 75, ref name) == System.Windows.Forms.DialogResult.OK)
            {
                if (taskList.FindItemWithText(name) == null && name != "")
                {
                    selectedIndex = taskList.Items.Count;
                    ListViewItem newItem = new ListViewItem(name); newItem.SubItems.Add("00:00");
                    taskList.Items.Add(newItem);
                    taskName.Text = name;
                    //ResizeColumns();
                    timerStartBtn.Enabled = true;
                    timerStopBtn.Enabled = false;
                    secondsBar.Value = 0;
                    taskNameLabel.Text = name;
                    dirty = true;
                    countTasks();
                }
            }
        }

        private void taskList_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (taskList.SelectedItems.Count == 1)
            {
                if(selectedIndex != -1)
                {
                    if (taskList.Items[selectedIndex].ImageKey != "Complete")
                        taskList.Items[selectedIndex].ImageKey = "Inactive";
                }
                selectedIndex = taskList.SelectedItems[0].Index;
                taskName.Text = taskList.SelectedItems[0].Text;
                if (taskList.Items[selectedIndex].ImageKey != "Complete")
                {
                    timerStartBtn.Enabled = true;
                    lockTaskBtn.Text = "Lock Task";
                    lockTaskBtn.Enabled = true;
                }
                else
                {
                    timerStartBtn.Enabled = false;
                    lockTaskBtn.Text = "Unlock Task";
                    lockTaskBtn.Enabled = true;
                }
                timerStopBtn.Enabled = false;
                secondsBar.Value = 0;
                taskTimer.Stop();
                timeLabel.Text = taskList.SelectedItems[0].SubItems[1].Text;
                taskNameLabel.Text = taskList.SelectedItems[0].SubItems[0].Text;
            }
        }

        private void removeTaskButton_Click(object sender, EventArgs e)
        {
            if (taskList.SelectedItems.Count != 0)
            {
                if (selectedIndex == taskList.SelectedIndices[0])
                {
                    taskName.Text = "";
                    selectedIndex = -1;
                    timerStartBtn.Enabled = false;
                    timerStopBtn.Enabled = false;
                    lockTaskBtn.Text = "Lock Task";
                    lockTaskBtn.Enabled = false;
                    taskTimer.Stop();
                    secondsBar.Value = 0;
                    timeLabel.Text = "00:00";
                    taskNameLabel.Text = "No Active Task";
                }
                dirty = true;
                taskList.Items.RemoveAt(taskList.SelectedIndices[0]);
            }
        }

        private void taskName_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar == Convert.ToChar(Keys.Enter))
            {
                taskList.Items[selectedIndex].Text = ((TextBox)sender).Text;
                dirty = true;
            }
        }

        private void taskList_ColumnWidthChanging(object sender, ColumnWidthChangingEventArgs e)
        {
            e.Cancel = true;
            e.NewWidth = taskList.Columns[e.ColumnIndex].Width;
        }

        private void taskTimer_Tick(object sender, EventArgs e)
        {
            dirty = true;
            secondsBar.PerformStep();
            if (secondsBar.Value == 60)
            {
                AddMinute();
                secondsBar.Value = 0;
                if(selectedIndex != -1)
                {
                    taskList.Items[selectedIndex].SubItems[1].Text = timeLabel.Text;
                }
            }
            SumTime();
        }

        private void timerStartBtn_Click(object sender, EventArgs e)
        {
            taskTimer.Start();
            taskList.Items[selectedIndex].ImageKey = "Active";
            timerStartBtn.Enabled = false;
            timerStopBtn.Enabled = true;
        }

        private void timerStopBtn_Click(object sender, EventArgs e)
        {
            taskTimer.Stop();
            taskList.Items[selectedIndex].ImageKey = "Inactive";
            timerStartBtn.Enabled = true;
            timerStopBtn.Enabled = false;
        }

        private void WriteXML()
        {
            XmlWriter writer = XmlWriter.Create(filename);
            writer.WriteStartDocument();
            writer.WriteWhitespace("\n");
            writer.WriteStartElement("TimeProject");
            writer.WriteStartAttribute("Name");
            writer.WriteString(projectName.Text);
            writer.WriteEndAttribute();
            writer.WriteWhitespace("\n");
            foreach(ListViewItem Item in taskList.Items)
            {
                writer.WriteWhitespace("\t");
                writer.WriteStartElement("Task");
                writer.WriteWhitespace("\n");
                writer.WriteWhitespace("\t\t");
                writer.WriteStartElement("Name");
                writer.WriteString(Item.SubItems[0].Text);
                writer.WriteEndElement();
                writer.WriteWhitespace("\n");
                writer.WriteWhitespace("\t\t");
                writer.WriteStartElement("Time");
                writer.WriteString(Item.SubItems[1].Text);
                writer.WriteEndElement();
                writer.WriteWhitespace("\n");
                writer.WriteWhitespace("\t\t");
                writer.WriteStartElement("Status");
                writer.WriteString( (Item.ImageKey == "Complete") ? "2" : "0" );
                writer.WriteEndElement();
                writer.WriteWhitespace("\n");
                writer.WriteWhitespace("\t");
                writer.WriteEndElement();
                writer.WriteWhitespace("\n");
            }
            writer.WriteEndElement();
            writer.WriteEndDocument();
            writer.Flush();
            writer.Close();
        }

        private void NewProject()
        {
            if(dirty)
            {
                DialogResult res = MessageBox.Show("Would you like to save the current project before closing?", "Unsaved Changes", MessageBoxButtons.YesNoCancel);
                if (res == DialogResult.Yes)
                {
                    Save();
                }
                else if (res == DialogResult.Cancel)
                {
                    return;
                }
            }
            projectName.Text = "";
            filename = "";
            dirty = false;
            taskList.Items.Clear();
            taskName.Text = "";
            taskNameLabel.Text = "No Active Task";
            timeLabel.Text = "00:00";
            timerStartBtn.Enabled = false;
            timerStopBtn.Enabled = false;
            taskTimer.Stop();
        }

        private void XMLRead()
        {
            XmlDocument document = new XmlDocument();
            document.Load(filename);
            string name = "";
            string time = "";
            eStatus status = eStatus.STATUS_INACTIVE;
            int firstNode = -1;
            if (document.FirstChild.NodeType == XmlNodeType.XmlDeclaration)
                firstNode = 1;
            else
                firstNode = 0;
            if(document.ChildNodes[firstNode].Name != "TimeProject")
            {
                MessageBox.Show("Not a valid time project!", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                NewProject();
                return;
            }
            projectName.Text = document.ChildNodes[firstNode].Attributes[0].Value;
            foreach (XmlNode node in document.ChildNodes[firstNode].ChildNodes)
            {
                if (node.ChildNodes.Count == 2)
                {
                    if (node.FirstChild.Name == "Name")
                    {
                        name = node.ChildNodes[0].InnerText;
                        time = node.ChildNodes[1].InnerText;
                        status = eStatus.STATUS_INACTIVE;
                    }
                    else if (node.FirstChild.Name == "Time")
                    {
                        name = node.ChildNodes[1].InnerText;
                        time = node.ChildNodes[0].InnerText;
                        status = eStatus.STATUS_INACTIVE;
                    }
                }
                else if(node.ChildNodes.Count == 3)
                {
                    int index = 0;
                    while(index != 3)
                    {
                        if (node.ChildNodes[index].Name == "Name")
                            name = node.ChildNodes[index].InnerText;
                        else if (node.ChildNodes[index].Name == "Time")
                            time = node.ChildNodes[index].InnerText;
                        else if(node.ChildNodes[index].Name == "Status")
                            switch(node.ChildNodes[index].InnerText)
                            {
                                case "0":
                                    status = eStatus.STATUS_INACTIVE;
                                    break;
                                case "1":
                                    status = eStatus.STATUS_ACTIVE;
                                    break;
                                case "2":
                                    status = eStatus.STATUS_LOCKED;
                                    break;
                                default:
                                    MessageBox.Show("Not a valid time project!", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    NewProject();
                                    return;
                            }
                        index++;
                    }
                }
                else
                {
                    MessageBox.Show("Not a valid time project!", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    NewProject();
                    return;
                }
                ListViewItem item = new ListViewItem(name); item.SubItems.Add(time);
                setImage(item, status);
                taskList.Items.Add(item);
                
            }
        }

        private void countTasks()
        {
            int cnt = 0;
            foreach(ListViewItem Item in taskList.Items)
            {
                if (Item.ImageKey == "Complete")
                    ++cnt;
            }
            taskCntLabel.Text = taskList.Items.Count.ToString();
            completedTasksLabel.Text = cnt.ToString();
        }

        private void setImage(ListViewItem item, eStatus status)
        {
            switch(status)
            {
                case eStatus.STATUS_INACTIVE:
                    item.ImageKey = "Inactive";
                    break;
                case eStatus.STATUS_ACTIVE:
                    item.ImageKey = "Active";
                    break;
                case eStatus.STATUS_LOCKED:
                    item.ImageKey = "Complete";
                    break;
            }
        }

        private void Open()
        {
            OpenFileDialog diag = new OpenFileDialog();
            diag.Filter = "Time Project File|*.xml";
            diag.Title = "Open Timing Project";
            diag.ShowDialog();
            if (diag.FileName == "")
                return;
            NewProject();
            filename = diag.FileName;
            XMLRead();
            dirty = false;
            SumTime();
            countTasks();
        }

        private void SaveAs()
        {
            SaveFileDialog diag = new SaveFileDialog();
            diag.Filter = "Time Project File|*.xml";
            diag.Title = "Save Timing Project";
            diag.ShowDialog();
            if (diag.FileName == "")
                return;
            filename = diag.FileName;
            WriteXML();
            dirty = false;
        }

        private void Save()
        {
            if(filename == "")
            {
                SaveFileDialog diag = new SaveFileDialog();
                diag.Filter = "Time Project File|*.xml";
                diag.Title = "Save Timing Project";
                diag.ShowDialog();
                if (diag.FileName == "")
                    return;
                filename = diag.FileName;
            }
            WriteXML();
            dirty = false;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            Close();
        }

        private void saveProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Save();
        }

        private void openProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Open();
        }

        private void newProjectToolStripMenuItem_Click(object sender, EventArgs e)
        {
            NewProject();
        }

        private void Notify_Click(object sender, EventArgs e)
        {
            Notify.BalloonTipTitle = "Task Timer";
            if (selectedIndex == -1)
                Notify.BalloonTipText = "No active task selected";
            else
                Notify.BalloonTipText = taskList.Items[selectedIndex].SubItems[0].Text + ": " + taskList.Items[selectedIndex].SubItems[1].Text;
            Notify.ShowBalloonTip(200);
        }

        private void TaskTimerForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            DialogResult res;
            if (dirty)
            {
                res = MessageBox.Show("Would you like to save the current project before closing?", "Unsaved Changes", MessageBoxButtons.YesNoCancel);
                if (res == DialogResult.Yes)
                {
                    Save();
                }
                else if (res == DialogResult.Cancel)
                {
                    e.Cancel = true;
                }
                dirty = false;
            }
            Notify.Visible = false;
            NewProject();
            
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveAs();
        }

        private void lockTaskBtn_Click(object sender, EventArgs e)
        {
            if( ((Button)sender).Text == "Lock Task" && selectedIndex != -1)
            {
                taskList.Items[selectedIndex].ImageKey = "Complete";
                ((Button)sender).Text = "Unlock Task";
                taskTimer.Stop();
                timerStopBtn.Enabled = false;
                timerStartBtn.Enabled = false;
            }
            else if (((Button)sender).Text == "Unlock Task" && selectedIndex != -1)
            {
                taskList.Items[selectedIndex].ImageKey = "Inactive";
                ((Button)sender).Text = "Lock Task";
                timerStopBtn.Enabled = false;
                timerStartBtn.Enabled = true;
            }
            countTasks();
                
        }


    }
}
