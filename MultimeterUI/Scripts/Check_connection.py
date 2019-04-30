#!/usr/bin/env python
import struct
import serial
import time
import sys
ser = serial.Serial()
# Configuration of serial port
ser.port = sys.argv[1]
ser.baudrate = 9600
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_TWO
ser.timeout = 2
ser.xonxoff = False
ser.rtscts = False
ser.dsrdtr = True

try:
	ser.open()
except(e):
	print("Cannot open serial port: {}".format(str(e)))
	exit()

command = "*IDN?\n"

ser.write(command.encode("utf-8"))

ret = ser.read_until().decode("utf-8")

print(ret)

ser.write(':SYST:REM\n'.encode("ASCII"))
ser.write(':MEAS:VOLT:DC?\n'.encode("ASCII"))
print(ser.readline().decode("ASCII"))

ser.close()