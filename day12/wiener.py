import owiener
import base64

word_size = 4

n_b64 = 'dbn25TSjDhUge4L68AYooIqwo0HC2mIYxK/ICnc+8/0fZi1CHo/QwiPCcHM94jYdfj3PIQFTri9j/za3oO+3gVK39bj2O9OekGPG2M1GtN0Sp+ltellLl1oV+TBpgGyDt8vcCAR1B6shOJbjPAFqL8iTaW1C4KyGDVQhQrfkXtAdYv3ZaHcV8tC4ztgA4euP9o1q+kZux0fTv31kJSE7K1iJDpGfy1HiJ5gOX5T9fEyzSR0kA3sk3a35qTuUU1OWkH5MqysLVKZXiGcStNErlaggvJb6oKkx1dr9nYbqFxaQHev0EFX4EVfPqQzEzesa9ZAZTtxbwgcV9ZmTp25MZg=='
n_b64_bytes = n_b64.encode('ascii')
n_bytes     = base64.b64decode(n_b64_bytes)

mpz_list = list()
for i in range(0, len(n_bytes), word_size):
    for j in range(0, word_size):
        key = (len(n_bytes) - word_size) - i + j
        mpz_list.append(n_bytes[key])

n_bytes = bytes(mpz_list)
n = int.from_bytes(n_bytes, byteorder='big', signed=False)

e_b64 = 'S/0OzzzDRdsps+I85tNi4d1i3d0Eu8pimcP5SBaqTeBzcADturDYHk1QuoqdTtwX9XY1Wii6AnySpEQ9eUEETYQkTRpq9rBggIkmuFnLygujFT+SI3Z+HLDfMWlBxaPW3Exo5Yqqrzdx4Zze1dqFNC5jJRVEJByd7c6+wqiTnS4dR77mnFaPHt/9IuMhigVisptxPLJ+g9QX4ZJX8ucU6GPSVzzTmwlDIjaenh7L0bC1Uq/euTDUJjzNWnMpHLHnSz2vgxLg4Ztwi91dOpO7KjvdZQ7++nlHRE6zlMHTsnPFSwLwG1ZxnGVdFnuMjEbPA3dcTe54LxOSb2cvZKDZqA=='
e_b64_bytes = e_b64.encode('ascii')
e_bytes     = base64.b64decode(e_b64_bytes)

mpz_list = list()
for i in range(0, len(e_bytes), word_size):
    for j in range(0, word_size):
        key = (len(e_bytes) - word_size) - i + j
        mpz_list.append(e_bytes[key])

e_bytes = bytes(mpz_list)
e = int.from_bytes(e_bytes, byteorder='big', signed=False)


print("n: " + str(n) + "\n")
print("e: " + str(e) + "\n")

d = owiener.attack(e,n)

if d is None:
    print("Failed")
else:
    print("Hacked d={}".format(d))

c_msg="fJdSIoC9qz27pWVpkXTIdJPuR9Fidfkq1IJPRQdnTM2XmhrcZToycoEoqJy91BxikRXQtioFKbS7Eun7oVS0y788IXid2pIa9SyUxc5hcXYQYFYspEaVJXRclOqk7uXI8XdXzjN8ZJ+PRmBDPtnFFZNtk7uSLGA28yeP80g38yh9FhTJgQg0DmL+EKwS0qRoKfYewKn3z6SyL/yXDUc1M/4oXKPCHaBkf6eTMvAj590kVsI3mLAUVej47OBwQwWr+y2fMsE0u2F6bp2VP27EaLN68uj2CXm9J1WVFyLgqeQryh5jMyryLwuJNo/pz4tXzRqV4a8gM0JGdjvF84mf+w=="
c_msg_bytes = base64.b64decode(c_msg.encode('ascii'))
c_msg = int.from_bytes(c_msg_bytes, byteorder='big', signed=False)
c_msg = 0x7c97522280bdab3dbba565699174c87493ee47d16275f92ad4824f4507674ccd979a1adc653a32728128a89cbdd41c629115d0b62a0529b4bb12e9fba154b4cbbf3c21789dda921af52c94c5ce6171761060562ca4469525745c94eaa4eee5c8f17757ce337c649f8f4660433ed9c515936d93bb922c6036f3278ff34837f3287d1614c98108340e62fe10ac12d2a46829f61ec0a9f7cfa4b22ffc970d473533fe285ca3c21da0647fa79332f023e7dd2456c23798b01455e8f8ece0704305abfb2d9f32c134bb617a6e9d953f6ec468b37af2e8f60979bd2755951722e0a9e42bca1e63332af22f0b89368fe9cf8b57cd1a95e1af20334246763bc5f3899ffb
print("\nc_msg: " + str(c_msg))

msg=pow(c_msg,d,n)

print("\nmsg: " + str(hex(msg)))
