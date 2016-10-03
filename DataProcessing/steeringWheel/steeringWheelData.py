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
# There are total number of len(dataList[0] - 7) possible ways of getting a byte.
# byteDataList[0] contains all the data using their first byte.
byteDataList = []
for i in range(0, len(dataList[0]) - 7):
    byteDataList.append([])
for i in range(0, len(dataList)):
    for j in range(0, len(dataList[i]) - 7):
        byteDataList[j].append(int(dataList[i][j : j + 8], base = 2))
for i in range(0, len(byteDataList)):
    plt.plot(timeList, byteDataList[i])
    plt.xlabel('time')
    plt.ylabel('data')
    plt.title('plot number ' + str(i))
    plt.show() 

