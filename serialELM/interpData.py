import binascii
from bitstring import BitArray

def convAngle(hexArr):
    if len(hexArr) == 3:
        hexStr = ''.join([hexArr[0], hexArr[1]])
        return int(hexStr, 16) + 255    
    elif len(hexArr) >= 4:
        fir2Bytes = ''.join(hexArr[0:2])
        sec2Bytes = ''.join(hexArr[3:5])
        if fir2Bytes == '00':
            return int(sec2Bytes, 16)
        elif fir2Bytes == '0E':
            binStr = '10' + format(int(sec2Bytes, 16), '0>8b')
            bitArr = BitArray(bin=binStr)
            return bitArr.int
        else:
            binStr = '1' + format(int(sec2Bytes, 16), '0>8b')
            bitArr = BitArray(bin=binStr)
            return bitArr.int

def convSpeed(hexArr):
    # Need to modifiy this latter.
    return ''.join(hexArr)
