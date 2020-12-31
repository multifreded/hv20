import sys

hexstr = sys.argv[1]

value = int(hexstr,16)
if value & (1 << 31):
    value -= 1 << 32

print(value)
