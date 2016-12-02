import thread
import serial
import binascii
import time

baud = 115200

def convAngle(hexStr):
    

def getSwAngle(port):
    print('1')
    ser = serial.Serial(port, baud, timeout=1)
    buff = []
    print('here')
    fd = open('angle.txt', 'w')
    ser.write('ATZ \r')
    ser.write('ATCRA 025 \r')
    ser.write('ATMA \r')
    print('sw')
    while True:
        rtn = ser.read()
        print(rtn)
        if rtn == '\r':
            if len(buff) >= 24:
                tmp = []
                for i in range(0, 6):
                    tmp.append(buff[i])
                val = ''.join(tmp)
                fd.write(val)
                fd.write('\n')
                print(val)
            if len(buff) == 3:
                fd.write(''.join(buff))
                print(''.join(buff))
            buff = []
        else:
            buff.append(rtn)

def getSpeed(port):
    ser = serial.Serial(port, baud, timeout=1)
    buff = []
    fd = open('speed.txt', 'w')
    ser.write('ATZ \r')
    ser.write('ATCRA 0AA \r')
    ser.write('ATMA \r')
    print('speed')
    while True:
        rtn = ser.read()
        if rtn == '\r':
            val = ''.join(buff)
            fd.write(val)
            fd.write('\n')
            print(val)
            buff = []
        else:
            buff.append(rtn)

print('before start')
try:
    thread.start_new_thread(getSwAngle, ('/dev/ttyUSB0',))
    thread.start_new_thread(getSpeed, ('/dev/ttyUSB1',))
except:
    print('Error')




# *1.5
# 0F FA
# left most: A3 + FF
# right most: 0E 62
