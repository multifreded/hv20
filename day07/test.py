ohmy = "BBuummBBuummWWiitthhTThheeTTuummTTuumm"
res = ""
for i in range(0,len(ohmy)):
    if i % 2 == 0 and i + 2 <= len(ohmy):
        res += ohmy[i+1]

print(res)


ohmy = "htroFdnAkcaB"
res = ""
for i in range(0,len(ohmy)):
    res += ohmy[len(ohmy) - 1 - i]

print(res)

ohmy = "nOMNSaSFjC["
num = 42
res = ""
for i in range(0,len(ohmy)):
    res += chr(ord(ohmy[i]) ^ num)
    num = num + i - 4

print(res)

