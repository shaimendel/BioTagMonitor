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
using LiveCharts; //Core of the library
using LiveCharts.Wpf; //The WPF controls
using LiveCharts.WinForms; //the WinForm wrappers

namespace MeasureGraph
{
    public partial class Form1 : Form
    {
        const string VOLTAGE_LOG_DIR = "Voltage";
        private SerialPort port;
        private StreamWriter voltageLogFile = null;
        private bool shouldViewGraph = false;
        private string pulseLengthData;
        private string dacOutputData;
        private string pulseIntervalData;
        private Task simulationTask = null;
        private bool isRealTag = true;

        struct Pulse {
            public string voltage;
            public string current;
            public string date;
            public string[] fullData;
        }

        private List<Pulse> pulses = new List<Pulse>();

        public Form1()
        {
            InitializeComponent();
            comPortComboBox.Items.AddRange(SerialPort.GetPortNames());
            if (comPortComboBox.Items.Count > 0)
                comPortComboBox.SelectedItem = comPortComboBox.Items[0];

            measureChart.Series = new SeriesCollection
            {
                new LineSeries // Voltage
                {
                    Title = "Voltage",
                    Values = new ChartValues<double> { }
                },
                new LineSeries // Current
                {
                    Title = "Current",
                    Values = new ChartValues<double> { }
                },
                new LineSeries // Voltage In Rest
                {
                    Title = "Voltage In Rest",
                    Values = new ChartValues<double> { }
                }
            };

            measureChart.AxisX.Add(new Axis
            {
                Title = "Time",
                Labels = new ChartValues<string> { }
            });

            measureChart.AxisY.Add(new Axis
            {
                Title = "Voltage/Current during peak",
            });            
        }

        private void port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string line = port.ReadLine().Replace("\r", "");
            string[] s = line.Split(',');
            
            if (s.Length < 4)
                return;
            string date = DateTime.Now.ToString();
            voltageLogFile.WriteLine(date + "," + line);
            voltageLogFile.Flush();

            if (!shouldViewGraph)
                return;

            object[] data = { s[0], s[1], s[3], date, s };
            BeginInvoke(new updateMeasure(addMeasure), data);
        }

        private void removeMeasures()
        {
            measureChart.AxisX[0].Labels.Clear();
            measureChart.Series[0].Values.Clear();
            measureChart.Series[1].Values.Clear();
        }

        private void addMeasure(string voltage, string current, string voltageInRest, string date, string[] fullData)
        {
            measureChart.AxisX[0].Labels.Add(date);
            measureChart.Series[0].Values.Add(double.Parse(voltage));
            measureChart.Series[1].Values.Add(double.Parse(current));
            measureChart.Series[2].Values.Add(double.Parse(voltageInRest));

            pulses.Add(new Pulse
            {
                voltage = voltage,
                current = current,
                date = date,
                fullData = fullData
            });
        }
        private delegate void updateMeasure(string voltage, string current, string voltageInRest, string date, string[] fullData);

        private void updateSampleData()
        {
            pulseIntervalData = pulseIntervalTextBox.Text;
            dacOutputData = dacTextBox.Text;
            pulseLengthData = pulseTextBox.Text;
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
            //simulationPanel.Enabled = false;
            checkBox1.Enabled = false;

            voltageLogFile = File.CreateText(Path.Combine(VOLTAGE_LOG_DIR, DateTime.Now.ToString("dd-MM-yyyy_HH-mm-ss") + ".txt"));
            voltageLogFile.WriteLine("date,voltage,current");

            // Begin communications
            port.Open();
            port.DtrEnable = true;
            port.RtsEnable = true;

            port.DataReceived += new SerialDataReceivedEventHandler(port_DataReceived);
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
                    Thread.Sleep(int.Parse(Volatile.Read(ref pulseIntervalData)));
                }
            });
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (voltageLogFile != null)
            {
                port.Close();
                voltageLogFile.Dispose();
            }
        }

        private void drawCheckBox_CheckedChanged(object sender, EventArgs e)
        {
            shouldViewGraph = !shouldViewGraph;
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

        private void measureChart_DataClick(object sender, ChartPoint p)
        {
            var sample = pulses[(int)p.X];
            (new SampleForm(sample.voltage, sample.current, sample.date, sample.fullData)).Show();
        }
    }
}
