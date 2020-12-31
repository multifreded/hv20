# Day 07 / HV20.07 Bad morals



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
by kuyaya

One of the elves recently took a programming 101 course. Trying to be helpful,
he implemented a program for Santa to generate all the flags for him for this
year's HACKvent 2020. The problem is, he can't remember how to use the program
any more and the link to the documentation just says `404 Not found`. I bet he
learned that in the Programming 101 class as well.

Can you help him get the flag back?

[BadMorals.exe](BadMorals.exe)


## Solution

The executable turned out to be a x86 .Net program:

``` shell
$ file BadMorals.exe 
BadMorals.exe: PE32 executable (console) Intel 80386 Mono/.Net assembly, for MS 
Windows
```

The good thing about .Net code is that it's bytecode and bytecode can easily be
decompiled. This was done with the [Jetbrains doPeek] software.

[Jetbrains doPeek]: https://www.jetbrains.com/decompiler/

Apart from a handful tricky spots reading the code was pretty straight forward.

Here are the pseudocode notes that lead to uncover the flag eventually:

```
First input

=> BumBumWithTheTumTum

Rule: i % 2 == 0 && i + 2 <= str.len {
          res += str[i+1]

=> BBuummBBuummWWiitthhTThheeTTuummTTuumm

---

Second input

=> BackAndForth

Rule: Reverse

=> htroFdnAkcaB

---

Third input

=> DinosAreLit

Rule: str[i] ^ num
      num = num + i - 4;

=> 2a 26 23 21 20 20 21 23 26 2a 2f
=> nOMNSaSFjC[

                    1                   2                   3               
0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7
B B u u m m B B 8 u m m W W X i t t h h T T h h e e T T u u m m T T u u m m 
                     8                                               14
SFYyMH + t + yMz + [0-9] + zcnMzXzN + u + ZzF + u + MzNyM + W + 5n + ? + 2
SFYyMHtyMz + [0-9] + zcnMzXzNuZzFuMzNyMW5n + ? + 2

Q1RGX3 + B + sNH + k + xbm + d + f
Q1RGX3BsNHkxbmdf
                    1
0 1 2 3 4 5 6 7 8 9 0
n O M N S a S F j C [
00ZD + N + f + M + zRzeX0=
00ZDNfMzRzeX0=



SFYyMHtyMz4zcnMzXzNuZzFuMzNyMW5nX200ZDNfMzRzeX0=
-> base64.decode():
HV20{r3>3rs3_3ng1n33r1ng_m4d3_34sy}
             CTF_pl4y1ng_

SFYyMHtyMz8zcnMzXzNuZzFuMzNyMW5nX200ZDNfMzRzeX0=
```
--------------------------------------------------------------------------------

Flag: `HV20{r3?3rs3_3ng1n33r1ng_m4d3_34sy}`

