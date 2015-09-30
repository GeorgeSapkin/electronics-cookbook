#!/usr/bin/env python

import smbus
import time

# for RPI rev 1:        bus 0
# for RPI rev 2 and up: bus 1
bus = smbus.SMBus(1)

slave_address = 0x07

while True:
    out_num = 0
    try:
        out_num = input("Enter 1-9: ")
    except NameError:
        continue
    except SyntaxError:
	continue

    if not out_num:
        continue

    bus.write_byte(slave_address, out_num)
    print "Pi > Arduino:", out_num

    time.sleep(.1)

    in_num = bus.read_byte(slave_address)
    print "Arduino > Pi:", in_num
