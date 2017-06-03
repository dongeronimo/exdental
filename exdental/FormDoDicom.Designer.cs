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
            this.buttonAbrir = new System.Windows.Forms.Button();
            this.textBoxPath = new System.Windows.Forms.TextBox();
            this.panelRenderizacao = new System.Windows.Forms.Panel();
            this.panelInferior = new System.Windows.Forms.Panel();
            this.txtLevel = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txtWindow = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.panelVr = new System.Windows.Forms.Panel();
            this.panelFiltros = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.panelPropriedadesGPU = new System.Windows.Forms.Panel();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.edtGpuSmoothIterations = new System.Windows.Forms.TextBox();
            this.edtGpuSmoothTimestep = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.edtGpuSmoothConductance = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.btnAplicarGpuSmooth = new System.Windows.Forms.Button();
            this.panelSuperior.SuspendLayout();
            this.panelInferior.SuspendLayout();
            this.panelFiltros.SuspendLayout();
            this.panelPropriedadesGPU.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelSuperior
            // 
            this.panelSuperior.Controls.Add(this.buttonAbrir);
            this.panelSuperior.Controls.Add(this.textBoxPath);
            this.panelSuperior.Dock = System.Windows.Forms.DockStyle.Top;
            this.panelSuperior.Location = new System.Drawing.Point(0, 0);
            this.panelSuperior.Name = "panelSuperior";
            this.panelSuperior.Size = new System.Drawing.Size(1022, 29);
            this.panelSuperior.TabIndex = 0;
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
            this.panelRenderizacao.Location = new System.Drawing.Point(268, 36);
            this.panelRenderizacao.Name = "panelRenderizacao";
            this.panelRenderizacao.Size = new System.Drawing.Size(422, 417);
            this.panelRenderizacao.TabIndex = 1;
            this.panelRenderizacao.Paint += new System.Windows.Forms.PaintEventHandler(this.panelRenderizacao_Paint);
            // 
            // panelInferior
            // 
            this.panelInferior.Controls.Add(this.txtLevel);
            this.panelInferior.Controls.Add(this.label2);
            this.panelInferior.Controls.Add(this.txtWindow);
            this.panelInferior.Controls.Add(this.label1);
            this.panelInferior.Controls.Add(this.progressBar);
            this.panelInferior.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.panelInferior.Location = new System.Drawing.Point(0, 459);
            this.panelInferior.Name = "panelInferior";
            this.panelInferior.Size = new System.Drawing.Size(1022, 29);
            this.panelInferior.TabIndex = 2;
            // 
            // txtLevel
            // 
            this.txtLevel.Location = new System.Drawing.Point(428, 4);
            this.txtLevel.Name = "txtLevel";
            this.txtLevel.Size = new System.Drawing.Size(100, 20);
            this.txtLevel.TabIndex = 3;
            this.txtLevel.TextChanged += new System.EventHandler(this.txtLevel_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(393, 7);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(29, 13);
            this.label2.TabIndex = 2;
            this.label2.Text = "level";
            // 
            // txtWindow
            // 
            this.txtWindow.Location = new System.Drawing.Point(280, 4);
            this.txtWindow.Name = "txtWindow";
            this.txtWindow.Size = new System.Drawing.Size(100, 20);
            this.txtWindow.TabIndex = 1;
            this.txtWindow.TextChanged += new System.EventHandler(this.txtWindow_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(238, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(43, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "window";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(0, 3);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(232, 23);
            this.progressBar.TabIndex = 0;
            // 
            // panelVr
            // 
            this.panelVr.Location = new System.Drawing.Point(696, 35);
            this.panelVr.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.panelVr.Name = "panelVr";
            this.panelVr.Size = new System.Drawing.Size(397, 418);
            this.panelVr.TabIndex = 3;
            // 
            // panelFiltros
            // 
            this.panelFiltros.Controls.Add(this.panelPropriedadesGPU);
            this.panelFiltros.Controls.Add(this.button1);
            this.panelFiltros.Location = new System.Drawing.Point(0, 35);
            this.panelFiltros.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.panelFiltros.Name = "panelFiltros";
            this.panelFiltros.Size = new System.Drawing.Size(263, 418);
            this.panelFiltros.TabIndex = 4;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(87, 110);
            this.button1.Margin = new System.Windows.Forms.Padding(2, 2, 2, 2);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(56, 19);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
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
            this.panelPropriedadesGPU.Size = new System.Drawing.Size(260, 100);
            this.panelPropriedadesGPU.TabIndex = 2;
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
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(14, 21);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(50, 13);
            this.label4.TabIndex = 1;
            this.label4.Text = "iterações";
            // 
            // edtGpuSmoothIterations
            // 
            this.edtGpuSmoothIterations.Location = new System.Drawing.Point(87, 21);
            this.edtGpuSmoothIterations.Name = "edtGpuSmoothIterations";
            this.edtGpuSmoothIterations.Size = new System.Drawing.Size(100, 20);
            this.edtGpuSmoothIterations.TabIndex = 2;
            this.edtGpuSmoothIterations.Text = "5";
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
            // btnAplicarGpuSmooth
            // 
            this.btnAplicarGpuSmooth.Location = new System.Drawing.Point(202, 4);
            this.btnAplicarGpuSmooth.Margin = new System.Windows.Forms.Padding(2);
            this.btnAplicarGpuSmooth.Name = "btnAplicarGpuSmooth";
            this.btnAplicarGpuSmooth.Size = new System.Drawing.Size(56, 19);
            this.btnAplicarGpuSmooth.TabIndex = 7;
            this.btnAplicarGpuSmooth.Text = "aplicar";
            this.btnAplicarGpuSmooth.UseVisualStyleBackColor = true;
            this.btnAplicarGpuSmooth.Click += new System.EventHandler(this.btnAplicarGpuSmooth_Click);
            // 
            // formDoDicom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1022, 488);
            this.Controls.Add(this.panelFiltros);
            this.Controls.Add(this.panelVr);
            this.Controls.Add(this.panelInferior);
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
            this.panelInferior.ResumeLayout(false);
            this.panelInferior.PerformLayout();
            this.panelFiltros.ResumeLayout(false);
            this.panelPropriedadesGPU.ResumeLayout(false);
            this.panelPropriedadesGPU.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel panelSuperior;
        private System.Windows.Forms.Panel panelRenderizacao;
        private System.Windows.Forms.Panel panelInferior;
        private System.Windows.Forms.Button buttonAbrir;
        private System.Windows.Forms.TextBox textBoxPath;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.TextBox txtLevel;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtWindow;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Panel panelVr;
        private System.Windows.Forms.Panel panelFiltros;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Panel panelPropriedadesGPU;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox edtGpuSmoothConductance;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox edtGpuSmoothTimestep;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox edtGpuSmoothIterations;
        private System.Windows.Forms.Button btnAplicarGpuSmooth;
    }
}

