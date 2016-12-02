import serial
import thread
import time

str1 = '/dev/ttyUSB2'
str2 = '/dev/ttyUSB3'
def printMsg(msg):
    ser = serial.Serial(msg, 115200, timeout=1)
    ser.write('ATZ \r')
    time.sleep(1)
    if msg == str1:
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
            val = ''.join(buff)
            fd.write(val)
            fd.write('\n')
            # print(val)
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