﻿namespace exdental
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
            this.button3 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.buttonAbrir = new System.Windows.Forms.Button();
            this.textBoxPath = new System.Windows.Forms.TextBox();
            this.panelRenderizacao = new System.Windows.Forms.Panel();
            this.panelVr = new System.Windows.Forms.Panel();
            this.panelFiltros = new System.Windows.Forms.Panel();
            this.panel1 = new System.Windows.Forms.Panel();
            this.label7 = new System.Windows.Forms.Label();
            this.txtLevel = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtWindow = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
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
            this.panelSuperior.SuspendLayout();
            this.panelFiltros.SuspendLayout();
            this.panel1.SuspendLayout();
            this.panelPropriedadesGPU.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelSuperior
            // 
            this.panelSuperior.Controls.Add(this.button3);
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
            // button3
            // 
            this.button3.Location = new System.Drawing.Point(875, 0);
            this.button3.Name = "button3";
            this.button3.Size = new System.Drawing.Size(75, 23);
            this.button3.TabIndex = 4;
            this.button3.Text = "button3";
            this.button3.UseVisualStyleBackColor = true;
            this.button3.Click += new System.EventHandler(this.button3_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(721, 0);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(125, 23);
            this.button2.TabIndex = 3;
            this.button2.Text = "abertura alternativa";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(565, 0);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(149, 23);
            this.button1.TabIndex = 2;
            this.button1.Text = "Salvar pro volview entender";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // buttonAbrir
            // 
            this.buttonAbrir.Location = new System.Drawing.Point(483, 0);
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
            this.textBoxPath.Size = new System.Drawing.Size(477, 20);
            this.textBoxPath.TabIndex = 0;
            // 
            // panelRenderizacao
            // 
            this.panelRenderizacao.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.panelRenderizacao.Location = new System.Drawing.Point(237, 35);
            this.panelRenderizacao.Name = "panelRenderizacao";
            this.panelRenderizacao.Size = new System.Drawing.Size(402, 383);
            this.panelRenderizacao.TabIndex = 1;
            this.panelRenderizacao.Paint += new System.Windows.Forms.PaintEventHandler(this.panelRenderizacao_Paint);
            // 
            // panelVr
            // 
            this.panelVr.Location = new System.Drawing.Point(644, 34);
            this.panelVr.Margin = new System.Windows.Forms.Padding(2);
            this.panelVr.Name = "panelVr";
            this.panelVr.Size = new System.Drawing.Size(367, 384);
            this.panelVr.TabIndex = 3;
            // 
            // panelFiltros
            // 
            this.panelFiltros.Controls.Add(this.panel1);
            this.panelFiltros.Controls.Add(this.txtLevel);
            this.panelFiltros.Controls.Add(this.label2);
            this.panelFiltros.Controls.Add(this.txtWindow);
            this.panelFiltros.Controls.Add(this.label1);
            this.panelFiltros.Controls.Add(this.panelPropriedadesGPU);
            this.panelFiltros.Location = new System.Drawing.Point(0, 35);
            this.panelFiltros.Margin = new System.Windows.Forms.Padding(2);
            this.panelFiltros.Name = "panelFiltros";
            this.panelFiltros.Size = new System.Drawing.Size(232, 383);
            this.panelFiltros.TabIndex = 4;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.label7);
            this.panel1.Location = new System.Drawing.Point(0, 103);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(229, 100);
            this.panel1.TabIndex = 8;
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
            // txtLevel
            // 
            this.txtLevel.Location = new System.Drawing.Point(52, 356);
            this.txtLevel.Name = "txtLevel";
            this.txtLevel.Size = new System.Drawing.Size(100, 20);
            this.txtLevel.TabIndex = 7;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 359);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 13);
            this.label2.TabIndex = 6;
            this.label2.Text = "level";
            // 
            // txtWindow
            // 
            this.txtWindow.Location = new System.Drawing.Point(52, 330);
            this.txtWindow.Name = "txtWindow";
            this.txtWindow.Size = new System.Drawing.Size(100, 20);
            this.txtWindow.TabIndex = 5;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 329);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "window";
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
            this.panelPropriedadesGPU.Location = new System.Drawing.Point(0, 4);
            this.panelPropriedadesGPU.Name = "panelPropriedadesGPU";
            this.panelPropriedadesGPU.Size = new System.Drawing.Size(232, 92);
            this.panelPropriedadesGPU.TabIndex = 2;
            // 
            // btnAplicarGpuSmooth
            // 
            this.btnAplicarGpuSmooth.Location = new System.Drawing.Point(176, 4);
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
            this.progressBar1.Location = new System.Drawing.Point(0, 424);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(1010, 23);
            this.progressBar1.TabIndex = 5;
            // 
            // formDoDicom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1016, 445);
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
            this.panelFiltros.PerformLayout();
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
        private System.Windows.Forms.TextBox txtLevel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtWindow;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button3;
        private System.Windows.Forms.ProgressBar progressBar1;
    }
}

