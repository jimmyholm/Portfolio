using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Xml;
using System.Threading.Tasks;
using System.Windows.Forms;

// Picross Editor
// 2016 Jimmy Holm
// Editor software for nonogram puzzles (picross)

namespace Picross
{
    public partial class Form1 : Form
    {
        private PicrossData data = new PicrossData();
        public PicrossData Data
        {
            get
            {
                return data;
            }

        }

        // Store the last save file name (to avoid having to show the save file-dialog every time the user wants to save.)
        private string PrevSaveName = null;
        // Allow the user to fill cells by dragging with the mouse over the grid.
        int lastX = -1;
        int lastY = -1;
        bool down = false;
        bool move = false;
        // Whenever dragging over the grid, only change cells with the same content as the first cell clicked.
        PicrossData.PicrossState firstState = PicrossData.PicrossState.Unfilled;
        // Same for color as for state
        UInt32 firstColor = 0;

        public Form1()
        {
            InitializeComponent();
            columnUpDown.Value = picrossGrid.ColumnCount;
            rowUpDown.Value = picrossGrid.RowCount;
        }

        // Handle changing the dimensions of the picross grid
        private void columnUpDown_ValueChanged(object sender, EventArgs e)
        {
            if (columnUpDown.Value < 1)
                columnUpDown.Value = 1;
            PicrossDataSingleton.Instance.ColumnCount = (int)columnUpDown.Value;
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }

        private void rowUpDown_ValueChanged(object sender, EventArgs e)
        {
            if (rowUpDown.Value < 1)
                rowUpDown.Value = 1;
            PicrossDataSingleton.Instance.RowCount = (int)rowUpDown.Value;
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            this.Close();
 
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (PicrossDataSingleton.Instance.Dirty)
                if (!AskDiscard())
                    e.Cancel = true;
        }
        // Save the file to disk, using the stored filename if available or by opening the save file dialog.
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (PicrossDataSingleton.Instance.Dirty)
            {
                if (PrevSaveName == null)
                    SaveAs();
                else
                    Save(PrevSaveName);
            }
        }

        // Ask the user to discard changes.
        private bool AskDiscard()
        {
            return (MessageBox.Show("There are unsaved changes that will be lost, continue anyway?", "Unsaved Changes", MessageBoxButtons.YesNo) == DialogResult.Yes);
        }

        // Display save file dialog and grab the filename (and path) of selected file.
        private void SaveAs()
        {
            SaveFileDialog FileSelector = new SaveFileDialog();
            FileSelector.AddExtension = true;
            FileSelector.DefaultExt = ".xml";
            FileSelector.OverwritePrompt = true;
            FileSelector.Title = "Save Picross Data";
            FileSelector.Filter = "Picross Data File|*.xml";
            DialogResult res = FileSelector.ShowDialog();
            if (res == DialogResult.OK)
            {
                Save(FileSelector.FileName);
            }
        }

        // Store the picross puzzle data to a XML file
        // XML file example layout:
        // <PicrossData Columns="3" Rows="3">
        // <SolutionData FilledCells="1 2 4 5" /> Store which cells are marked in the solution
        // <ColorData CellColors="0 1 1 2 2 2 1 0 1"> Store the entries into the 5-color palette for each cell
        // <Color ARGB="-1" />  Palette color 0 (Background)
        // <Color ARGB="-1" />  Palette color 1
        // <Color ARGB="-1" />  Palette color 2
        // <Color ARGB="-1" />  Palette color 3
        // <Color ARGB="-1" />  Palette color 4
        // </ColorData>
        // </PicrossData>
        private void Save(string Filename)
        {
            XmlWriterSettings settings = new XmlWriterSettings();
            settings.Indent = true;
            System.IO.FileStream stream = new System.IO.FileStream(Filename, System.IO.FileMode.Create);
            using (XmlWriter Writer = XmlWriter.Create(stream))
            {
                Writer.WriteStartDocument();
                Writer.WriteStartElement("PicrossData");
                Writer.WriteAttributeString("Rows", PicrossDataSingleton.Instance.RowCount.ToString());
                Writer.WriteAttributeString("Columns", PicrossDataSingleton.Instance.ColumnCount.ToString());
                Writer.WriteAttributeString("Version", "1.0.0");
                Writer.WriteStartElement("SolutionData");
                string filledCells = "";
                string cellColors = "";
                foreach (int cell in Enumerable.Range(0, PicrossDataSingleton.Instance.ColumnCount * PicrossDataSingleton.Instance.RowCount))
                {
                    if (PicrossDataSingleton.Instance[cell] == PicrossData.PicrossState.Filled)
                    {
                        if (filledCells.Length > 0)
                            filledCells += " ";
                        filledCells += cell.ToString();
                    }
                    if (cellColors.Length > 0)
                        cellColors += " ";
                    cellColors += PicrossDataSingleton.Instance.getCellColIndex(cell).ToString();
                }
                Writer.WriteAttributeString("FilledCells", filledCells);
                Writer.WriteEndElement(); // SolutionData
                Writer.WriteStartElement("ColorData");
                Writer.WriteAttributeString("CellColors", cellColors);
                foreach (int index in Enumerable.Range(0, 5))
                {
                    Color c = PicrossDataSingleton.Instance.getPalette(index);
                    Writer.WriteStartElement("Color");
                    Writer.WriteAttributeString("ARGB", c.ToArgb().ToString());
                    Writer.WriteEndElement(); //Color
                }
                Writer.WriteEndElement(); // ColorData
                Writer.WriteEndElement(); // PicrossData
                Writer.WriteEndDocument();
                Writer.Close();
                PicrossDataSingleton.Instance.Dirty = false;
                PrevSaveName = Filename;
            }
            stream.Close();
            stream = null;
        }

        // Switch between solution and color drawing mode
        private void selectColor_CheckedChanged(object sender, EventArgs e)
        {

            picrossGrid.DrawColors = ((RadioButton)sender).Checked;
            picrossDisplay1.DrawColors = ((RadioButton)sender).Checked;

            selectCol1.Enabled = ((RadioButton)sender).Checked;
            colorSelection1.Enabled = ((RadioButton)sender).Checked;

            selectCol2.Enabled = ((RadioButton)sender).Checked;
            colorSelection2.Enabled = ((RadioButton)sender).Checked;

            selectCol3.Enabled = ((RadioButton)sender).Checked;
            colorSelection3.Enabled = ((RadioButton)sender).Checked;

            selectCol4.Enabled = ((RadioButton)sender).Checked;
            colorSelection4.Enabled = ((RadioButton)sender).Checked;

            selectCol5.Enabled = ((RadioButton)sender).Checked;
            colorSelection5.Enabled = ((RadioButton)sender).Checked;
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }

        // Change the colors of the palette.
        private void colorSelection1_OnColorSelection(object sender, Color c)
        {
            PicrossDataSingleton.Instance.setPalette(0, c);
            picrossDisplay1.Invalidate();
            picrossGrid.Invalidate();
        }

        private void colorSelection2_OnColorSelection(object sender, Color c)
        {
            PicrossDataSingleton.Instance.setPalette(1, c);
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }

        private void colorSelection3_OnColorSelection(object sender, Color c)
        {
            PicrossDataSingleton.Instance.setPalette(2, c);
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }

        private void colorSelection4_OnColorSelection(object sender, Color c)
        {
            PicrossDataSingleton.Instance.setPalette(3, c);
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }

        private void colorSelection5_OnColorSelection(object sender, Color c)
        {
            PicrossDataSingleton.Instance.setPalette(4, c);
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }
        
        // Click inside the grid-area, edit a single cell
        private bool GetXYCell(MouseEventArgs arg, out int X, out int Y)
        {
            int smallestAxis = (picrossGrid.Width - 150 < picrossGrid.Height - 150) ? picrossGrid.Width - 150 : picrossGrid.Height - 150;
            int horizDim = ((smallestAxis) / picrossGrid.ColumnCount) - 1;
            int vertDim = ((smallestAxis) / picrossGrid.RowCount) - 1;
            int dim = (horizDim < vertDim) ? horizDim : vertDim;
            int ColumnCount = PicrossDataSingleton.Instance.ColumnCount;
            int RowCount = PicrossDataSingleton.Instance.RowCount;
            X = arg.X - 100;
            Y = arg.Y - 100;
            if (X < 0 || Y < 0)
                return false;
            X = (X) / (dim + 1);
            Y = (Y) / (dim + 1);
            if (X >= ColumnCount || Y >= RowCount)
                return false; // Outside of grid
            return true;
            
        }
        private void picrossGrid_Click(object sender, EventArgs e)
        {
            if (move)
                return;
            MouseEventArgs arg = (MouseEventArgs)e;
            if (arg.Button != MouseButtons.Left)
                return;
            int x, y;
            if (!GetXYCell(arg, out x, out y))
                return;
            if (x >= 0 && x < picrossGrid.ColumnCount && y >= 0 && y < picrossGrid.RowCount)
            {
                if(selectSolution.Checked)
                    PicrossDataSingleton.Instance[x, y] = (PicrossDataSingleton.Instance[x, y] == PicrossData.PicrossState.Filled) ? PicrossData.PicrossState.Unfilled : PicrossData.PicrossState.Filled;
                else
                {
                    ushort color = (ushort)((selectCol1.Checked) ? 0 :
                                       (selectCol2.Checked) ? 1 :
                                       (selectCol3.Checked) ? 2 :
                                       (selectCol4.Checked) ? 3 :
                                       4);
                    PicrossDataSingleton.Instance.setCellColIndex(x, y, color);
                }
            }
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }

        private void picrossGrid_MouseMove(object sender, MouseEventArgs e)
        {
            if (!down)
                return;
            move = true;
            int x, y;
            if (!GetXYCell(e, out x, out y))
                return;
            if (x == lastX && y == lastY)
                return;
            if (x >= 0 && x < picrossGrid.ColumnCount && y >= 0 && y < picrossGrid.RowCount)
                if (selectSolution.Checked)
                {
                    if (PicrossDataSingleton.Instance[x, y] == firstState)
                    {
                        PicrossDataSingleton.Instance[x, y] = (PicrossDataSingleton.Instance[x, y] == PicrossData.PicrossState.Filled) ? PicrossData.PicrossState.Unfilled : PicrossData.PicrossState.Filled;
                    }
                }
                else
                {
                    if (PicrossDataSingleton.Instance.getCellColIndex(x, y) == firstColor)
                    {
                       ushort color =(ushort)((selectCol1.Checked) ? 0 :
                                       (selectCol2.Checked) ? 1 :
                                       (selectCol3.Checked) ? 2 :
                                       (selectCol4.Checked) ? 3 :
                                       4);
                        PicrossDataSingleton.Instance.setCellColIndex(x, y, color);
                    }
                }
            lastX = x; lastY = y;
            picrossGrid.Invalidate();
            picrossDisplay1.Invalidate();
        }

        private void picrossGrid_MouseUp(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                down = false;
                move = false;
            }
        }

        private void picrossGrid_MouseDown(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                down = true;
                int x, y;
                if (!GetXYCell(e, out x, out y))
                    return;
                if (x >= 0 && x < picrossGrid.ColumnCount && y >= 0 && y < picrossGrid.RowCount)
                {
                    if (selectSolution.Checked)
                        firstState = PicrossDataSingleton.Instance[x, y];
                    else
                    {
                        firstColor = PicrossDataSingleton.Instance.getCellColIndex(x, y);
                    }
                }
                else
                    down = false;
                move = false;
                picrossGrid.Invalidate();
                picrossDisplay1.Invalidate();
            }
        }

        private void saveAsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            SaveAs();
        }

        private void newToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (PicrossDataSingleton.Instance.Dirty)
            {
                if (!AskDiscard())
                {
                    return;
                }
            }
            Reset();
        }

        private void Reset()
        {
            PicrossDataSingleton.Instance.Reset();
            colorSelection1.Color = Color.White;
            colorSelection1.Invalidate();
            colorSelection2.Color = Color.White;
            colorSelection2.Invalidate();
            colorSelection3.Color = Color.White;
            colorSelection3.Invalidate();
            colorSelection4.Color = Color.White;
            colorSelection4.Invalidate();
            colorSelection5.Color = Color.White;
            colorSelection5.Invalidate();
            selectCol1.Checked = true;
            selectSolution.Checked = true;
            picrossDisplay1.Invalidate();
            picrossGrid.Invalidate();
            PrevSaveName = null;
            columnUpDown.Value = 5;
            rowUpDown.Value = 5;
        }

        private void aboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form abt = new AboutBox();
            abt.ShowDialog();
        }

        private enum XMLStage
        {
            XMLDeclaration,
            XMLRoot,
            XMLSolution,
            XMLColorData,
            XMLColorARGB,
            XMLEnd
        }

        public class PicrossDataFileException : Exception
        {
            public PicrossDataFileException(string Message ="") { }
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if(PicrossDataSingleton.Instance.Dirty)
            {
                if (!AskDiscard())
                {
                    return;
                }
            }
            OpenFileDialog FileSelector = new OpenFileDialog();
            FileSelector.AddExtension = true;
            FileSelector.DefaultExt = ".xml";
            FileSelector.Title = "Save Picross Data";
            FileSelector.Filter = "Picross Data File|*.xml";
            DialogResult res = FileSelector.ShowDialog();
            XMLStage Stage = XMLStage.XMLDeclaration;
            if(res == DialogResult.OK)
            {
                Reset();
                int paletteCount = 0;
                int tmpInt = 0;
                string tmp = "";
                string[] cells = null;
                
                using (XmlReader Reader = XmlReader.Create(FileSelector.OpenFile()))
                {
                    while (Reader.Read())
                    { 
                        if (Reader.NodeType == XmlNodeType.Whitespace || Reader.NodeType == XmlNodeType.SignificantWhitespace)
                            continue;
                        switch(Stage)
                        {
                            case XMLStage.XMLDeclaration:
                                if (Reader.NodeType != XmlNodeType.XmlDeclaration)
                                    throw new PicrossDataFileException("Invalid Picross Data File, missing XML Declaration.");
                                Stage = XMLStage.XMLRoot;
                                break;
                            case XMLStage.XMLRoot:
                                if (Reader.NodeType != XmlNodeType.Element)
                                    throw new PicrossDataFileException("Invalid Picross Data File, missing root.");
                                if (Reader.Name != "PicrossData")
                                    throw new PicrossDataFileException("Invalid root element, expected PicrossData");
                                bool success = int.TryParse(Reader.GetAttribute("Columns"), out tmpInt);
                                if (!success)
                                    throw new PicrossDataFileException("Invalid Picross Data File, missing column count.");
                                PicrossDataSingleton.Instance.ColumnCount = tmpInt;
                                success = int.TryParse(Reader.GetAttribute("Rows"), out tmpInt);
                                if (!success)
                                    throw new PicrossDataFileException("Invalid Picross Data File, missing row count.");
                                PicrossDataSingleton.Instance.RowCount = tmpInt;
                                Stage = XMLStage.XMLSolution;
                                break;
                            case XMLStage.XMLSolution:
                                if (Reader.NodeType != XmlNodeType.Element)
                                    throw new PicrossDataFileException("Invalid Picross Data File, missing element.");
                                if (Reader.Name != "SolutionData")
                                    throw new PicrossDataFileException("Invalid root element, expected SolutionData");
                                tmp = Reader.GetAttribute("FilledCells");
                                cells = tmp.Split(new char[] { ' ' });
                                tmpInt = 0;
                                foreach(string s in cells)
                                {
                                    int.TryParse(s, out tmpInt);
                                    PicrossDataSingleton.Instance[tmpInt] = PicrossData.PicrossState.Filled;
                                }
                                cells = null;
                                Stage = XMLStage.XMLColorData;
                                break;
                            case XMLStage.XMLColorData:
                                if (Reader.NodeType != XmlNodeType.Element)
                                    throw new PicrossDataFileException("Invalid Picross Data File, missing element.");
                                if (Reader.Name != "ColorData")
                                    throw new PicrossDataFileException("Invalid root element, expected ColorData");
                                tmp = Reader.GetAttribute("CellColors");
                                cells = tmp.Split(new char[] { ' ' });
                                if(cells.Length != PicrossDataSingleton.Instance.ColumnCount* PicrossDataSingleton.Instance.RowCount)
                                    throw new PicrossDataFileException("Malformed Picross Data File; not all cells have color information.");
                                tmpInt = 0;
                                foreach (int index in Enumerable.Range(0, cells.Length))
                                {
                                    tmp = cells[index];
                                    int.TryParse(tmp, out tmpInt);
                                    PicrossDataSingleton.Instance.setCellColIndex(index, (ushort)tmpInt);
                                }
                                cells = null;
                                Stage = XMLStage.XMLColorARGB;
                                break;
                            case XMLStage.XMLColorARGB:
                                if (Reader.NodeType != XmlNodeType.Element)
                                    throw new PicrossDataFileException("Invalid Picross Data File, missing element.");
                                if (Reader.Name != "Color")
                                    throw new PicrossDataFileException("Invalid root element, expected Color");
                                tmp = Reader.GetAttribute("ARGB");
                                success = int.TryParse(tmp, out tmpInt);
                                if (!success)
                                    throw new PicrossDataFileException("Could not load color information!");
                                PicrossDataSingleton.Instance.setPalette(paletteCount++, Color.FromArgb(tmpInt));
                                switch(paletteCount)
                                {
                                    case 1:
                                        colorSelection1.Color = Color.FromArgb(tmpInt);
                                        colorSelection1.Invalidate();
                                        break;
                                    case 2:
                                        colorSelection2.Color = Color.FromArgb(tmpInt);
                                        colorSelection1.Invalidate();
                                        break;
                                    case 3:
                                        colorSelection3.Color = Color.FromArgb(tmpInt);
                                        colorSelection1.Invalidate();
                                        break;
                                    case 4:
                                        colorSelection4.Color = Color.FromArgb(tmpInt);
                                        colorSelection1.Invalidate();
                                        break;
                                    case 5:
                                        colorSelection5.Color = Color.FromArgb(tmpInt);
                                        colorSelection1.Invalidate();
                                        break;
                                }
                                if (paletteCount == 5)
                                    Stage = XMLStage.XMLEnd;                               
                                break;
                            default:
                                break;
                        }
                    }
                    Reader.Close();
                }
                PicrossDataSingleton.Instance.Dirty = false;
                PrevSaveName = FileSelector.FileName;
                columnUpDown.Value = PicrossDataSingleton.Instance.ColumnCount;
                rowUpDown.Value = PicrossDataSingleton.Instance.RowCount;
            }
        }
    }
}
