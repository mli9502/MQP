import serial
import thread
import time
from interpData import convAngle
from interpData import convSpeed

str1 = '/dev/ttyUSB2'
str2 = '/dev/ttyUSB3'
def printMsg(port):
    ser = serial.Serial(port, 115200, timeout=1)
    ser.write('ATZ \r')
    time.sleep(1)
    if port == str1:
        ser.write('ATCRA 0AA \r')
        fd = open('speed.txt', 'w')
    else:
        ser.write('ATCRA 025 \r')
        fd = open('sw.txt', 'w')
    time.sleep(1)
    ser.write('ATMA \r')
    time.sleep(1)
    buff = []
    while True:
        rtn = ser.read()
        if rtn == '\r':
            if port == str1:
                val = convSpeed(buff)
            else:
                val = convAngle(buff)
            fd.write(val)
            fd.write('\n')
            print(val);
            buff = []
        else:
            buff.append(rtn)

try:
    thread.start_new_thread(printMsg, (str1,))
    thread.start_new_thread(printMsg, (str2,))
except:
    print('error')

while 1:
    pass