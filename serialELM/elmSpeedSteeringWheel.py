import serial
import time

mode = 'steering wheel: '
port = '/dev/ttyUSB2'
baud = 115200
ser = serial.Serial(port, baud, timeout=1)
result = []
buff = []
fd = open('data.txt', 'w')
ser.write('ATZ \r')
time.sleep(1)
ser.write('ATCRA 025 \r')
time.sleep(1)
ser.write('ATMA \r')
time.sleep(1)
# *1.5
# 0F FA
# left most: A3 + FF
# right most: 0E 62
while True:
    rtn = ser.read()
    if rtn == '\r':
        print ''.join(buff)
        '''
        if mode == 'steering wheel: ':
            ser.write('ATCRA 0AA \r')
            mode = 'speed: '
        else:
            ser.write('ATCRA 025 \r')
            mode = 'steering wheel: '
        '''
        buff = []
    else:
        buff.append(rtn)