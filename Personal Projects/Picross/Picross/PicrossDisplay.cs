using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Picross
{
    public partial class PicrossDisplay : UserControl
    {
        public PicrossDisplay()
        {
            InitializeComponent();
        }
        public bool DrawColors = false;
        private void PicrossDisplay_Paint(object sender, PaintEventArgs e)
        {
            //base.OnPaint(e);
            Graphics g = e.Graphics;

            // Draw bounding-box.
            g.DrawRectangle(Pens.Black, 0, 0, this.Width-1, this.Height-1);
            // Draw cells as 10x10 pixels
            SolidBrush[] brushes = new SolidBrush[5];
            brushes[0] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(0));
            brushes[1] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(1));
            brushes[2] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(2));
            brushes[3] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(3));
            brushes[4] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(4));
            int dim = 10;
            int colCount = PicrossDataSingleton.Instance.ColumnCount;
            int rowCount = PicrossDataSingleton.Instance.RowCount;
            if (dim*colCount> Width-2 || dim*rowCount > Width-2)
            {
                // Find the largest axis of the data
                if(colCount > PicrossDataSingleton.Instance.RowCount)
                {
                    // Resize squares to fit inside the frame
                    dim = (Width - 2) / colCount;
                }
                else
                {
                    // Resize squares to fit inside the frame
                    dim = (Height- 2) / rowCount;
                }
            }
            // Place square in the center of the frame.
            int StartX = 1 + (Width  / 2) - ((dim * colCount) / 2);
            int StartY = 1 + (Height / 2) - ((dim * rowCount) / 2);
            foreach (int y in Enumerable.Range(0,PicrossDataSingleton.Instance.RowCount))
            {
                foreach (int x in Enumerable.Range(0, PicrossDataSingleton.Instance.ColumnCount))
                {
                    if (!DrawColors)
                    {
                        if (PicrossDataSingleton.Instance[x, y] == PicrossData.PicrossState.Filled)
                        {
                            e.Graphics.FillRectangle(Brushes.Black, StartX + x * dim, StartY + y * dim, dim, dim);
                        }
                        else
                        {
                            e.Graphics.FillRectangle(Brushes.White, StartX + x * dim, StartY + y * dim, dim, dim);
                        }
                    }
                    else
                    {
                        g.FillRectangle(brushes[PicrossDataSingleton.Instance.getCellColIndex(x, y)], StartX + x * dim, StartY + y * dim, dim, dim);
                    }
                }
            }
        }
    }
}
