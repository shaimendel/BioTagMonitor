using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using LiveCharts; //Core of the library
using LiveCharts.Wpf; //The WPF controls
using LiveCharts.WinForms; //the WinForm wrappers

namespace MeasureGraph
{
    public partial class SampleForm : Form
    {
        public SampleForm(string voltage, string current, string date, string[] fullData)
        {
            InitializeComponent();
            sampleChart.Series = new SeriesCollection
            {
                new LineSeries // Voltage
                {
                    Title = "Voltage In Pulse",
                    Values = new ChartValues<double> { }
                },
                new LineSeries // Current
                {
                    Title = "Current",
                    Values = new ChartValues<double> { }
                }
            };

            sampleChart.AxisX.Add(new Axis
            {
                Title = "Time",
                Labels = new ChartValues<string> { }
            });

            sampleChart.AxisY.Add(new Axis
            {
                Title = "Voltage/Current during peak",
            });

            if (fullData[4].StartsWith("*") || String.IsNullOrEmpty(fullData[4].Trim()))
                return;

            for (int i = 4; i < fullData.Length; i++)
            {
                string[] sampleData = fullData[i].Split('@');

                sampleChart.AxisX[0].Labels.Add(sampleData[2]);
                sampleChart.Series[0].Values.Add(double.Parse(sampleData[0]));
                sampleChart.Series[1].Values.Add(double.Parse(sampleData[1]));
            }
        }
    }
}
