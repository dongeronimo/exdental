using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace exdental
{
    public partial class FormEscolhaExame : Form
    {
        class Series
        {
            public String identifier;
            public String numeroDeFatias;
            public string Identifier { get { return identifier; } set { identifier = value; } }
            public string NumeroDeFatias { get { return numeroDeFatias; } set { numeroDeFatias = value; } }
        }        
        private List<Series> listaDeSeries;

        private int _selectedRow;
        public int SelectedRow { get { return _selectedRow;} set { _selectedRow = value; } }
        public FormEscolhaExame()
        {
            InitializeComponent();
        }

        public void SetListaDeSeries(List<String> lst)
        {
            listaDeSeries = new List<Series>();
            for (int i = 0; i < lst.Count; i++)
            {
                string[] pedacos = lst[i].Split(';');    
                Series s = new Series();
                s.identifier = pedacos[0];
                s.numeroDeFatias = pedacos[1];
                listaDeSeries.Add(s);
            }
            dataGridView1.DataSource = listaDeSeries;
            
        }

        private void FormEscolhaExame_Load(object sender, EventArgs e)
        {
        }

        private void dataGridView1_MouseDoubleClick(object sender, MouseEventArgs e)
        {

        }

        private void dataGridView1_SelectionChanged(object sender, EventArgs e)
        {

        }

        private void dataGridView1_CellContentDoubleClick(object sender, DataGridViewCellEventArgs e)
        {
            _selectedRow = e.RowIndex;
            this.DialogResult = DialogResult.OK;
            this.Close();
        }
    }
}
