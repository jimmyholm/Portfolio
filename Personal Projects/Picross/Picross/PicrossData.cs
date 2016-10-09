using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace Picross
{
    public class PicrossData
    {
        // Properties
        private bool dirty = false;
        public bool Dirty
        {
            get
            {
                return dirty;
            }
            set
            {
                dirty = value;
            }
        }
        private int columnCount = 5;
        private int rowCount = 5;
        public enum PicrossState
        {
            Unfilled = 0,
            Filled
        }
        private PicrossState[] cells;
        // Palette of all colors available. Data is RGBX, packed into a 32-bit int.
        public Color[] palette = new Color[5];

        private ushort[] cellColors;
        // Contains information on filled cell-groups per row and data.
        private List<int>[] rowData = null;
        private List<int>[] colData = null;

        // Palette accessor functions
        public Color getPalette(int index)
        {
            if (index < 0 || index > 4)
                throw new ArgumentOutOfRangeException();
            return palette[index];
        }
        public void setPalette(int index, Color color)
        {
            if (index < 0 || index > 4)
                throw new ArgumentOutOfRangeException();
            palette[index] = color;
        }
        // Cell color accessor functions
        public ushort getCellColIndex(int x, int y)
        {
            if (x < 0 || y < 0 || x + y * columnCount >= rowCount * columnCount)
                throw new ArgumentOutOfRangeException();
            return cellColors[x + y * columnCount];
        }
        public ushort getCellColIndex(int cell)
        {
            if (cell <0 || cell >= rowCount * columnCount)
                throw new ArgumentOutOfRangeException();
            return cellColors[cell];
        }
        public void setCellColIndex(int x, int y, ushort ColIndex)
        {
            if(x < 0 || y < 0 || x >= columnCount || y >= rowCount)
                throw new ArgumentOutOfRangeException();
            setCellColIndex(x + y * columnCount, ColIndex);
        }
        public void setCellColIndex(int cell, ushort ColIndex)
        {
            if (cell < 0 || cell >= rowCount * columnCount || ColIndex < 0 || ColIndex > 4)
                throw new ArgumentOutOfRangeException();
            cellColors[cell] = ColIndex;
        }

        // Build the solution-lists.
        private void buildColRowData()
        {
            // Build data per row.
            rowData = new List<int>[rowCount];
            // Keep a running tally on number of filled cells found.
            int filledCells = 0;
            foreach (int y in Enumerable.Range(0, rowCount))
            {
                rowData[y] = new List<int>();
                foreach (int x in Enumerable.Range(0, columnCount))
                {
                    // Once an unfilled cell is found following a count of filled cells, add cell-count to the list and reset the count.
                    if (this[x, y] == PicrossState.Unfilled && filledCells > 0)
                    {
                        rowData[y].Add(filledCells);
                        filledCells = 0;
                    }
                    // Filled cell, add to the count.
                    else if (this[x, y] == PicrossState.Filled)
                    {
                        filledCells++;
                    }
                }
                if (filledCells > 0)
                {
                    rowData[y].Add(filledCells);
                }
                filledCells = 0;
            }
            // Build data per column.
            colData = new List<int>[columnCount];
            foreach (int x in Enumerable.Range(0, columnCount))
            {
                colData[x] = new List<int>();
                foreach (int y in Enumerable.Range(0, rowCount))
                {
                    // Once an unfilled cell is found following a count of filled cells, add cell-count to the list and reset the count.
                    if (this[x, y] == PicrossState.Unfilled && filledCells > 0)
                    {
                        colData[x].Add(filledCells);
                        filledCells = 0;
                    }
                    // Filled cell, add to the count
                    else if (this[x, y] == PicrossState.Filled)
                    {
                        filledCells++;
                    }
                }
                if (filledCells > 0)
                {
                    colData[x].Add(filledCells);
                }
                filledCells = 0;
            }
        }
        // Return the list of filled cell counts in a given row.
        public List<int> GetRowData(int index)
        {
            if (index < 0 || index > RowCount)
                throw new ArgumentOutOfRangeException();
            if (rowData == null)
                buildColRowData();
            return rowData[index];
        }
        // Return the list of filled cell counts in a given column.
        public List<int> GetColumnData(int index)
        {
            if (index < 0 || index > ColumnCount)
                throw new ArgumentOutOfRangeException();
            if (colData == null)
                buildColRowData();
            return colData[index];
        }

        // Provide the maximum number of clusters in a row
        public int LongestRowData
        {
            get
            {
                if (rowData == null)
                    buildColRowData();
                int tmp = 0;
                foreach (List<int> l in rowData)
                {
                    if (l.Count > tmp)
                    {
                        tmp = l.Count;
                    }
                }
                return tmp;
            }
        }

        // Provide the maximum number of clusters in a column
        public int LongestColumnData
        {
            get
            {
                if (colData == null)
                    buildColRowData();
                int tmp = 0;
                foreach (List<int> l in colData)
                {
                    if (l.Count > tmp)
                    {
                        tmp = l.Count;
                    }
                }
                return tmp;
            }
        }

        // Reset data to default state.
        public void Reset()
        {
            cells = new PicrossState[25];
            palette = new Color[5];
            cellColors = new ushort[25];
            foreach (int index in Enumerable.Range(0, 25))
            {
                cells[index] = PicrossState.Unfilled;
                cellColors[index] = 0;
            }
            foreach(int index in Enumerable.Range(0,5))
            {
                palette[index] = Color.White;
            }
            
            rowCount = 5;
            columnCount = 5;
            Dirty = false;
            buildColRowData();
        }

        // Allow for dynamic resize, non-destructive if possible.
        public int ColumnCount
        {
            get
            {
                return columnCount;
            }
            set
            {
                if (value < 0)
                    throw new ArgumentOutOfRangeException("Column-count must be non-negative");
                if (value == columnCount)
                    return;
                PicrossState[] tmp = new PicrossState[columnCount * rowCount];
                ushort[] tmp2 = new ushort[columnCount * rowCount];
                cells.CopyTo(tmp, 0);
                cellColors.CopyTo(tmp2, 0);
                cells = new PicrossState[value * rowCount];
                cellColors = new ushort[value * rowCount];
                if (value > columnCount)
                {
                    int newCol = value - columnCount;
                    foreach (int y in Enumerable.Range(0, rowCount))
                        foreach (int x in Enumerable.Range(0, value))
                        {
                            cells[x + y * value] = (x >= value - newCol) ? PicrossState.Unfilled : tmp[x + y * columnCount];
                            cellColors[x + y * value] = (x >= value - newCol) ? (ushort)0 : tmp2[x + y * columnCount];
                        }
                }
                else
                {
                    foreach (int y in Enumerable.Range(0, rowCount))
                        foreach (int x in Enumerable.Range(0, value))
                        {
                            cells[x + y * value] = tmp[x + y * columnCount];
                            cellColors[x + y * value] = tmp2[x + y * columnCount];
                        }
                }
                dirty = true;
                columnCount = value;
                tmp = null;
                tmp2 = null;
                buildColRowData();
            }
        }

        public int RowCount
        {
            get
            {
                return rowCount;
            }
            set
            {
                if (value < 0)
                    throw new ArgumentOutOfRangeException("Rowcount must be non-negative");
                if (value == rowCount)
                    return;
                PicrossState[] tmp = new PicrossState[columnCount * rowCount];
                ushort[] tmp2 = new ushort[columnCount * rowCount];
                cells.CopyTo(tmp, 0);
                cellColors.CopyTo(tmp2, 0);
                cells = new PicrossState[value * columnCount];
                cellColors = new ushort[value * columnCount];
                int newRow = (value > rowCount) ? value - rowCount : rowCount - value;
                foreach (int y in Enumerable.Range(0, value))
                {
                    foreach (int x in Enumerable.Range(0, columnCount))
                    {
                        if (value > rowCount)
                        {
                            cells[x + y * columnCount] = (y >= value - newRow) ? PicrossState.Unfilled : tmp[x + y * columnCount];
                            cellColors[x + y * columnCount] = (y >= value - newRow) ? (ushort)0 : tmp2[x + y * columnCount];
                        }
                        else
                        {
                            cells[x + y * columnCount]      = tmp[x + y * columnCount];
                            cellColors[x + y * columnCount] = tmp2[x + y * columnCount];
                        }
                    }
                }
                dirty = true;
                rowCount = value;
                tmp = null;
                tmp2 = null;
                buildColRowData();
            }
        }

        // Access data fields using 2-dimensional array like syntax
        public PicrossState this[int x, int y]
        {
            get
            {
                if (x < 0 || x > columnCount)
                    throw new ArgumentOutOfRangeException(String.Format("X value out of range. {0} not in range [0, {1}]", x, columnCount - 1));
                if (y < 0 || y > rowCount)
                    throw new ArgumentOutOfRangeException(String.Format("Y value out of range. {0} not in range [0, {1}]", x, rowCount - 1));

                return cells[x + y * columnCount];
            }
            set
            {
                if (x < 0 || x > columnCount)
                    throw new ArgumentOutOfRangeException(String.Format("X value out of range. {0} not in range [0, {1}]", x, columnCount - 1));
                if (y < 0 || y > rowCount)
                    throw new ArgumentOutOfRangeException(String.Format("Y value out of range. {0} not in range [0, {1}]", x, rowCount - 1));
                cells[x + y * columnCount] = value;
                dirty = true;
                buildColRowData();
            }
        }
        // Access data fields using direct indexing
        public PicrossState this[int index]
        {
            get
            {
                if (index < 0 || index >= columnCount * rowCount)
                    throw new ArgumentOutOfRangeException();
                return cells[index];
            }
            set
            {
                if (index < 0 || index >= columnCount * rowCount)
                    throw new ArgumentOutOfRangeException();
                dirty = true;
                cells[index] = value;
                buildColRowData();
            }
        }
        public PicrossData()
        {
            Reset();
        }
    }

    // Keep a singleton of the picross data available to the program - all controls interact with the same instance of the puzzle.
    public sealed class PicrossDataSingleton
    {
        private static readonly Lazy<PicrossData> data =
            new Lazy<PicrossData>(() => new PicrossData());

        public static PicrossData Instance {get{return data.Value;} }

        private PicrossDataSingleton()
        {

        }
    }
}
