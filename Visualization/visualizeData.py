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

	def drawPulse(self, pulse, pulseIndex):
		microsFromStart = []
		voltage = []
		current = []

		for sample in pulse:
			if sample.startswith("*") or not sample.strip():
				return
			[sampleVoltage, sampleCurrent, sampleTime] = sample.split("@")
			voltage.append(float(sampleVoltage))
			current.append(float(sampleCurrent)/11)
			microsFromStart.append(int(sampleTime))

		fig2, ax2 = plt.subplots()
		volt_in_pulse = ax2.plot(microsFromStart, voltage, "r", label = "Voltage In Pulse")
		ax2.set_ylim(0, 3.5)
		ax2.set_ylabel('Voltage', color='r')


		ax3 = ax2.twinx()
		curr_in_pulse = ax3.plot(microsFromStart, current, "b", label = "Current In Pulse")
		ax3.set_ylabel('Current', color='b')
		ax3.set_ylim(0, 0.3)

		fig2.tight_layout()

		lns = curr_in_pulse+volt_in_pulse
		labs = [l.get_label() for l in lns]
		leg = plt.legend(lns, labs, loc='best', ncol=2, mode="expand", shadow=True, fancybox=True)
		leg.get_frame().set_alpha(0.5)

		plt.title("Sample no " + str(pulseIndex))
		plt.xlabel("Micros From Start")
		
		plt.show()

	def onpick(self, event):
		line = event.artist
		xdata, ydata = line.get_data()
		ind = event.ind[0]

		self.drawPulse(self.pulses[ind], ind)

	def showSinglePoint(self, pulse):
		self.drawPulse(pulse, 0)
		


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
			if (len(splittedRow) < 4):
				continue
			voltInPulse.append(float(splittedRow[1]))
			currentInPulse.append(float(splittedRow[2])/11)
			voltInRest.append(float(splittedRow[4]))

			if not showAllData or len(text) == 1:
				pulses.append(splittedRow[5:])
			currDate = datetime.strptime(splittedRow[0], TIME_FORMAT)
			if firstDate:
				x.append((currDate - firstDate).total_seconds())
			else:
				firstDate = currDate

	if len(pulses) == 1:
		browser = PointBrowser(pulses)
		browser.showSinglePoint(pulses[0])
		return

	fig, ax = plt.subplots()
	curr_in_pulse = ax.plot(x, currentInPulse, "b", label = "Current In Pulse")
	ax.set_ylabel('Current', color='b')
	ax.set_ylim(0, 0.3)

	ax2 = ax.twinx()
	volt_in_pulse = ax2.plot(x, voltInPulse, "r", label = "Voltage In Pulse", picker=1)
	ax2.set_ylim(0, 3.5)
	volt_in_rest = ax2.plot(x, voltInRest, "g", label = "Voltage In Rest")
	ax2.set_ylabel('Voltage', color='r')
	fig.tight_layout()

	lns = curr_in_pulse+volt_in_pulse+volt_in_rest
	labs = [l.get_label() for l in lns]
	leg = plt.legend(lns, labs, loc='best', ncol=2, mode="expand", shadow=True, fancybox=True)
	leg.get_frame().set_alpha(0.5)

	plt.title(basename(FILE_NAME))
	plt.xlabel("Seconds From Start")

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
parser.add_argument("--os", nargs='?',
						const=True, default="windows", dest="os",
						help="The OS the log captured on. windows/linux")

args = parser.parse_args()

FILE_NAME = args.filepath;

if args.os.lower() == "windows":
	TIME_FORMAT = TIME_FORMAT_WINDOWS
else:
	TIME_FORMAT = TIME_FORMAT_LINUX

displayGraph(args.isFull)