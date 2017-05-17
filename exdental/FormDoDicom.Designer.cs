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
            this.button2 = new System.Windows.Forms.Button();
            this.panelSuperior.SuspendLayout();
            this.panelInferior.SuspendLayout();
            this.panelFiltros.SuspendLayout();
            this.SuspendLayout();
            // 
            // panelSuperior
            // 
            this.panelSuperior.Controls.Add(this.buttonAbrir);
            this.panelSuperior.Controls.Add(this.textBoxPath);
            this.panelSuperior.Dock = System.Windows.Forms.DockStyle.Top;
            this.panelSuperior.Location = new System.Drawing.Point(0, 0);
            this.panelSuperior.Margin = new System.Windows.Forms.Padding(4);
            this.panelSuperior.Name = "panelSuperior";
            this.panelSuperior.Size = new System.Drawing.Size(1469, 36);
            this.panelSuperior.TabIndex = 0;
            // 
            // buttonAbrir
            // 
            this.buttonAbrir.Location = new System.Drawing.Point(644, 0);
            this.buttonAbrir.Margin = new System.Windows.Forms.Padding(4);
            this.buttonAbrir.Name = "buttonAbrir";
            this.buttonAbrir.Size = new System.Drawing.Size(100, 25);
            this.buttonAbrir.TabIndex = 1;
            this.buttonAbrir.Text = "Abrir";
            this.buttonAbrir.UseVisualStyleBackColor = true;
            this.buttonAbrir.Click += new System.EventHandler(this.buttonAbrir_Click);
            // 
            // textBoxPath
            // 
            this.textBoxPath.Location = new System.Drawing.Point(0, 0);
            this.textBoxPath.Margin = new System.Windows.Forms.Padding(4);
            this.textBoxPath.Name = "textBoxPath";
            this.textBoxPath.Size = new System.Drawing.Size(635, 22);
            this.textBoxPath.TabIndex = 0;
            // 
            // panelRenderizacao
            // 
            this.panelRenderizacao.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(192)))), ((int)(((byte)(192)))));
            this.panelRenderizacao.Location = new System.Drawing.Point(358, 44);
            this.panelRenderizacao.Margin = new System.Windows.Forms.Padding(4);
            this.panelRenderizacao.Name = "panelRenderizacao";
            this.panelRenderizacao.Size = new System.Drawing.Size(563, 513);
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
            this.panelInferior.Location = new System.Drawing.Point(0, 565);
            this.panelInferior.Margin = new System.Windows.Forms.Padding(4);
            this.panelInferior.Name = "panelInferior";
            this.panelInferior.Size = new System.Drawing.Size(1469, 36);
            this.panelInferior.TabIndex = 2;
            // 
            // txtLevel
            // 
            this.txtLevel.Location = new System.Drawing.Point(571, 5);
            this.txtLevel.Margin = new System.Windows.Forms.Padding(4);
            this.txtLevel.Name = "txtLevel";
            this.txtLevel.Size = new System.Drawing.Size(132, 22);
            this.txtLevel.TabIndex = 3;
            this.txtLevel.TextChanged += new System.EventHandler(this.txtLevel_TextChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(524, 9);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(37, 17);
            this.label2.TabIndex = 2;
            this.label2.Text = "level";
            // 
            // txtWindow
            // 
            this.txtWindow.Location = new System.Drawing.Point(373, 5);
            this.txtWindow.Margin = new System.Windows.Forms.Padding(4);
            this.txtWindow.Name = "txtWindow";
            this.txtWindow.Size = new System.Drawing.Size(132, 22);
            this.txtWindow.TabIndex = 1;
            this.txtWindow.TextChanged += new System.EventHandler(this.txtWindow_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(317, 9);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(53, 17);
            this.label1.TabIndex = 0;
            this.label1.Text = "window";
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(0, 4);
            this.progressBar.Margin = new System.Windows.Forms.Padding(4);
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(309, 28);
            this.progressBar.TabIndex = 0;
            // 
            // panelVr
            // 
            this.panelVr.Location = new System.Drawing.Point(928, 43);
            this.panelVr.Name = "panelVr";
            this.panelVr.Size = new System.Drawing.Size(529, 515);
            this.panelVr.TabIndex = 3;
            // 
            // panelFiltros
            // 
            this.panelFiltros.Controls.Add(this.button2);
            this.panelFiltros.Controls.Add(this.button1);
            this.panelFiltros.Location = new System.Drawing.Point(0, 43);
            this.panelFiltros.Name = "panelFiltros";
            this.panelFiltros.Size = new System.Drawing.Size(351, 514);
            this.panelFiltros.TabIndex = 4;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(13, 23);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 0;
            this.button1.Text = "button1";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(13, 53);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(75, 23);
            this.button2.TabIndex = 1;
            this.button2.Text = "button2";
            this.button2.UseVisualStyleBackColor = true;
            // 
            // formDoDicom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1469, 601);
            this.Controls.Add(this.panelFiltros);
            this.Controls.Add(this.panelVr);
            this.Controls.Add(this.panelInferior);
            this.Controls.Add(this.panelRenderizacao);
            this.Controls.Add(this.panelSuperior);
            this.Margin = new System.Windows.Forms.Padding(4);
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
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button button1;
    }
}

