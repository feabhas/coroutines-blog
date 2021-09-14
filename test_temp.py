import struct
import sys

start = 0.0
for ms, value in enumerate([20.1, 20.9, 20.8, 21.1]):
    sys.stdout.buffer.write(struct.pack('>ff', start + ms*0.1, value))
