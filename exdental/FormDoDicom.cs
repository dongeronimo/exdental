﻿using System;
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
using System.Globalization;
using System.Threading;

//TODO: Saida do VR
//TODO: Filtros na imagem
//TODO: Hough transform
namespace exdental
{
    public partial class formDoDicom : Form
    {
        private ImageLoader loader = null;
        private geronimo.Image image = null;
        private geronimo.TelaRadiografia telaRadiografia = null;
        private TelaVR telaVr = null;

        private void RefreshTelas()
        {
            panelRenderizacao.Refresh();
            panelVr.Refresh();
        }
        public formDoDicom()
        {
            InitializeComponent();
        }

        private void buttonAbrir_Click(object sender, EventArgs e)
        {
            loader = new ImageLoader(this.Handle);
            List<String> listaDeImagens = loader.GetListaDeImagens(textBoxPath.Text);
            if (listaDeImagens.Count == 0)
            {
                throw new Exception("Sem imagens");
            }
            else if (listaDeImagens.Count == 1)
            {
                loader.Load();
            }
            else
            {
                FormEscolhaExame formEscolha = new FormEscolhaExame();
                formEscolha.SetListaDeSeries(listaDeImagens);
                formEscolha.ShowDialog();
                int selectedRow = formEscolha.SelectedRow;
                formEscolha.Dispose();
                loader.Load(selectedRow);
            }
            image = loader.GetImage();//A partir daqui não preciso mais do loader, já tenho 
            //o que quero.
            telaRadiografia = new TelaRadiografia();
            telaRadiografia.CreateScreen(panelRenderizacao);
            telaRadiografia.SetImagem(image);
            telaVr = new TelaVR();
            telaVr.CreateScreen(panelVr);
            telaVr.SetImagem(image);
            loader.Dispose();
        }
        private void formDoDicom_Shown(object sender, EventArgs e)
        {
            
        }

        private void formDoDicom_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (telaRadiografia != null)
                telaRadiografia.Dispose();
            if (telaVr != null)
                telaVr.Dispose();
            if (image != null)
                image.Dispose();
        }

        private void formDoDicom_ResizeEnd(object sender, EventArgs e)
        {
            //if(telaRadiografia!=null)
            //    telaRadiografia.Resize(this.Size.Width, this.Size.Height);
        }

        private void formDoDicom_Resize(object sender, EventArgs e)
        {
            //if (telaRadiografia != null)
            //    telaRadiografia.Resize(this.Size.Width, this.Size.Height);
        }
        protected override void WndProc(ref Message m)
        {
            if (m.Msg == 0x0112) // WM_SYSCOMMAND
            {
                if (m.WParam == new IntPtr(0xF030)) // Maximize event - SC_MAXIMIZE from Winuser.h
                {
                    //if (telaRadiografia != null)
                    //    telaRadiografia.Resize(this.Size.Width, this.Size.Height);
                }
            }
            if (m.Msg == (2024))//O Evento que progressObserver da itk e vtk geram:
            {
                int progresso = m.WParam.ToInt32();
                progressBar1.Value = progresso;
                progressBar1.Refresh();
            }
            base.WndProc(ref m);
        }

        private void txtWindow_TextChanged(object sender, EventArgs e)
        {

        }

        private void txtLevel_TextChanged(object sender, EventArgs e)
        {

        }

        private void panelRenderizacao_Paint(object sender, PaintEventArgs e)
        {

        }

        private void btnAplicarGpuSmooth_Click(object sender, EventArgs e)
        {
            int _gpuIteracoes = Int32.Parse(edtGpuSmoothIterations.Text);
            double _gpuTS = Double.Parse(edtGpuSmoothTimestep.Text, new CultureInfo("en-US"));
            double _gpuConductance = Double.Parse(edtGpuSmoothConductance.Text, new CultureInfo("en-US"));
            image.AplicarSuavizacao(_gpuIteracoes, _gpuTS, _gpuConductance);
            RefreshTelas();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            image.SalvarParaOVolview("C:\\Users\\geronimo\\dicom\\artefato_maxilar.vti");
        }

        private void button2_Click(object sender, EventArgs e)
        {
            loader = new ImageLoader(this.Handle);
            loader.LoadVTI("C:\\Users\\geronimo\\dicom\\artefato_maxilar.vti");
            image = loader.GetImage();//A partir daqui não preciso mais do loader, já tenho 
            //o que quero.
            telaRadiografia = new TelaRadiografia();
            telaRadiografia.CreateScreen(panelRenderizacao);
            telaRadiografia.SetImagem(image);
            telaVr = new TelaVR();
            telaVr.CreateScreen(panelVr);
            telaVr.SetImagem(image);
            loader.Dispose();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            loader = new ImageLoader(this.Handle);
            loader.TesteEnvioDeEventoDeVoltaPraTela(this.Handle);
        }

        private void txtWindow_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void btnAplicarSigmoid_Click(object sender, EventArgs e)
        {
            int alpha = Int32.Parse(edtSigmoidAlpha.Text);
            int beta = Int32.Parse(edtSimgoidBeta.Text);
            int min = Int32.Parse(edtSigmoidMin.Text);
            int max = Int32.Parse(edtSigmoidMax.Text);
            image.AplicarSigmoide(alpha, beta, min, max);
            RefreshTelas();
        }

        private void button3_Click_1(object sender, EventArgs e)
        {
            image.SalvarSigmoide("C:\\Users\\geronimo\\dicom\\maxilar_sigmoide.vti");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            image.SalvarOtsu("C:\\Users\\geronimo\\dicom\\maxilar_otsu.vti");
        }
    }
}

