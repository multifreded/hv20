# Day 03 / HV20.03 Packed gifts



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: [@darkstar](https://twitter.com/___darkstar__)
* Tags:   #crypto
* Level:  easy

One of the elves has unfortunately added a password to the last presents
delivery and we cannot open it. The elf has taken a few days off after all the
stress of the last weeks and is not available. Can you open the package for us?

We found the following packages:

* [Package 1](Package1.zip)
* [Package 2](Package2.zip)



## Solution

Both files are [PKZIP]() files (further on called _ZIP files_). Lets take a look
what's inside:

[PKZIP]: https://en.wikipedia.org/wiki/PKZIP

``` shell
$ unzip -Z Package1.zip
Archive:  Package1.zip
Zip file size: 28649 bytes, number of entries: 100
-rw-r--r--  6.3 unx      172 bx defN 20-Nov-24 09:07 0000.bin
-rw-r--r--  6.3 unx      172 bx defN 20-Nov-24 09:07 0001.bin
-rw-r--r--  6.3 unx      172 bx defN 20-Nov-24 09:07 0002.bin
[…]
-rw-r--r--  6.3 unx      172 bx defN 20-Nov-24 09:07 0098.bin
-rw-r--r--  6.3 unx      172 bx defN 20-Nov-24 09:07 0099.bin
100 files, 17200 bytes uncompressed, 15827 bytes compressed:  8.0%
```

``` shell
$ unzip -Z Package2.zip
Archive:  Package2.zip
Zip file size: 30070 bytes, number of entries: 101
-rw-r--r--  6.3 unx      172 Bx defN 20-Nov-24 09:07 0000.bin
-rw-r--r--  6.3 unx      172 Bx defN 20-Nov-24 09:07 0001.bin
-rw-r--r--  6.3 unx      172 Bx defN 20-Nov-24 09:07 0002.bin
[…]
-rw-r--r--  6.3 unx      172 Bx defN 20-Nov-24 09:07 0098.bin
-rw-r--r--  6.3 unx      172 Bx defN 20-Nov-24 09:07 0099.bin
-rw-r--r--  6.3 unx      172 Bx defN 20-Nov-24 09:25 flag.bin
101 files, 17372 bytes uncompressed, 15908 bytes compressed:  8.4%
```

Both ZIP files seem to contain the same 100 files with the ending `.bin`. The 
second archive additionally contains a file called `flag.bin`. 

The _Package2.zip_ is encrypted (as indicated by the upper case `B` of the
fifth field) whereas _Package1.zip_ is unencrypted (as indicated by the lower
case `b` of the fifth field). The encryption of these ZIP files is per se is
quite strong so brute-forcing is out of the question.

Since _Package1.zip_ is unencrypted and seems to contain the same files as
_Package2.zip_, a known plain text attack would be possible. Also there is
software available for this called [bkcrack].

The cracking tool is named after the attack's inventors [Eli **B**iham][biham]
and Paul C. **K**och. See [_A Known Plaintext Attack on the PKZIP Stream 
Cipher_][bkcrack-paper] for the white paper about the topic.
[bkcrack]: https://github.com/kimci86/bkcrack
[biham]: https://en.wikipedia.org/wiki/Eli_Biham
[bkcrack-paper]: https://link.springer.com/chapter/10.1007/3-540-60590-8_12

During the attack a software tries to derive the encryption keys by comparing
the known plain text with its corresponding cipher text.


### How to use the damn tool

It took me a while to understand how _bkcrack_ is suppossed to be used since
the documentation was a bit ambiguous. It basically works like this:

* The first goal is to get the encryption keys. The second goal is to use the
  keys to extract files from the encrypted ZIP file.

* You need 2 ZIP files:

  1. The encrypted ZIP file.
  2. An unencrypted ZIP file that was made with the same compression mechanism.

  There must be at least 1 file in both ZIP files having the **same contents**.
  That file acts as the _known plain text_.

* You need to specifiy the following things to _bkcrack_

  * `-C <path to the encrypted ZIP file>` 
  * `-c <known plain text file name>`\
    This is the _name_ of a file in the encrypted ZIP file.
  * `-P <path to the unencrypted ZIP file>`
  * `-p <known plain text file name>`\
    This is the _name_ of a file in the unencrypted ZIP file.

  The names of the `-c` and `-p` files can differ but their contents have to be
  the same.


### Using the damn tool

In order to get the names of the file that acts as known plain text, I first
needed a way to verify that files with the same name actually have the same
content. Luckily I found an option of unzip(1) that shows [CRC-32] checksums of
the files in the ZIP files:
[CRC-32]: https://en.wikipedia.org/wiki/Cyclic_redundancy_check

``` shell
$ unzip -v Package1.zip 
Archive:  Package1.zip
 Length   Method    Size  Cmpr    Date    Time   CRC-32   Name
--------  ------  ------- ---- ---------- ----- --------  ----
     172  Defl:N      159   8% 11-24-2020 09:07 d1380cc4  0000.bin
     172  Defl:N      158   8% 11-24-2020 09:07 3cea7f5e  0001.bin
     172  Defl:N      158   8% 11-24-2020 09:07 b69fa5a2  0002.bin
[…]

$ unzip -v Package2.zip
Archive:  Package2.zip
 Length   Method    Size  Cmpr    Date    Time   CRC-32   Name
--------  ------  ------- ---- ---------- ----- --------  ----
     172  Defl:N      159   8% 11-24-2020 09:07 12df6163  0000.bin
     172  Defl:N      158   8% 11-24-2020 09:07 2ec39f7a  0001.bin
     172  Defl:N      159   8% 11-24-2020 09:07 842dfdfe  0002.bin
[…]
```

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
To much of my suprise did **none** of the files seem to have the same contents.
I wrote the following shellscript to compare every checksum from the first ZIP
file with every checksum of the second ZIP file:

``` bash
#!/bin/bash

for crc in $(unzip -v Package2.zip | grep -Eo ' [0-9a-f]{8} '); do
    if unzip -v Package1.zip | grep -q $crc; then
        echo "Package1.zip:"
        unzip -v Package1.zip | grep $crc
        echo "Package2.zip:"
        unzip -v Package2.zip | grep $crc
    fi
done
```

Running the script gave:

``` shell
$ ./cmp_chksums.sh
Package1.zip:
     172  Defl:N      159   8% 11-24-2020 09:07 fcd6b08a  0053.bin
Package2.zip:
     172  Defl:N      159   8% 11-24-2020 09:07 fcd6b08a  0053.bin
```

Aw yiss! Onwards to cracking the keys:

``` shell
$ bkcrack -P Package1.zip -p 0053.bin -C Package2.zip -c 0053.bin
bkcrack 1.0.0 - 2020-11-11
Generated 4194304 Z values.
[22:54:30] Z reduction using 151 bytes of known plaintext
100.0 % (151 / 151)
53880 values remaining.
[22:54:31] Attack on 53880 Z values at index 7
Keys: 2445b967 cfb14967 dceb769b 
68.8 % (37081 / 53880)
[22:55:23] Keys
2445b967 cfb14967 dceb769b 
```

Great success! How about extracting the juicy _flag.bin_ file ?

``` shell
$ bkcrack -C Package2.zip -c flag.bin -k 2445b967 cfb14967 dceb769b -d flag.comp
bkcrack 1.0.0 - 2020-11-11
Wrote deciphered text.
```

Since _Package2.zip_ is compressed, the extracted _flag.comp_ file is still
compressed and needs to be _inflated_. There is a python3 script on the bkcrack
github site that does the inflation: [inflate.py][inflate]
[inflate]: https://github.com/kimci86/bkcrack/blob/master/tools/inflate.py

``` shell
$ ./inflate.py < flag.comp > flag.bin
$ xxd flag.bin
00000000: 5346 5979 4d48 7461 6158 4244 636e 6c77  SFYyMHtaaXBDcnlw
00000010: 6444 4266 647a 4630 6146 3972 626a 4233  dDBfdzF0aF9rbjB3
00000020: 626c 3977 6247 4578 626e 526c 6548 5266  bl9wbGExbnRleHRf
00000030: 4d58 4e66 5a57 467a 6556 3930 4d46 396b  MXNfZWFzeV90MF9k
00000040: 5a57 4e79 6558 4230 6653 4167 4943 4167  ZWNyeXB0fSAgICAg
00000050: 4943 4167 4943 4167 4943 4167 4943 4167  ICAgICAgICAgICAg
00000060: 5346 5979 4d48 7461 6158 4244 636e 6c77  SFYyMHtaaXBDcnlw
00000070: 6444 4266 647a 4630 6146 3972 626a 4233  dDBfdzF0aF9rbjB3
00000080: 626c 3977 6247 4578 626e 526c 6548 5266  bl9wbGExbnRleHRf
00000090: 4d58 4e66 5a57 467a 6556 3930 4d46 396b  MXNfZWFzeV90MF9k
000000a0: 5a57 4e79 6558 4230 6651 6f3d            ZWNyeXB0fQo=
```

A look inside flag.bin revealed that the contents were [base64] encoded.
Decoding the contents yields the flag:
[base64]: https://en.wikipedia.org/wiki/Base64

``` shell
$ base64 -D flag.bin
HV20{ZipCrypt0_w1th_kn0wn_pla1ntext_1s_easy_t0_decrypt}                 HV20{ZipCrypt0_w1th_kn0wn_pla1ntext_1s_easy_t0_decrypt}
```

--------------------------------------------------------------------------------

Flag: `HV20{ZipCrypt0_w1th_kn0wn_pla1ntext_1s_easy_t0_decrypt}`

