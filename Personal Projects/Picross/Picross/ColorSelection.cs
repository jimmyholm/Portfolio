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
    public delegate void ColorSelected(object sender, Color c);
    public partial class ColorSelection : UserControl
    {
        public event ColorSelected OnColorSelection;
        private Color color = Color.White;
        public Color Color
        {
            get
            {
                return color;
            }
            set
            {
                color = value;
                selectColor.BackColor = color;
                Invalidate();
            }
        }
        public ColorSelection()
        {
            InitializeComponent();
            selectColor.BackColor = color;
            Invalidate();
        }
        
        private void selectColor_Click(object sender, EventArgs e)
        {
            DialogResult dr = colorDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                color = colorDialog.Color;
                selectColor.BackColor = color;
                Invalidate();
                if (OnColorSelection != null)
                    OnColorSelection(this, color);

            }
        }
    }
}
