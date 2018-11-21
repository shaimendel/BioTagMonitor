namespace Measure
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
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.simulationPanel = new System.Windows.Forms.Panel();
            this.updateButton = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.pulseTextBox = new System.Windows.Forms.TextBox();
            this.pulseIntervalTextBox = new System.Windows.Forms.TextBox();
            this.dacTextBox = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.goButton = new System.Windows.Forms.Button();
            this.comPortComboBox = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.skipBadPulsesCheckBox = new System.Windows.Forms.CheckBox();
            this.simulationPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(209, 184);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(95, 21);
            this.checkBox1.TabIndex = 21;
            this.checkBox1.Text = "Simulation";
            this.checkBox1.UseVisualStyleBackColor = true;
            this.checkBox1.CheckedChanged += new System.EventHandler(this.checkBox1_CheckedChanged);
            // 
            // simulationPanel
            // 
            this.simulationPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.simulationPanel.Controls.Add(this.skipBadPulsesCheckBox);
            this.simulationPanel.Controls.Add(this.updateButton);
            this.simulationPanel.Controls.Add(this.label2);
            this.simulationPanel.Controls.Add(this.label4);
            this.simulationPanel.Controls.Add(this.pulseTextBox);
            this.simulationPanel.Controls.Add(this.pulseIntervalTextBox);
            this.simulationPanel.Controls.Add(this.dacTextBox);
            this.simulationPanel.Controls.Add(this.label3);
            this.simulationPanel.Enabled = false;
            this.simulationPanel.Location = new System.Drawing.Point(12, 22);
            this.simulationPanel.Name = "simulationPanel";
            this.simulationPanel.Size = new System.Drawing.Size(415, 153);
            this.simulationPanel.TabIndex = 20;
            // 
            // updateButton
            // 
            this.updateButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.updateButton.BackColor = System.Drawing.Color.DarkSeaGreen;
            this.updateButton.Location = new System.Drawing.Point(246, 9);
            this.updateButton.Name = "updateButton";
            this.updateButton.Size = new System.Drawing.Size(155, 139);
            this.updateButton.TabIndex = 15;
            this.updateButton.Text = "Update";
            this.updateButton.UseVisualStyleBackColor = false;
            this.updateButton.MouseClick += new System.Windows.Forms.MouseEventHandler(this.updateButton_Click);
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(11, 9);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(123, 17);
            this.label2.TabIndex = 9;
            this.label2.Text = "Pulse Length (ms)";
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(9, 84);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(125, 17);
            this.label4.TabIndex = 13;
            this.label4.Text = "Pulse Interval (ms)";
            // 
            // pulseTextBox
            // 
            this.pulseTextBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.pulseTextBox.Location = new System.Drawing.Point(140, 6);
            this.pulseTextBox.Name = "pulseTextBox";
            this.pulseTextBox.Size = new System.Drawing.Size(100, 22);
            this.pulseTextBox.TabIndex = 8;
            this.pulseTextBox.Text = "8";
            this.pulseTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.genericTextBox_KeyPress);
            // 
            // pulseIntervalTextBox
            // 
            this.pulseIntervalTextBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.pulseIntervalTextBox.Location = new System.Drawing.Point(140, 83);
            this.pulseIntervalTextBox.Name = "pulseIntervalTextBox";
            this.pulseIntervalTextBox.Size = new System.Drawing.Size(100, 22);
            this.pulseIntervalTextBox.TabIndex = 12;
            this.pulseIntervalTextBox.Text = "1000";
            this.pulseIntervalTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.genericTextBox_KeyPress);
            // 
            // dacTextBox
            // 
            this.dacTextBox.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.dacTextBox.Location = new System.Drawing.Point(140, 44);
            this.dacTextBox.Name = "dacTextBox";
            this.dacTextBox.Size = new System.Drawing.Size(100, 22);
            this.dacTextBox.TabIndex = 10;
            this.dacTextBox.Text = "23";
            this.dacTextBox.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.genericTextBox_KeyPress);
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(11, 47);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(83, 17);
            this.label3.TabIndex = 11;
            this.label3.Text = "DAC Output";
            // 
            // goButton
            // 
            this.goButton.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.goButton.BackColor = System.Drawing.Color.DarkSeaGreen;
            this.goButton.Location = new System.Drawing.Point(453, 22);
            this.goButton.Name = "goButton";
            this.goButton.Size = new System.Drawing.Size(159, 127);
            this.goButton.TabIndex = 18;
            this.goButton.Text = "Go";
            this.goButton.UseVisualStyleBackColor = false;
            this.goButton.MouseClick += new System.Windows.Forms.MouseEventHandler(this.goButton_Click);
            // 
            // comPortComboBox
            // 
            this.comPortComboBox.FormattingEnabled = true;
            this.comPortComboBox.Location = new System.Drawing.Point(84, 181);
            this.comPortComboBox.Name = "comPortComboBox";
            this.comPortComboBox.Size = new System.Drawing.Size(121, 24);
            this.comPortComboBox.TabIndex = 17;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(11, 183);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 17);
            this.label1.TabIndex = 16;
            this.label1.Text = "Com Port";
            // 
            // skipBadPulsesCheckBox
            // 
            this.skipBadPulsesCheckBox.AutoSize = true;
            this.skipBadPulsesCheckBox.Location = new System.Drawing.Point(12, 127);
            this.skipBadPulsesCheckBox.Name = "skipBadPulsesCheckBox";
            this.skipBadPulsesCheckBox.Size = new System.Drawing.Size(132, 21);
            this.skipBadPulsesCheckBox.TabIndex = 17;
            this.skipBadPulsesCheckBox.Text = "Skip Bad Pulses";
            this.skipBadPulsesCheckBox.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(624, 231);
            this.Controls.Add(this.checkBox1);
            this.Controls.Add(this.simulationPanel);
            this.Controls.Add(this.goButton);
            this.Controls.Add(this.comPortComboBox);
            this.Controls.Add(this.label1);
            this.Name = "Form1";
            this.Text = "Tag Measure";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.simulationPanel.ResumeLayout(false);
            this.simulationPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.Panel simulationPanel;
        private System.Windows.Forms.Button updateButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox pulseTextBox;
        private System.Windows.Forms.TextBox pulseIntervalTextBox;
        private System.Windows.Forms.TextBox dacTextBox;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button goButton;
        private System.Windows.Forms.ComboBox comPortComboBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.CheckBox skipBadPulsesCheckBox;
    }
}

