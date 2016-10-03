import numpy as np
import matplotlib.pyplot as plt

def processLine(line, timeList, dataList):
    lineList = line.split(" ")
    if lineList[0] == "//" or lineList[0] == "\n" or lineList[0] == "-----------------------------\n":
        pass
    elif lineList[0] == "get":
        # Get the time of the data.
        timeList.append(int(lineList[len(lineList) - 1]))
    else:
        tmpList = line.split("\t")
        # Remove \n.
        tmpList.pop()
        binStr = "";
        for i in range(0, len(tmpList)):
            tmpList[i] = int(tmpList[i], 16)
            binStr += np.binary_repr(tmpList[i], width = 8)
        dataList.append(binStr)

fd = open('steeringWheel.txt', 'r')
print fd
# timeList contains the time in ms. This is the x-axis data.
timeList = []
# dataList contains the binary format of the input 8-bytes data.
dataList = []
for line in fd:
    processLine(line, timeList, dataList)
