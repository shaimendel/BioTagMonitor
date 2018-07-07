namespace MeasureGraph
{
    partial class Form1
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
            this.comPortComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.goButton = new System.Windows.Forms.Button();
            this.measureChart = new LiveCharts.WinForms.CartesianChart();
            this.drawCheckBox = new System.Windows.Forms.CheckBox();
            this.pulseTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.dacTextBox = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.pulseIntervalTextBox = new System.Windows.Forms.TextBox();
            this.panel1 = new System.Windows.Forms.Panel();
            this.updateButton = new System.Windows.Forms.Button();
            this.panel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // comPortComboBox
            // 
            this.comPortComboBox.FormattingEnabled = true;
            this.comPortComboBox.Location = new System.Drawing.Point(84, 24);
            this.comPortComboBox.Name = "comPortComboBox";
            this.comPortComboBox.Size = new System.Drawing.Size(121, 24);
            this.comPortComboBox.TabIndex = 4;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 26);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "Com Port";
            // 
            // goButton
            // 
            this.goButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.goButton.BackColor = System.Drawing.Color.DarkSeaGreen;
            this.goButton.Location = new System.Drawing.Point(1144, 19);
            this.goButton.Name = "goButton";
            this.goButton.Size = new System.Drawing.Size(178, 32);
            this.goButton.TabIndex = 5;
            this.goButton.Text = "Go";
            this.goButton.UseVisualStyleBackColor = false;
            this.goButton.Click += new System.EventHandler(this.goButton_Click);
            // 
            // measureChart
            // 
            this.measureChart.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.measureChart.Location = new System.Drawing.Point(12, 69);
            this.measureChart.Name = "measureChart";
            this.measureChart.Size = new System.Drawing.Size(1310, 709);
            this.measureChart.TabIndex = 6;
            this.measureChart.Text = "measureChart";
            // 
            // drawCheckBox
            // 
            this.drawCheckBox.AutoSize = true;
            this.drawCheckBox.Location = new System.Drawing.Point(215, 25);
            this.drawCheckBox.Name = "drawCheckBox";
            this.drawCheckBox.Size = new System.Drawing.Size(62, 21);
            this.drawCheckBox.TabIndex = 7;
            this.drawCheckBox.Text = "Draw";
            this.drawCheckBox.UseVisualStyleBackColor = true;
            this.drawCheckBox.CheckedChanged += new System.EventHandler(this.drawCheckBox_CheckedChanged);
            // 
            // pulseTextBox
            // 
            this.pulseTextBox.Location = new System.Drawing.Point(127, 12);
            this.pulseTextBox.Name = "pulseTextBox";
            this.pulseTextBox.Size = new System.Drawing.Size(100, 22);
            this.pulseTextBox.TabIndex = 8;
            this.pulseTextBox.Text = "8";
            this.pulseTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.genericTextBox_KeyPress);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 14);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(123, 17);
            this.label2.TabIndex = 9;
            this.label2.Text = "Pulse Length (ms)";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(240, 14);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(83, 17);
            this.label3.TabIndex = 11;
            this.label3.Text = "DAC Output";
            // 
            // dacTextBox
            // 
            this.dacTextBox.Location = new System.Drawing.Point(329, 12);
            this.dacTextBox.Name = "dacTextBox";
            this.dacTextBox.Size = new System.Drawing.Size(100, 22);
            this.dacTextBox.TabIndex = 10;
            this.dacTextBox.Text = "372";
            this.dacTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.genericTextBox_KeyPress);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(445, 16);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(125, 17);
            this.label4.TabIndex = 13;
            this.label4.Text = "Pulse Interval (ms)";
            // 
            // pulseIntervalTextBox
            // 
            this.pulseIntervalTextBox.Location = new System.Drawing.Point(576, 13);
            this.pulseIntervalTextBox.Name = "pulseIntervalTextBox";
            this.pulseIntervalTextBox.Size = new System.Drawing.Size(100, 22);
            this.pulseIntervalTextBox.TabIndex = 12;
            this.pulseIntervalTextBox.Text = "1000";
            this.pulseIntervalTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.genericTextBox_KeyPress);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Controls.Add(this.updateButton);
            this.panel1.Controls.Add(this.label2);
            this.panel1.Controls.Add(this.label4);
            this.panel1.Controls.Add(this.pulseTextBox);
            this.panel1.Controls.Add(this.pulseIntervalTextBox);
            this.panel1.Controls.Add(this.dacTextBox);
            this.panel1.Controls.Add(this.label3);
            this.panel1.Location = new System.Drawing.Point(283, 12);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(855, 46);
            this.panel1.TabIndex = 14;
            // 
            // updateButton
            // 
            this.updateButton.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.updateButton.BackColor = System.Drawing.Color.DarkSeaGreen;
            this.updateButton.Location = new System.Drawing.Point(685, 5);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(155, 32);
            this.updateButton.TabIndex = 15;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = false;
            this.updateButton.Click += new System.EventHandler(this.updateButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1350, 801);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.drawCheckBox);
            this.Controls.Add(this.measureChart);
            this.Controls.Add(this.goButton);
            this.Controls.Add(this.comPortComboBox);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Tag Measure";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox comPortComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button goButton;
        private LiveCharts.WinForms.CartesianChart measureChart;
        private System.Windows.Forms.CheckBox drawCheckBox;
        private System.Windows.Forms.TextBox pulseTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox dacTextBox;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox pulseIntervalTextBox;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button updateButton;
    }
}

