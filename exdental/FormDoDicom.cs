using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using geronimo;
using System.Diagnostics;
//TODO: Saida do VR
//TODO: Filtros na imagem
//TODO: Hough transform
namespace exdental
{
    public partial class formDoDicom : Form
    {
        //O meu objeto pras coisas da vtk.
        //private VtkContext contextoDaVtk = null;
        
        //Minha tela
        private TelaRadiografia telaRadiografia = null;
        //O carregador de dicom
        private ImageLoader imageLoader = null;
        //A imagem carregada
        private Imagem image = null;

        public formDoDicom()
        {
            InitializeComponent();
        }

        private void buttonAbrir_Click(object sender, EventArgs e)
        {
            imageLoader = new ImageLoader();
            imageLoader.SetProgressBar(progressBar);
            List<String> listDeImagensNoDir = imageLoader.GetListaDeImagens(textBoxPath.Text);
            if (listDeImagensNoDir.Count == 1)
            {
                progressBar.Value = 0;
                imageLoader.LoadFromDir(textBoxPath.Text);
            }
            else
            {
                FormEscolhaExame formEscolha = new FormEscolhaExame();
                formEscolha.SetListaDeSeries(listDeImagensNoDir);
                formEscolha.ShowDialog();
                int selectedRow = formEscolha.SelectedRow;
                //Agora eu sei qual serie foi escolhida, passar pra vtk.
                formEscolha.Dispose();
                progressBar.Value = 0;
                imageLoader.LoadFromDir(textBoxPath.Text, selectedRow);
            }
            image = imageLoader.GetImagemCarregada();
            telaRadiografia = new TelaRadiografia();
            telaRadiografia.CreateScreen(panelRenderizacao);
            telaRadiografia.SetImagem(image);
            imageLoader.Dispose();

        }
        private void formDoDicom_Shown(object sender, EventArgs e)
        {
            
        }

        private void formDoDicom_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (telaRadiografia != null)
                telaRadiografia.Dispose();
            if (image != null)
                image.Dispose();
        }

        private void formDoDicom_ResizeEnd(object sender, EventArgs e)
        {
            if(telaRadiografia!=null)
                telaRadiografia.Resize(this.Size.Width, this.Size.Height);
        }

        private void formDoDicom_Resize(object sender, EventArgs e)
        {
            if (telaRadiografia != null)
                telaRadiografia.Resize(this.Size.Width, this.Size.Height);
        }
        protected override void WndProc(ref Message m)
        {
            if (m.Msg == 0x0112) // WM_SYSCOMMAND
            {
                if (m.WParam == new IntPtr(0xF030)) // Maximize event - SC_MAXIMIZE from Winuser.h
                {
                    if (telaRadiografia != null)
                        telaRadiografia.Resize(this.Size.Width, this.Size.Height);
                }
            }
            base.WndProc(ref m);
        }

        private void txtWindow_TextChanged(object sender, EventArgs e)
        {
            try
            {
                int w = Int32.Parse(txtWindow.Text);
                int l = Int32.Parse(txtLevel.Text);
                telaRadiografia.SetWL(w, l);
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception);
            }
        }

        private void txtLevel_TextChanged(object sender, EventArgs e)
        {
            try
            {
                int w = Int32.Parse(txtWindow.Text);
                int l = Int32.Parse(txtLevel.Text);
                telaRadiografia.SetWL(w, l);
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception);
            }
        }

        private void panelRenderizacao_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
