using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.Design;

namespace Picross
{
    public partial class PicrossGrid : UserControl
    {
        public int ColumnCount
        {
            get
            {
                return PicrossDataSingleton.Instance.ColumnCount;
            }
            set
            {
                PicrossDataSingleton.Instance.ColumnCount = value;
                Invalidate();
            }
        }

        public int RowCount
        {
            get
            {
                return PicrossDataSingleton.Instance.RowCount;
            }
            set
            {
                PicrossDataSingleton.Instance.RowCount = value;
                Invalidate();
            }
        }
        public bool DrawColors = false;
        // Store for repeated use.
        private FontFamily Family = new FontFamily("consolas");
        protected override void OnPaint(PaintEventArgs e)
        {
            base.OnPaint(e);
            // Figure out what size to make the text, in order to fit inside the alotted space.
            int longestRow = PicrossDataSingleton.Instance.LongestRowData;
            int longestColumn = PicrossDataSingleton.Instance.LongestColumnData;
            // prepare the string to measure.
            float hFontSize = 10;
            float vFontSize = 10;
            // Horizontal and vertical text might have different font scales.
            Font hFont = new Font(Family, hFontSize, FontStyle.Bold);
            Font vFont = new Font(Family, vFontSize, FontStyle.Bold);
            SizeF horizSpace;
            SizeF vertSpace;

            // Figure out the size of each cell
            int smallestAxis = (Size.Width-150 < Size.Height-150) ? Size.Width-150 : Size.Height-150;
            int horizDim = ((smallestAxis) / ColumnCount)-1;
            int vertDim = ((smallestAxis) / RowCount)-1;
            int dim = (horizDim < vertDim) ? horizDim : vertDim;
            int botY = 110 + dim*RowCount+RowCount;
            int rightX = 110 + dim * ColumnCount+ColumnCount;
            string measure = "00";
            for (int y = 0; y < longestRow; y++)
            {
                measure += "0 ";
            }
            horizSpace = e.Graphics.MeasureString(measure, hFont);
            while (horizSpace.Width > 99 || horizSpace.Height > dim/2)
            {
                hFontSize -= 0.25f;
                hFont = new Font(Family, hFontSize, FontStyle.Bold);
                horizSpace = e.Graphics.MeasureString(measure, hFont);
            }
            measure = "00";
            for (int x = 0; x < longestColumn; x++)
            {
                measure += "0 "+Environment.NewLine;
            }
            vertSpace = e.Graphics.MeasureString(measure, vFont);
            while(vertSpace.Height > 99 ||vertSpace.Width > dim/2)
            {
                vFontSize -= 0.25f;
                vFont = new Font(Family, vFontSize, FontStyle.Bold);
                vertSpace = e.Graphics.MeasureString(measure, vFont);
            }
            SolidBrush[] brushes = new SolidBrush[5];
            brushes[0] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(0));
            brushes[1] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(1));
            brushes[2] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(2));
            brushes[3] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(3));
            brushes[4] = new SolidBrush(PicrossDataSingleton.Instance.getPalette(4));
            foreach (int y in Enumerable.Range(0, RowCount))
            {
                foreach (int x in Enumerable.Range(0, ColumnCount))
                {
                    if (!DrawColors)
                    { 
                        if (PicrossDataSingleton.Instance[x, y] == PicrossData.PicrossState.Filled)
                        {
                            e.Graphics.FillRectangle(Brushes.Black, 100 + x * dim + x, 100 + y * dim + y, dim, dim);
                        }
                        else
                        {
                            e.Graphics.FillRectangle(Brushes.White, 100 + x * dim + x, 100 + y * dim + y, dim, dim);
                        }
                    }
                    else
                    {
                        e.Graphics.FillRectangle(brushes[PicrossDataSingleton.Instance.getCellColIndex(x,y)], 100 + x * dim + x, 100 + y * dim + y, dim, dim);
                    }
                }
            }

            // Draw grid lines
            bool Alternate = false;
            int tmpX = 100 + ColumnCount + dim * ColumnCount;
            foreach (int y in Enumerable.Range(-1, RowCount +1))
            {
                if (y >= 0)
                {
                    if (Alternate)
                    {
                        e.Graphics.FillRectangle(Brushes.DarkGray, 0, 100 + y * dim + y, 100, dim);
                        e.Graphics.FillRectangle(Brushes.DarkGray, tmpX, 100 + y * dim + y, Width - tmpX, dim);
                        Alternate = !Alternate;
                    }
                    else
                    {
                        e.Graphics.FillRectangle(Brushes.LightGray, 0, 100 + y * dim + y, 100, dim);
                        e.Graphics.FillRectangle(Brushes.LightGray, tmpX, 100 + y * dim + y, Width - tmpX, dim);
                        Alternate = !Alternate;
                    }
                }
                e.Graphics.DrawLine(Pens.Black, 0, 100 + y + dim + dim * y, Width, 100 + y + dim + dim * y);
            }
            Alternate = false;
            int tmpY = 100 + RowCount + dim * RowCount;
            // Draw grid lines
            foreach (int x in Enumerable.Range(-1, ColumnCount + 1))
            {
                if (x >= 0)
                {
                    if (Alternate)
                    {
                        e.Graphics.FillRectangle(Brushes.DarkGray, 100 + x * dim + x, 0, dim, 99);
                        e.Graphics.FillRectangle(Brushes.DarkGray, 100 + x * dim + x,tmpY, dim, Height-tmpY);
                        Alternate = !Alternate;
                    }
                    else
                    {
                        e.Graphics.FillRectangle(Brushes.LightGray, 100 + x * dim + x, 0, dim, 99);
                        e.Graphics.FillRectangle(Brushes.LightGray, 100 + x * dim + x, tmpY, dim, Height - tmpY);
                        Alternate = !Alternate;
                    }
                }
                e.Graphics.DrawLine(Pens.Black, 100 + x + dim + dim * x, 0, 100 + x + dim + dim * x, Height);
            }

            // Print help data.
            string str = "";
            List<int> L = null;
            foreach (int y in Enumerable.Range(0, RowCount))
            {
                L = PicrossDataSingleton.Instance.GetRowData(y);
                foreach (int i in L)
                    str += i + " ";
                e.Graphics.DrawString(str, hFont, Brushes.Black, 0, 100 + (dim/2)+dim * y+y);
                str = "";
                L = null;
                // Print row numbers
                e.Graphics.DrawString((y+1).ToString(), hFont, Brushes.Black, Right-(Width-tmpX)/2, 100 + (dim / 2) + dim * y + y);

            }
            foreach (int x in Enumerable.Range(0, ColumnCount))
            {
                L = PicrossDataSingleton.Instance.GetColumnData(x);
                foreach (int i in L)
                    str += i + Environment.NewLine;
                e.Graphics.DrawString(str, vFont, Brushes.Black, 100 + (dim / 2) + dim * x+x, 0);
                e.Graphics.DrawString((x + 1).ToString(), hFont, Brushes.Black, 100 + (dim / 2) + dim * x + x, Bottom - (Height - tmpY) / 2);
                str = "";
                L = null;
            }       
        }

        public PicrossGrid()
        {
            InitializeComponent();
            SetStyle(ControlStyles.ResizeRedraw, true);
        }
    }
}
