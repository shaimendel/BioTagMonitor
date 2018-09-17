import numpy as np
import matplotlib.pyplot as plt
from os.path import basename
from datetime import datetime,timedelta
import sys
import argparse

FILE_NAME = r'c:\Projects\private\thesis\BioTagMonitor\MeasureGraph\bin\Debug\Voltage\29-08-2018_19-50-48.txt'
REDUCE_FACTOR = 4
TIME_FORMAT_LINUX = '%m/%d/%Y %I:%M:%S %p'
TIME_FORMAT_WINDOWS = '%d/%m/%Y %H:%M:%S'

TIME_FORMAT = TIME_FORMAT_WINDOWS

class PointBrowser(object):
	"""
	Click on a point to select and highlight it -- the data that
	generated the point will be shown in the lower axes.  Use the 'n'
	and 'p' keys to browse through the next and previous points
	"""

	def __init__(self, pulses):
		self.pulses = pulses

	def onpick(self, event):
		line = event.artist
		xdata, ydata = line.get_data()
		ind = event.ind[0]

		microsFromStart = []
		voltage = []
		current = []

		for sample in self.pulses[ind]:
			if sample.startswith("*") or not sample.strip():
				return
			[sampleVoltage, sampleCurrent, sampleTime] = sample.split("@")
			voltage.append(float(sampleVoltage))
			current.append(float(sampleCurrent))
			microsFromStart.append(int(sampleTime))

		fig2, ax2 = plt.subplots()
		ax2.plot(microsFromStart, voltage, "r", label = "Voltage In Pulse")
		ax2.set_ylim(0, 3.5)
		ax2.plot(microsFromStart, current, "b", label = "Current In Pulse")

		leg2 = plt.legend(loc='best', ncol=2, mode="expand", shadow=True, fancybox=True)
		leg2.get_frame().set_alpha(0.5)

		plt.title("Sample no " + str(ind))
		plt.xlabel("Micros From Start")
		plt.ylabel("Voltage")
		
		plt.show()
		


def displayGraph(showAllData):
	voltInPulse = []
	currentInPulse = []
	voltInRest = []
	pulses = []
	x = [0]
	firstDate = None
	with open(FILE_NAME, 'rb') as inputFile:
		if showAllData:
			text = inputFile.readlines()[1::REDUCE_FACTOR]
		else:
			text = inputFile.readlines()[-3601:][1:]

		for row in text:
			if not row.strip():
				continue
			splittedRow = row.split(",");
			voltInPulse.append(float(splittedRow[1]))
			currentInPulse.append(float(splittedRow[2]))
			voltInRest.append(float(splittedRow[4]))

			if not showAllData:
				pulses.append(splittedRow[5:])
			currDate = datetime.strptime(splittedRow[0], TIME_FORMAT)
			if firstDate:
				x.append((currDate - firstDate).total_seconds())
			else:
				firstDate = currDate

	fig, ax = plt.subplots()
	ax.plot(x, voltInPulse, "r", label = "Voltage In Pulse", picker=1)
	ax.set_ylim(0, 3.5)
	ax.plot(x, currentInPulse, "b", label = "Current In Pulse")
	ax.plot(x, voltInRest, "g", label = "Voltage In Rest")

	leg = plt.legend(loc='best', ncol=2, mode="expand", shadow=True, fancybox=True)
	leg.get_frame().set_alpha(0.5)

	plt.title(basename(FILE_NAME))
	plt.xlabel("Seconds From Start")
	plt.ylabel("Voltage")

	if not showAllData:
		browser = PointBrowser(pulses)
		fig.canvas.mpl_connect('pick_event', browser.onpick)
	
	plt.show()



def str2bool(v):
	if v.lower() in ('yes', 'true', 't', 'y', '1'):
		return True
	elif v.lower() in ('no', 'false', 'f', 'n', '0'):
		return False
	else:
		raise argparse.ArgumentTypeError('Boolean value expected.')

parser = argparse.ArgumentParser(description='Samples Visualizer')
parser.add_argument('filepath', metavar='FILE_PATH',
					help='Samples file path')
parser.add_argument("--full", type=str2bool, nargs='?',
						const=True, default=False, dest="isFull",
						help="Should sample all")

args = parser.parse_args()

FILE_NAME = args.filepath;
displayGraph(args.isFull)