[← Day 17](../day17/) / [↑ TOC](../README.md) / [→ Day 19](../day19/)


# Day 18 / HV20.18 Santa's lost home



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: darkstar ([@darkstar](https://twitter.com/___darkstar__))
* Tags:   `#forensic` `#crypto` `#linux`
* Level:  Hard

Santa has forgotten his password and can no longer access his data. While trying
to read the hard disk from another computer he also destroyed an important file.
To avoid further damage he made a backup of his home partition. Can you help him
recover the data.

When asked he said the only thing he remembers is that he used his name in the
password... I thought this was something only a _real human_ would do...

[Backup](Backup.img.bz2)


### Hints

* It's not rock-science, it's station-science!
* Use default options



## Solution

The backup image is copied to a Raspberry Pi (that's what I had available at
the time), decompressed and inspected …

```sh
$ bunzip2 Backup.img.bz2 

$ ls
Backup.img

$ file Backup.img 
Backup.img: Linux rev 1.0 ext2 filesystem data, UUID=5a9bec26-3f99-4101-bc44-153139202629 (extents) (64bit) (large files) (huge files)

$ sudo fdisk -lu Backup.img
Disk Backup.img: 94 MiB, 98566144 bytes, 192512 sectors
Units: sectors of 1 * 512 = 512 bytes
Sector size (logical/physical): 512 bytes / 512 bytes
I/O size (minimum/optimal): 512 bytes / 512 bytes

$ sudo losetup /dev/loop0 Backup.img 

$ sudo fsck -fv /dev/loop0
fsck from util-linux 2.29.2
e2fsck 1.43.4 (31-Jan-2017)
Durchgang 1: Inodes, Blöcke und Größen werden geprüft
Durchgang 2: Verzeichnisstruktur wird geprüft
Durchgang 3: Verzeichnisverknüpfungen werden geprüft
Durchgang 4: Referenzzähler werden überprüft
Durchgang 5: Zusammengefasste Gruppeninformation wird geprüft

          47 Inodes sind in Benutzung (0.20% von 24064)
           0 nicht zusammenhängende Dateien (0.0%)
           0 nicht zusammenhängende Verzeichnisse (0.0%)
             # von Inodes mit ind/dind/tind Blöcken: 0/0/0
             Histogramm der Tiefe von Erweiterungen: 34
         830 Blöcke werden benutzt (3.45% von 24064)
           0 defekte Blöcke
           1 große Datei

          17 reguläre Dateien
          15 Verzeichnisse
           0 zeichenorientierte Gerätedateien
           0 Blockgerätedateien
           0 Fifos
           0 Verknüpfungen
           6 symbolische Verknüpfungen (4 schnelle symbolische Verknüpfungen)
           0 Sockets
------------
          38 Dateien
```

Then the image is mounted and its contents inspected …

```sh
$ sudo mount /dev/loop0 /mnt

$ cd /mnt

$ sudo tree -a
.
├── .ecryptfs
│   └── santa
│       ├── .ecryptfs
│       │   ├── auto-mount
│       │   ├── auto-umount
│       │   ├── Private.mnt
│       │   └── Private.sig
│       └── .Private
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7d3jR0N.8eRZ6tCge1bB0sDk-- -> ECRYPTFS_FNEK_ENCRYPTED.FXZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dJ4crkSjoZDbKybFsTcbU3yO9MZ2HbI9q-r8GoG6m0gU-
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7d71FVjTGpVsJzCndwWUizwk--
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dAmhR-btY3XiBOwSO2PoBPk--
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dCUVmirG.GL1fQxxAD3586k--
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7ddA6PxrTroJKVisYGJ47EK---
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dDVAbJ.qWUGo9VsA6228ga--- -> ECRYPTFS_FNEK_ENCRYPTED.FXZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7da7uYMlQvW-7PRkhg.A1LcCmrqbiCpUc1VYSQCCaA6.k-
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dHHFh-OfKDySlXA1OHDc9kE--
│           │   ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dDx48i0T0jI5URCnvjmXJH---
│           │   │   ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7d0gl-eBzHzhweHy.hxwrepU--
│           │   │   └── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7d4-FSVeCqFM4EKvvgbE.Md---
│           │   ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dF5Wq-pTCFN4dRBWQwWf-hU--
│           │   │   └── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dcPebJwTGr-2huuEfFceP0E--
│           │   └── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dYlmFuEbQLRU7XhONkTKeP---
│           │       └── ECRYPTFS_FNEK_ENCRYPTED.FXZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dm99hH.vn-aClEY-KMvsthXhI-abirzOWcbkjl6t4JBA-
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dHPZG3mNdhgjB0XYdMv0rkk--
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7doIjA5NmFV6PqUW5O0D4Rfk--
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dtEnnKY5yelbZezXFJrTul---
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dx8yxbRZmYzmSUtn4Vpt5t---
│           ├── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dzkmECdlI6niYOUV5xGTJjU--
│           │   └── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7d1JDODsETfukf65VhSkI0n---
│           │       └── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dH.bKOaBjUbJM2U2TIiU-ik--
│           │           └── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dqLfSXNIF5kpOP.NxOzrZyk--
│           └── ECRYPTFS_FNEK_ENCRYPTED.FWZ07.HM9hn6u-TZiWKrjgW6DXtByC4T9a7dzl-gSPMHg2YAMT2BQA3o.---
├── lost+found
└── santa
    ├── Access-Your-Private-Data.desktop -> /usr/share/ecryptfs-utils/ecryptfs-mount-private.desktop
    ├── .ecryptfs -> /home/.ecryptfs/santa/.ecryptfs
    ├── .Private -> /home/.ecryptfs/santa/.Private
    └── README.txt -> /usr/share/ecryptfs-utils/ecryptfs-mount-private.txt

16 directories, 21 files
```

It seems Santa used a file system encryption software called [eCryptfs].
Obviously the necessary software has to be installed:

[eCryptfs]: https://en.wikipedia.org/wiki/ECryptfs

```sh
$ sudo apt-get install ecryptfs-utils
Paketlisten werden gelesen... Fertig
…
```


### Ideas about how everything fits together

The challenge description says, that Santa not only had a password that he
cannot remember but the ding dong also deleted an important file by accident.
The suspicion is, that the deleted is a so called _wrapped passphrase_, a vital
part of the eCryptfs encryption scheme. It contains the actual passphrase
needed to decrypt the ecryptfs data. The _wrapped passphrase_ file itself was
encrypted with Santa's password.

What needs to be done first is to recover the accidentally lost _wrapped
passphrase_-file and secondly to crack the password for the _wrapped passphrase_
file in order to gain the actual passphrase for decrypting the files.


### Recovering the lost wrapped passphrase file

Before beginning to search through the raw data of the backup image, some
identifying property of _wrapped passphrase_ files needs to be determined. Since
wasn't anything readily retreivable on the web, the next best thing is to
produce _dummy_ wrapped passphrase file and look at it. Maybe there is some
identifying header byte sequence …

```sh
$ ecryptfs-wrap-passphrase dummy
Passphrase to wrap: dummy
Wrapping passphrase: dummy

$ xxd dummy 
00000000: 3a02 2f7a e7fb a1d6 f567 6564 6338 3335  :./z.....gedc835
00000010: 3763 3535 3937 3034 3537 b075 a81d 6272  7c55970457.u..br
00000020: 122a 7b20 0404 53e4 e8e9                 .*{ ..S...
```

… the new hope is that the byte sequence `0x3a02` may be unique and identifying
enough …

```sh
$ xxd -p Backup.img | sed 's/\(..\)/\1 /g' | grep -C 10 '3a 02'
ba 8b 56 c8 61 ee 91 1c 83 02 92 fa 8a c3 f9 2d 0f 52 3f 0a 31 02 e5 98 03 8d 52 ad e3 24 
d4 b8 51 79 e6 b5 f8 71 3e f5 64 88 6b f1 e5 96 97 54 c0 5c f3 5d 4f 6f 8e bd 4c 55 d4 f0 
fe 1a 97 38 09 82 aa 7e 79 77 16 1c 53 e2 83 e8 37 b7 de 32 ba 1b 35 73 8f 05 2f ad c9 27 
b2 37 f0 12 3e df a0 9c d0 f3 19 94 9f cd c5 21 77 a8 98 2e 51 9d 16 76 3e 9a 25 aa ed 1a 
16 b4 80 9f 68 ba bf ee df d8 f5 25 0e 37 a0 67 c7 31 6a e2 a7 e2 e6 6a da 6c e2 d5 66 67 
05 12 5d fb 5b 67 aa 65 bc a2 2a 7a f0 10 77 56 ea 4a 66 b7 0a 19 f1 83 6d 47 27 29 ca d4 
b6 e4 37 09 4c 60 31 57 d6 df 7a 75 33 48 d8 02 65 98 1e b3 26 c2 fa d1 21 3c da 9e 98 3d 
9c d7 05 e1 18 06 1a 96 8e 0b 4c bd a5 da 96 33 b8 0a 5b cc af 84 69 50 c6 b7 b7 ce 02 99 
a7 a8 b3 80 54 8d 87 31 42 68 10 cb 56 3e cd 22 a7 60 de 76 e6 54 be 4d b9 73 c3 d4 7f ef 
d3 35 03 1d 7d 51 fb 26 bf 50 48 88 4e 6a 81 1f ea e8 cd 13 e8 d2 30 23 42 8b 4f f1 06 cc 
9b e2 cf 8f 02 ce 8c d6 22 3b ad f8 4b a8 f4 c6 98 2e 5d d3 c5 30 06 d1 4c 3a 02 1e 34 6d 
cd 99 11 fd 6c 5c f8 01 41 0f e5 ae ef c0 1b b6 65 9e 46 25 fd 80 30 a7 22 58 ac 28 64 09 
75 79 4e cd 81 98 d2 1e 41 d1 80 f3 de 10 cf f1 cb 07 aa ae 49 72 00 bd ce 02 9d 4e b0 e1 
6b 82 90 9e cd b5 31 53 ca 2c 1a bb bf d8 be d7 7e 06 6f dd de 13 a1 3f ba 46 35 77 f0 65 
d6 74 47 00 9c a2 a6 21 c3 f8 36 e8 cd c2 eb bc 0c 87 27 d1 f0 ab b8 86 99 0e 9f 95 a2 7e 
f6 eb 1e 4d f5 a2 a2 89 22 69 77 93 f8 5e ab 1f fd 7f 4b 8e 95 a2 14 5e 48 92 c1 37 ad 7a 
52 44 32 04 0a a3 aa d5 a1 c6 1b b2 dd 80 ca 65 fa a4 d2 ec ef 40 85 09 25 6b e3 4d 72 16 
a4 01 d1 f6 ea 6d 89 05 af 8b 8d 37 0a 16 ab 38 fe d0 d4 01 1a 8a 4f f4 32 54 96 9b 67 39 
67 bf fe 15 99 e6 0b 7a 80 20 3d 89 18 c7 12 cd 9d 05 1d 6d 20 b6 29 cc 89 f7 47 db 0a b2 
00 03 7f 1d 36 4c 3a ce 3e fc 31 f0 b8 f9 c3 3d 5a 16 4c 71 0f 33 a0 54 f8 9e a4 cb 74 6d 
27 8d 6b 40 0c 74 a9 8b 67 a7 79 a9 03 ad cb 07 33 df a2 45 4a 49 bf 04 14 d7 29 5f a4 74 
--
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 3a 02 a7 23 b1 2f 66 bc fe aa 30 35 31 31 31 39 62 30 62 61 63 65 30 61 62 36 db b8 
dd 00 47 8f a1 89 ae c3 cb e5 22 94 f4 ca d1 57 fe 2d 78 65 67 74 61 1f 32 1b 99 30 6f c7 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 
```

Indeed searching for the byte sequence in `Backup.img` yielded two matches. Standing so
alone the second one is probably the missing wrapped passphrase file.

```sh
$ echo "3a 02 a7 23 b1 2f 66 bc fe aa 30 35 31 31 31 39 62 30 62 61 63 65 30 61 62 36 db b8 dd 00 47 8f a1 89 ae c3 cb e5 22 94 f4 ca d1 57 fe 2d 78 65 67 74 61 1f 32 1b 99 30 6f c7"\
| sed 's/ //g' | xxd -p -r > recovered_wrapped-passphrase
```


### Cracking Santa's password.

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
The challenge description mentioned _real humans_ in a strange way. There is a
famous password list that supposedly only contains _real human passwords_. It's
called [crackstation-human-only.txt]() \(Thanks for the hint, jokker\).

[crackstation-human-only.txt]: https://crackstation.net/crackstation-wordlist-password-cracking-dictionary.htm

The list is downloaded and checked for how many passwords contain the string
`santa` in lower and upper case.

```sh
$ grep -i 'santa' crackstation-human-only.txt > santa_passwords.txt \
&& wc -l santa_passwords.txt
13852 santa_passwords.txt
```

This list is further reduced since ecryptfs only accepts passwords that are
shorter than 65 characters.

For the cracking procedure _hashcat_ is used. But before that, the _wrapped
passphrase_ file has to be converted with a [script] in order to be digestible
by _hashcat_ …

[script]: https://github.com/openwall/john/blob/bleeding-jumbo/run/ecryptfs2john.py

```sh
$ ./ecryptfs2john.py recovered_wrapped-passphrase > wrapped.hash

$ cat wrapped.hash
$ecryptfs$0$1$a723b12f66bcfeaa$051119b0bace0ab6

$ hashcat -m 12200 wrapped.hash santa_passwords_max64.txt 
hashcat (v6.1.1) starting...

OpenCL API (OpenCL 1.2 (Jun 23 2019 21:50:55)) - Platform #1 [Apple]
====================================================================
* Device #1: Intel(R) Core(TM) i5-8265U CPU @ 1.60GHz, skipped
* Device #2: Intel(R) Iris(TM) Plus Graphics 655, 1472/1536 MB (384 MB allocatable), 48MCU

Minimum password length supported by kernel: 0
Maximum password length supported by kernel: 256

Hashes: 1 digests; 1 unique digests, 1 unique salts
Bitmaps: 16 bits, 65536 entries, 0x0000ffff mask, 262144 bytes, 5/13 rotates
Rules: 1

Applicable optimizers applied:
* Zero-Byte
* Single-Hash
* Single-Salt
* Slow-Hash-SIMD-LOOP
* Uses-64-Bit

Watchdog: Hardware monitoring interface not found on your system.
Watchdog: Temperature abort trigger disabled.

Host memory required for this attack: 169 MB

Dictionary cache built:
* Filename..: santa_passwords_max64.txt
* Passwords.: 13802
* Bytes.....: 220648
* Keyspace..: 13802
* Runtime...: 0 secs

[s]tatus [p]ause [b]ypass [c]heckpoint [q]uit => s

Session..........: hashcat
Status...........: Running
Hash.Name........: eCryptfs
Hash.Target......: $ecryptfs$0$1$a723b12f66bcfeaa$051119b0bace0ab6
Time.Started.....: Fri Dec 18 23:31:15 2020 (31 secs)
Time.Estimated...: Fri Dec 18 23:32:45 2020 (59 secs)
Guess.Base.......: File (santa_passwords_max64.txt)
Guess.Queue......: 1/1 (100.00%)
Speed.#2.........:      155 H/s (4.11ms) @ Accel:1 Loops:128 Thr:8 Vec:1
Recovered........: 0/1 (0.00%) Digests
Progress.........: 4608/13802 (33.39%)
Rejected.........: 0/4608 (0.00%)
Restore.Point....: 4608/13802 (33.39%)
Restore.Sub.#2...: Salt:0 Amplifier:0-1 Iteration:35712-35840
Candidates.#2....: racingsantanderlogo -> SANTA-MARIA-DELLE-GRAZIE-THE-LAST-SUPPER

$ecryptfs$0$1$a723b12f66bcfeaa$051119b0bace0ab6:think-santa-lives-at-north-pole

$ printf "think-santa-lives-at-north-pole" | ecryptfs-unwrap-passphrase recovered_wrapped-passphrase -
eeafa1586db2365d5f263ef867f586e4
```

The password is `think-santa-lives-at-north-pole`.\
The passphrase is `eeafa1586db2365d5f263ef867f586e4`.



### Decrypting the files

Lastly decrypting the files unveils the flag file …

```sh
$ sudo ecryptfs-recover-private .ecrypfts/santa/.Private
INFO: Searching for encrypted private directories (this might take a while)...
INFO: Found [/home/.ecryptfs/santa/.Private].
Try to recover this directory? [Y/n]: y
INFO: Could not find your wrapped passphrase file.
INFO: To recover this directory, you MUST have your original MOUNT passphrase.
INFO: When you first setup your encrypted private directory, you were told to record
INFO: your MOUNT passphrase.
INFO: It should be 32 characters long, consisting of [0-9] and [a-f].

Enter your MOUNT passphrase: 
INFO: Success!  Private data mounted at [/tmp/ecryptfs.TLj7L23X].

$ cd /tmp/ecryptfs.TLj7L23X/

$ ls
.bash_history  .bashrc	.config/    flag.txt	.gtkrc-xfce  .local/	.profile
.bash_logout   .cache/	.ecryptfs@  .gtkrc-2.0	.joe_state   .Private@

$ cat flag.txt 
HV20{a_b4ckup_of_1mp0rt4nt_f1l35_15_3553nt14l}
```

--------------------------------------------------------------------------------

Flag: `HV20{a_b4ckup_of_1mp0rt4nt_f1l35_15_3553nt14l}`

[← Day 17](../day17/) / [↑ TOC](../README.md) / [→ Day 19](../day19/)
