using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.IO.Ports;
using System.IO;
using System.Windows.Forms;

namespace Measure
{
    public partial class Form1 : Form
    {
        const string VOLTAGE_LOG_DIR = "Voltage";
        const double BAD_PULSES_LOWER_VOLTAGE_THRESHOLD = 2.3;
        private SerialPort port;
        private StreamWriter voltageLogFile = null;
        private string pulseLengthData;
        private string dacOutputData;
        private string pulseIntervalData;
        private bool shouldSkipBadPulses = false;
        private Task simulationTask = null;
        private bool isClosing = false;
        private bool isRealTag = true;

        public Form1()
        {
            InitializeComponent();
            comPortComboBox.Items.AddRange(SerialPort.GetPortNames());
            if (comPortComboBox.Items.Count > 0)
                comPortComboBox.SelectedItem = comPortComboBox.Items[0];
        }

        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string line = port.ReadLine().Replace("\r", "");
            string[] s = line.Split(',');

            if (s.Length < 2)
                return;
            string date = DateTime.Now.ToString();
            voltageLogFile.WriteLine(date + "," + line);
            voltageLogFile.Flush();
        }

        private delegate void updateMeasure(string voltage, string current, string date, string[] fullData);

        private void updateSampleData()
        {
            pulseIntervalData = pulseIntervalTextBox.Text;
            dacOutputData = dacTextBox.Text;
            pulseLengthData = pulseTextBox.Text;
            shouldSkipBadPulses = skipBadPulsesCheckBox.Checked;
        }

        private void goButton_Click(object sender, EventArgs e)
        {
            updateSampleData();
            port = new SerialPort(comPortComboBox.SelectedItem.ToString(), 14400, Parity.None, 8, StopBits.One);

            if (!Directory.Exists(VOLTAGE_LOG_DIR))
            {
                Directory.CreateDirectory(VOLTAGE_LOG_DIR);
            }

            goButton.Enabled = false;
            checkBox1.Enabled = false;

            voltageLogFile = File.CreateText(Path.Combine(VOLTAGE_LOG_DIR, DateTime.Now.ToString("dd-MM-yyyy_HH-mm-ss") + ".txt"));
            voltageLogFile.WriteLine("date,voltage,current");

            // Begin communications
            port.Open();
            port.DtrEnable = true;
            port.RtsEnable = true;

            port.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
            OperatingSystem osVersion = Environment.OSVersion;
            if (!osVersion.VersionString.Contains("Windows"))
            {
                Console.WriteLine(osVersion.VersionString);
                Task.Run(() => {
                    while (true)
                    {
                        if (isClosing)
                            return;

                        if (port.BytesToRead > 0)
                            port_DataReceived(null, null);

                        Thread.Sleep(50);
                    }
                });
            }


            goButton.Enabled = false;

            port.WriteLine(isRealTag ? "yes" : "no");

            createSimulationTaskIfNeeded();
        }

        private void createSimulationTaskIfNeeded()
        {
            if (isRealTag)
                return;

            simulationTask = Task.Run(() => {
                while (true)
                {
                    string d = Volatile.Read(ref dacOutputData);
                    port.WriteLine(d);
                    port.WriteLine(Volatile.Read(ref pulseLengthData));

                    double bad_pulses_threshold = Volatile.Read(ref shouldSkipBadPulses) ? BAD_PULSES_LOWER_VOLTAGE_THRESHOLD : 0.0;
                    port.WriteLine(bad_pulses_threshold.ToString());
                    Thread.Sleep(int.Parse(Volatile.Read(ref pulseIntervalData)));
                }
            });
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (voltageLogFile != null)
            {
                voltageLogFile.Dispose();
                port.Close();
            }
        }

        private void genericTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            if (!char.IsControl(e.KeyChar) && !char.IsDigit(e.KeyChar))
            {
                e.Handled = true;
            }
        }

        private void updateButton_Click(object sender, EventArgs e)
        {
            updateSampleData();
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            simulationPanel.Enabled = !simulationPanel.Enabled;
            isRealTag = !isRealTag;
            //createSimulationTaskIfNeeded();
        }
    }
}
