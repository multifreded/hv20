# Day 12 / HV20.12 Wiener waltz



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: SmartSmurf
* Tags:   #crypto
* Level:  medium


### Introduction

During their yearly season opening party our super-smart elves developed an
improved usage of the well known RSA crypto algorithm. Under the "Green IT"
initiative they decided to save computing horsepower (or rather reindeer power?)
on their side. To achieve this they chose a pretty large private exponent,
around 1/4 of the length of the modulus - impossible to guess. The reduction of
75% should save a lot of computing effort while still being safe. Shouldn't it?


### Mission

Your SIGINT team captured some communication containing key exchange and
encrypted data. Can you recover the original message?

[Download](Download.pcap)


### Hints

Don't waste time with the attempt to brute-force the private key



## Solution

The problem with this crypto setup is that RSA becomes vulnerable to the
[Wiener attack] when such extreme values are chosen.

[Wiener attack]: https://en.wikipedia.org/wiki/Wiener's_attack#Small_private_key

To launch a Wiener attack all that is needed is are the public key values
`e` and `n`.

In the PCAP file the packet 1952 containes such a public key …

```
Paket 1952:

n: "dbn25TSjDhUge4L68AYooIqwo0HC2mIYxK/ICnc+8/0fZi1CHo/QwiPCcHM94jYdfj3PIQFTri9j/za3oO+3gVK39bj2O9OekGPG2M1GtN0Sp+ltellLl1oV+TBpgGyDt8vcCAR1B6shOJbjPAFqL8iTaW1C4KyGDVQhQrfkXtAdYv3ZaHcV8tC4ztgA4euP9o1q+kZux0fTv31kJSE7K1iJDpGfy1HiJ5gOX5T9fEyzSR0kA3sk3a35qTuUU1OWkH5MqysLVKZXiGcStNErlaggvJb6oKkx1dr9nYbqFxaQHev0EFX4EVfPqQzEzesa9ZAZTtxbwgcV9ZmTp25MZg=="

e: "S/0OzzzDRdsps+I85tNi4d1i3d0Eu8pimcP5SBaqTeBzcADturDYHk1QuoqdTtwX9XY1Wii6AnySpEQ9eUEETYQkTRpq9rBggIkmuFnLygujFT+SI3Z+HLDfMWlBxaPW3Exo5Yqqrzdx4Zze1dqFNC5jJRVEJByd7c6+wqiTnS4dR77mnFaPHt/9IuMhigVisptxPLJ+g9QX4ZJX8ucU6GPSVzzTmwlDIjaenh7L0bC1Uq/euTDUJjzNWnMpHLHnSz2vgxLg4Ztwi91dOpO7KjvdZQ7++nlHRE6zlMHTsnPFSwLwG1ZxnGVdFnuMjEbPA3dcTe54LxOSb2cvZKDZqA=="

                   "format": ["mpz_export",-1,4,1,0]
                                            ^ ^ ^ ^
                                            | | | |
 Order: -1 = least significatn word first --' | | |
                                              | | |
             Size: Number of bytes per word --' | |
                                                | |
   Endianess: 1 = most significant byte first --' |
                                                  |
 Nails: Number of most significant bits to skip --'

sessionId: "RmERqOnbsA/oua67sID4Eg=="
```

What's a bit of a problem is on the one hand the special `mpz_export` notation 
that first has to be sorted out and on the other the fact that the message to be 
decrypted is spread over 4 network packets and first needs to be put together
correctly. 

Individual message packets:

```
Packet 1956

sessionId: "RmERqOnbsA/oua67sID4Eg=="  
blockId:   0,  
data:      "fJdSIoC9qz27pWVpkXTIdJPuR9Fidfkq1IJPRQdnTM2XmhrcZToycoEoqJy91BxikRXQtioFKbS7Eun7oVS0yw=="                     
format:    "plain"

Packet 1960

sessionId: "RmERqOnbsA/oua67sID4Eg==",
blockId:   2, 
data:      "fRYUyYEINA5i/hCsEtKkaCn2HsCp98+ksi/8lw1HNTP+KFyjwh2gZH+nkzLwI+fdJFbCN5iwFFXo+OzgcEMFqw==",                   
format:    "plain" 
   
Packet 1964

sessionId: "RmERqOnbsA/oua67sID4Eg==", 
blockId:   3, 
data:      "+y2fMsE0u2F6bp2VP27EaLN68uj2CXm9J1WVFyLgqeQryh5jMyryLwuJNo/pz4tXzRqV4a8gM0JGdjvF84mf+w==", 
format:    "plain"

Packet 1968

sessionId: "RmERqOnbsA/oua67sID4Eg==", 
blockId:   1, 
data:      "vzwheJ3akhr1LJTFzmFxdhBgViykRpUldFyU6qTu5cjxd1fOM3xkn49GYEM+2cUVk22Tu5IsYDbzJ4/zSDfzKA==", 
format:    "plain"
```

Combined single encrypted message:

```
block 0: 7c 97 52 22 80 bd ab 3d bb a5 65 69 91 74 c8 74 93 ee 47 d1 62 75 f9 2a d4 82 4f 45 07 67 4c cd 97 9a 1a dc 65 3a 32 72 81 28 a8 9c bd d4 1c 62 91 15 d0 b6 2a 05 29 b4 bb 12 e9 fb a1 54 b4 cb

block 1: bf 3c 21 78 9d da 92 1a f5 2c 94 c5 ce 61 71 76 10 60 56 2c a4 46 95 25 74 5c 94 ea a4 ee e5 c8 f1 77 57 ce 33 7c 64 9f 8f 46 60 43 3e d9 c5 15 93 6d 93 bb 92 2c 60 36 f3 27 8f f3 48 37 f3 28

block 2: 7d 16 14 c9 81 08 34 0e 62 fe 10 ac 12 d2 a4 68 29 f6 1e c0 a9 f7 cf a4 b2 2f fc 97 0d 47 35 33 fe 28 5c a3 c2 1d a0 64 7f a7 93 32 f0 23 e7 dd 24 56 c2 37 98 b0 14 55 e8 f8 ec e0 70 43 05 ab

block 3: fb 2d 9f 32 c1 34 bb 61 7a 6e 9d 95 3f 6e c4 68 b3 7a f2 e8 f6 09 79 bd 27 55 95 17 22 e0 a9 e4 2b ca 1e 63 33 2a f2 2f 0b 89 36 8f e9 cf 8b 57 cd 1a 95 e1 af 20 33 42 46 76 3b c5 f3 89 9f fb

Combined: 7c 97 52 22 80 bd ab 3d bb a5 65 69 91 74 c8 74 93 ee 47 d1 62 75 f9 2a d4 82 4f 45 07 67 4c cd 97 9a 1a dc 65 3a 32 72 81 28 a8 9c bd d4 1c 62 91 15 d0 b6 2a 05 29 b4 bb 12 e9 fb a1 54 b4 cb bf 3c 21 78 9d da 92 1a f5 2c 94 c5 ce 61 71 76 10 60 56 2c a4 46 95 25 74 5c 94 ea a4 ee e5 c8 f1 77 57 ce 33 7c 64 9f 8f 46 60 43 3e d9 c5 15 93 6d 93 bb 92 2c 60 36 f3 27 8f f3 48 37 f3 28 7d 16 14 c9 81 08 34 0e 62 fe 10 ac 12 d2 a4 68 29 f6 1e c0 a9 f7 cf a4 b2 2f fc 97 0d 47 35 33 fe 28 5c a3 c2 1d a0 64 7f a7 93 32 f0 23 e7 dd 24 56 c2 37 98 b0 14 55 e8 f8 ec e0 70 43 05 ab fb 2d 9f 32 c1 34 bb 61 7a 6e 9d 95 3f 6e c4 68 b3 7a f2 e8 f6 09 79 bd 27 55 95 17 22 e0 a9 e4 2b ca 1e 63 33 2a f2 2f 0b 89 36 8f e9 cf 8b 57 cd 1a 95 e1 af 20 33 42 46 76 3b c5 f3 89 9f fb
```

After all theses intricacies have been sorted out, the actual Wiener attack can
be executed. This is done with the following python script that already contains
all the sampled key and cipher text data. The message is decrypted in a
"mathematical" way. So the result has to be handled further more.

```python
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
```

Running the scripts yields:

```sh
$ python3 wiener.py 
n: 21136187113648735910956792902340987261238482724808044660872655926597365083148384784275999147719115005171023510870084682239018605609844594894880405609510814634404536868649155403129057903532257019060842686994634155205978467383309519881921823354273590936861045431841523283059891729069450531823193829758198452195159839001802409808310303539270828581792136817589972743921904535921749280330153901291531642543946250472645757855636930605097838505480384294629089321241798555566459046743741824235125746402090921912493396059817338067723079903962753795145687173236901003277653830701564333638891277876961702941978996729372105897701

e: 12703148700486856571456640284543930158485441147798980218669328932721873837903118006895885638306703700146300157588744922573525972231890883171794381140159146432366116691422353585619938803060563166160513071142031888780581428871210353376077782114636012547145421154246397069298658668372048637974096728556378192041823865600245728866360820303463508288677034505462614941425772365440025016354622878586568634346248386264921756141627262617888108166058845769396410463089005177762158324354462305559557728141729110983431022424786938837309186823930758907423061347118761390982013522713098779662020937499191572512966979990705904881359

Hacked d=6466004211023169931626852412529775638154232788523485346270752857587637907099874953950214032608531274791907536993470882928101441905551719029085370950197807

c_msg: 15728168902580001908597516462333326018530211196966332004405204181339039750500231671925994577113088042149317557183451400765813081420696808311927057791246464561194797144397265898951168688777637228526598195547112091614853627450147693884030988777555447488548272997133571420912416166701055958063189383646698527129142918175504346831025993966032574469739425111130122253629829143723900125449342127181240374096535321144237731152040526918071868603539495524381155246254890454199469350492226229443133055753874748977614593062562820322902874503410694904482016403214529911487245403091812683802132470939500989349886833516053615190011

msg: 0x10000000000000000000000000000000d596f75206d61646520697421204865726520697320796f757220666c61673a20485632307b35686f72375f507269763378705f61316e375f6e305f356d6172377d0d0d476f6f64206c75636b20666f72204861636b76656e742c206d6572727920582d6d617320616e6420616c6c20746865206265737420666f7220323032312c2067726565747a20536d617274536d7572660000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
```

Converting the message value into the actual message is most easily done with
[Cyberchef]\:

[Cyberchef]: https://gchq.github.io/CyberChef/#recipe=From_Hex('None')&input=MTAgMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwZDU5NmY3NTIwNmQ2MTY0NjUyMDY5NzQyMTIwNDg2NTcyNjUyMDY5NzMyMDc5NmY3NTcyMjA2NjZjNjE2NzNhMjA0ODU2MzIzMDdiMzU2ODZmNzIzNzVmNTA3MjY5NzYzMzc4NzA1ZjYxMzE2ZTM3NWY2ZTMwNWYzNTZkNjE3MjM3N2QwZDBkNDc2ZjZmNjQyMDZjNzU2MzZiMjA2NjZmNzIyMDQ4NjE2MzZiNzY2NTZlNzQyYzIwNmQ2NTcyNzI3OTIwNTgyZDZkNjE3MzIwNjE2ZTY0MjA2MTZjNmMyMDc0Njg2NTIwNjI2NTczNzQyMDY2NmY3MjIwMzIzMDMyMzEyYzIwNjc3MjY1NjU3NDdhMjA1MzZkNjE3Mjc0NTM2ZDc1NzI2NjAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDAwMDA

```
................
You made it! Here is your flag: HV20{5hor7_Priv3xp_a1n7_n0_5mar7}

Good luck for Hackvent, merry X-mas and all the best for 2021, greetz SmartSmurf............................................................................................

```

--------------------------------------------------------------------------------

Flag: `HV20{5hor7_Priv3xp_a1n7_n0_5mar7}`

