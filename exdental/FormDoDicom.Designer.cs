namespace exdental
{
    partial class formDoDicom
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
            this.panelSuperior = new System.Windows.Forms.Panel();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.buttonAbrir = new System.Windows.Forms.Button();
            this.textBoxPath = new System.Windows.Forms.TextBox();
            this.panelRenderizacao = new System.Windows.Forms.Panel();
            this.panelVr = new System.Windows.Forms.Panel();
            this.panelFiltros = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.btnAplicarSigmoid = new System.Windows.Forms.Button();
            this.edtSigmoidMax = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.edtSigmoidMin = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.edtSimgoidBeta = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.edtSigmoidAlpha = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.panelPropriedadesGPU = new System.Windows.Forms.Panel();
            this.btnAplicarGpuSmooth = new System.Windows.Forms.Button();
            this.edtGpuSmoothConductance = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.edtGpuSmoothTimestep = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.edtGpuSmoothIterations = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.button3 = new System.Windows.Forms.Button();
            this.panelSuperior.SuspendLayout();
            this.panelFiltros.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panelPropriedadesGPU.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelSuperior
            // 
            this.panelSuperior.Controls.Add(this.button2);
            this.panelSuperior.Controls.Add(this.button1);
            this.panelSuperior.Controls.Add(this.buttonAbrir);
            this.panelSuperior.Controls.Add(this.textBoxPath);
            this.panelSuperior.Dock = System.Windows.Forms.DockStyle.Top;
            this.panelSuperior.Location = new System.Drawing.Point(0, 0);
            this.panelSuperior.Name = "panelSuperior";
            this.panelSuperior.Size = new System.Drawing.Size(1016, 29);
            this.panelSuperior.TabIndex = 0;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(431, 0);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(125, 23);
            this.button2.TabIndex = 3;
            this.button2.Text = "abertura alternativa";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(855, 3);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(149, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Salvar pro volview entender";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonAbrir
            // 
            this.buttonAbrir.Location = new System.Drawing.Point(350, 1);
            this.buttonAbrir.Name = "buttonAbrir";
            this.buttonAbrir.Size = new System.Drawing.Size(75, 20);
            this.buttonAbrir.TabIndex = 1;
            this.buttonAbrir.Text = "Abrir";
            this.buttonAbrir.UseVisualStyleBackColor = true;
            this.buttonAbrir.Click += new System.EventHandler(this.buttonAbrir_Click);
            // 
            // textBoxPath
            // 
            this.textBoxPath.Location = new System.Drawing.Point(0, 0);
            this.textBoxPath.Name = "textBoxPath";
            this.textBoxPath.Size = new System.Drawing.Size(344, 20);
            this.textBoxPath.TabIndex = 0;
            // 
            // panelRenderizacao
            // 
            this.panelRenderizacao.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.panelRenderizacao.Location = new System.Drawing.Point(237, 35);
            this.panelRenderizacao.Name = "panelRenderizacao";
            this.panelRenderizacao.Size = new System.Drawing.Size(402, 441);
            this.panelRenderizacao.TabIndex = 1;
            this.panelRenderizacao.Paint += new System.Windows.Forms.PaintEventHandler(this.panelRenderizacao_Paint);
            // 
            // panelVr
            // 
            this.panelVr.Location = new System.Drawing.Point(644, 35);
            this.panelVr.Margin = new System.Windows.Forms.Padding(2);
            this.panelVr.Name = "panelVr";
            this.panelVr.Size = new System.Drawing.Size(367, 441);
            this.panelVr.TabIndex = 3;
            // 
            // panelFiltros
            // 
            this.panelFiltros.Controls.Add(this.panel1);
            this.panelFiltros.Controls.Add(this.panelPropriedadesGPU);
            this.panelFiltros.Location = new System.Drawing.Point(0, 35);
            this.panelFiltros.Margin = new System.Windows.Forms.Padding(2);
            this.panelFiltros.Name = "panelFiltros";
            this.panelFiltros.Size = new System.Drawing.Size(232, 441);
            this.panelFiltros.TabIndex = 4;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.button3);
            this.panel1.Controls.Add(this.btnAplicarSigmoid);
            this.panel1.Controls.Add(this.edtSigmoidMax);
            this.panel1.Controls.Add(this.label9);
            this.panel1.Controls.Add(this.edtSigmoidMin);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Controls.Add(this.edtSimgoidBeta);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.edtSigmoidAlpha);
            this.panel1.Controls.Add(this.label8);
            this.panel1.Controls.Add(this.label7);
            this.panel1.Location = new System.Drawing.Point(3, 101);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(229, 135);
            this.panel1.TabIndex = 8;
            // 
            // btnAplicarSigmoid
            // 
            this.btnAplicarSigmoid.Location = new System.Drawing.Point(87, 4);
            this.btnAplicarSigmoid.Margin = new System.Windows.Forms.Padding(2);
            this.btnAplicarSigmoid.Name = "btnAplicarSigmoid";
            this.btnAplicarSigmoid.Size = new System.Drawing.Size(56, 19);
            this.btnAplicarSigmoid.TabIndex = 15;
            this.btnAplicarSigmoid.Text = "aplicar";
            this.btnAplicarSigmoid.UseVisualStyleBackColor = true;
            this.btnAplicarSigmoid.Click += new System.EventHandler(this.btnAplicarSigmoid_Click);
            // 
            // edtSigmoidMax
            // 
            this.edtSigmoidMax.Location = new System.Drawing.Point(87, 93);
            this.edtSigmoidMax.Name = "edtSigmoidMax";
            this.edtSigmoidMax.Size = new System.Drawing.Size(100, 20);
            this.edtSigmoidMax.TabIndex = 14;
            this.edtSigmoidMax.Text = "1000";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(14, 93);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(26, 13);
            this.label9.TabIndex = 13;
            this.label9.Text = "max";
            // 
            // edtSigmoidMin
            // 
            this.edtSigmoidMin.Location = new System.Drawing.Point(87, 70);
            this.edtSigmoidMin.Name = "edtSigmoidMin";
            this.edtSigmoidMin.Size = new System.Drawing.Size(100, 20);
            this.edtSigmoidMin.TabIndex = 12;
            this.edtSigmoidMin.Text = "0";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(14, 70);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(23, 13);
            this.label1.TabIndex = 11;
            this.label1.Text = "min";
            // 
            // edtSimgoidBeta
            // 
            this.edtSimgoidBeta.Location = new System.Drawing.Point(87, 47);
            this.edtSimgoidBeta.Name = "edtSimgoidBeta";
            this.edtSimgoidBeta.Size = new System.Drawing.Size(100, 20);
            this.edtSimgoidBeta.TabIndex = 10;
            this.edtSimgoidBeta.Text = "1392";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(14, 47);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Beta";
            // 
            // edtSigmoidAlpha
            // 
            this.edtSigmoidAlpha.Location = new System.Drawing.Point(87, 25);
            this.edtSigmoidAlpha.Name = "edtSigmoidAlpha";
            this.edtSigmoidAlpha.Size = new System.Drawing.Size(100, 20);
            this.edtSigmoidAlpha.TabIndex = 8;
            this.edtSigmoidAlpha.Text = "409";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(14, 25);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(34, 13);
            this.label8.TabIndex = 7;
            this.label8.Text = "Alpha";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(14, 4);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(50, 13);
            this.label7.TabIndex = 0;
            this.label7.Text = "Sigmoide";
            // 
            // panelPropriedadesGPU
            // 
            this.panelPropriedadesGPU.Controls.Add(this.btnAplicarGpuSmooth);
            this.panelPropriedadesGPU.Controls.Add(this.edtGpuSmoothConductance);
            this.panelPropriedadesGPU.Controls.Add(this.label6);
            this.panelPropriedadesGPU.Controls.Add(this.edtGpuSmoothTimestep);
            this.panelPropriedadesGPU.Controls.Add(this.label5);
            this.panelPropriedadesGPU.Controls.Add(this.edtGpuSmoothIterations);
            this.panelPropriedadesGPU.Controls.Add(this.label4);
            this.panelPropriedadesGPU.Controls.Add(this.label3);
            this.panelPropriedadesGPU.Location = new System.Drawing.Point(3, 3);
            this.panelPropriedadesGPU.Name = "panelPropriedadesGPU";
            this.panelPropriedadesGPU.Size = new System.Drawing.Size(232, 92);
            this.panelPropriedadesGPU.TabIndex = 2;
            // 
            // btnAplicarGpuSmooth
            // 
            this.btnAplicarGpuSmooth.Location = new System.Drawing.Point(134, 4);
            this.btnAplicarGpuSmooth.Margin = new System.Windows.Forms.Padding(2);
            this.btnAplicarGpuSmooth.Name = "btnAplicarGpuSmooth";
            this.btnAplicarGpuSmooth.Size = new System.Drawing.Size(56, 19);
            this.btnAplicarGpuSmooth.TabIndex = 7;
            this.btnAplicarGpuSmooth.Text = "aplicar";
            this.btnAplicarGpuSmooth.UseVisualStyleBackColor = true;
            this.btnAplicarGpuSmooth.Click += new System.EventHandler(this.btnAplicarGpuSmooth_Click);
            // 
            // edtGpuSmoothConductance
            // 
            this.edtGpuSmoothConductance.Location = new System.Drawing.Point(87, 66);
            this.edtGpuSmoothConductance.Name = "edtGpuSmoothConductance";
            this.edtGpuSmoothConductance.Size = new System.Drawing.Size(100, 20);
            this.edtGpuSmoothConductance.TabIndex = 6;
            this.edtGpuSmoothConductance.Text = "3";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(14, 66);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(70, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "conductance";
            // 
            // edtGpuSmoothTimestep
            // 
            this.edtGpuSmoothTimestep.Location = new System.Drawing.Point(87, 43);
            this.edtGpuSmoothTimestep.Name = "edtGpuSmoothTimestep";
            this.edtGpuSmoothTimestep.Size = new System.Drawing.Size(100, 20);
            this.edtGpuSmoothTimestep.TabIndex = 4;
            this.edtGpuSmoothTimestep.Text = "0.0125";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(14, 43);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(49, 13);
            this.label5.TabIndex = 3;
            this.label5.Text = "time step";
            // 
            // edtGpuSmoothIterations
            // 
            this.edtGpuSmoothIterations.Location = new System.Drawing.Point(87, 21);
            this.edtGpuSmoothIterations.Name = "edtGpuSmoothIterations";
            this.edtGpuSmoothIterations.Size = new System.Drawing.Size(100, 20);
            this.edtGpuSmoothIterations.TabIndex = 2;
            this.edtGpuSmoothIterations.Text = "5";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 21);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(50, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "iterações";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 4);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(118, 13);
            this.label3.TabIndex = 0;
            this.label3.Text = "Suavização Anistrópica";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(0, 481);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(1010, 23);
            this.progressBar1.TabIndex = 5;
            // 
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(147, 4);
            this.button3.Margin = new System.Windows.Forms.Padding(2);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(66, 19);
            this.button3.TabIndex = 16;
            this.button3.Text = "salvar";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click_1);
            // 
            // formDoDicom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1016, 505);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.panelFiltros);
            this.Controls.Add(this.panelVr);
            this.Controls.Add(this.panelRenderizacao);
            this.Controls.Add(this.panelSuperior);
            this.Name = "formDoDicom";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.formDoDicom_FormClosing);
            this.Shown += new System.EventHandler(this.formDoDicom_Shown);
            this.ResizeEnd += new System.EventHandler(this.formDoDicom_ResizeEnd);
            this.Resize += new System.EventHandler(this.formDoDicom_Resize);
            this.panelSuperior.ResumeLayout(false);
            this.panelSuperior.PerformLayout();
            this.panelFiltros.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panelPropriedadesGPU.ResumeLayout(false);
            this.panelPropriedadesGPU.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelSuperior;
        private System.Windows.Forms.Panel panelRenderizacao;
        private System.Windows.Forms.Button buttonAbrir;
        private System.Windows.Forms.TextBox textBoxPath;
        private System.Windows.Forms.Panel panelVr;
        private System.Windows.Forms.Panel panelFiltros;
        private System.Windows.Forms.Panel panelPropriedadesGPU;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox edtGpuSmoothConductance;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox edtGpuSmoothTimestep;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox edtGpuSmoothIterations;
        private System.Windows.Forms.Button btnAplicarGpuSmooth;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.Button btnAplicarSigmoid;
        private System.Windows.Forms.TextBox edtSigmoidMax;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox edtSigmoidMin;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox edtSimgoidBeta;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox edtSigmoidAlpha;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Button button3;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
    }
}

