# Day 11 / HV20.11 Chris'mas carol



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: Chris
* Tags:   #crypto #forensic
* Level:  medium

Since yesterday's challenge seems to have been a bit on the hard side, we're
adding a small musical innuendo to relax.

My friend Chris from Florida sent me this score. Enjoy! Is this what you call
postmodern?

![](noten.png)


### Hints

* He also sent [this image](hongkong.png), but that doesn't look like Miami's
  skyline to me.
* The secret code is useful for a file - not a website



## Solution


### Notes

The notes from the picture can be translated to hex code:

```
treble clef:       e3 b4 f4 e3 d3 e2 d3 a5 b5 d5 a2 e5 a5 e3 a3                    
from hex:          >  K  O  >  =  .  =  Z  [  ]  *  ^  Z  >  :

bass clef:         b3 e3 d5 d3 a3 d1 a1 c4 e3 e4 a1 d4 a1 d3 a1
from hex:          ;  >  ]  =  :  .  .  L  >  N  .  M  .  =  .

XOR (From Hex):    P  W  !  0  p  3  r  a  V  1  s  1  t  0  r
```

See [Scientific pitch notation](https://en.wikipedia.org/wiki/Scientific_pitch_notation)


### The Hongkong picture

The picture of Hongkong is an example from a steganography online server called
[Mobilefish.com](https://www.mobilefish.com/services/steganography/steganography.php)
and is probably just meant as a hint to find this particular web service.

The picture with the notes can be uploaded to the service and decrypted
**without** a password. The result is a file that can be downloaded called:
`flag.zip`. The file is an encrypted ZIP archive.

```sh
$ $ file flag.zip 
flag.zip: Zip archive data, at least v5.1 to extract
fresal@slimslom  _today  $ zipinfo -v flag.zip 
Archive:  flag.zip
There is no zipfile comment.

End-of-central-directory record:
-------------------------------

  Zip archive file size:                       221 (00000000000000DDh)
  Actual end-cent-dir record offset:           199 (00000000000000C7h)
  Expected end-cent-dir record offset:         199 (00000000000000C7h)
  (based on the length of the central directory and its expected offset)

  This zipfile constitutes the sole disk of a single-part archive; its
  central directory contains 1 entry.
  The central directory is 101 (0000000000000065h) bytes long,
  and its (expected) offset in bytes from the beginning of the zipfile
  is 98 (0000000000000062h).


Central directory entry #1:
---------------------------

  flag.txt

  offset of local header from start of archive:   0
                                                  (0000000000000000h) bytes
  file system or operating system of origin:      MS-DOS, OS/2 or NT FAT
  version of encoding software:                   6.3
  minimum file system compatibility required:     MS-DOS, OS/2 or NT FAT
  minimum software version required to extract:   5.1
  compression method:                             unknown (99)
  file security status:                           encrypted
  extended local header:                          no
  file last modified on (DOS date/time):          2020 Dec 10 17:09:04
  32-bit CRC value (hex):                         00000000
  compressed size:                                49 bytes
  uncompressed size:                              21 bytes
  length of filename:                             8 characters
  length of extra field:                          47 bytes
  length of file comment:                         0 characters
  disk number on which file begins:               disk 1
  apparent file type:                             binary
  non-MSDOS external file attributes:             000000 hex
  MS-DOS file attributes (20 hex):                arc 

  The central-directory extra field contains:
  - A subfield with ID 0x000a (PKWARE Win32) and 32 data bytes.  The first
    20 are:   00 00 00 00 01 00 18 00 8c 01 b9 c6 0e cf d6 01 df 2e dc c6.
  - A subfield with ID 0x9901 (unknown) and 7 data bytes:
    02 00 41 45 03 00 00.

  There is no file comment.
```

After some trial and error I noticed that the 7-Zip tool on Windows is able
to open the file. It asks for a password and `PW!0p3raV1s1t0r` is the correct
one. Inside the archive is the flag.

--------------------------------------------------------------------------------

Flag: `HV20{r3ad-th3-mus1c!}`

