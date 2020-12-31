from distorm3 import Decode, Decode16Bits, Decode32Bits, Decode64Bits

l = Decode(0x1000, open("padawanlock", "rb").read(), Decode32Bits)

for i in l:
    print ("0x%08x (%02x) %-20s %s" % (i[0], i[1], i[3], i[2]))

