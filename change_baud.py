from machine import UART
import time

uart = UART(0, 4800)                          # init with given baudrate
uart.init(4800, bits=8, parity=None, stop=1)  # init with given parameter