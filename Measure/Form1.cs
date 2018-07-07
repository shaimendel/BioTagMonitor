using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace Measure
{
    public partial class Form1 : Form
    {
        private SerialPort port;

        public Form1()
        {
            InitializeComponent();
            comPortComboBox.Items.AddRange(SerialPort.GetPortNames());
            if (comPortComboBox.Items.Count > 0)
                comPortComboBox.SelectedItem = comPortComboBox.Items[0];
        }

        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            // Show all the incoming data in the port's buffer
            String[] data = { port.ReadExisting() };
            BeginInvoke(new setLog(appendLog), data);
        }

        private void appendLog(String data)
        {
            String formattedData = DateTime.Now.ToString() + "\n" + data;
            richTextBox2.Text = formattedData;
            richTextBox1.AppendText(formattedData);
        }
        private delegate void setLog(String text);

        private void goButton_Click(object sender, EventArgs e)
        {
            port = new SerialPort(comPortComboBox.SelectedItem.ToString(), 9600, Parity.None, 8, StopBits.One);

            // Begin communications
            port.Open();
            port.DtrEnable = true;
            port.RtsEnable = true;

            port.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            return;
            // set the current caret position to the end
            richTextBox1.SelectionStart = richTextBox1.Text.Length;
            // scroll it automatically
            richTextBox1.ScrollToCaret();
        }
    }
}
