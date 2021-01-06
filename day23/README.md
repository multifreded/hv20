[← Day 22](../day22/) / [↑ TOC](../README.md) / [→ Day 24](../day24/)


# Day 23 / HV20.23 Those who make backups are cowards!



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: hardlock
* Tags:   #iOS #crypto
* Level:  hard

Santa tried to get an important file back from his old mobile phone backup.
Thankfully he left a post-it note on his phone with the PIN. Sadly Rudolph
thought the Apple was real and started eating it (there we go again...). Now
only the first of eight digits, a 2, is still visible...

But maybe you can do something to help him get his important stuff back?

[Download](Download.rar)


### Hints

If you get stuck, call Shamir



## Solution


### Part 1: Cranking into the encrypted iOS backup

Inside the RAR archive were a bunch of files that could easily be identified as
an iOS device backup. After searching the web there were two very helpful webpages:

1. [Breaking into encrypted iPhone Backpus](https://medium.com/taptuit/breaking-into-encrypted-iphone-backups-4dacc39403f0)
2. [Cracking iTunes Backup Passwords with hashcat](https://irq5.io/2017/03/07/cracking-itunes-backup-passwords-with-hashcat/)

First a the `manifest.plist` file was identified as it contains the keybag that
can be used to decrypt the files in the backup. Then the [script]()
_itunes\_backup2hashcat.pl_ was used to convert the `manifest.plist` into hashes
that can be fed into _hashcat_:

[script]: https://github.com/philsmd/itunes_backup2hashcat

```sh
$ find Backup -iname "Manifest.plist"
Backup/Manifest.plist

$ cd itunes_backup2hashcat/

$ ./itunes_backup2hashcat.pl ../Backup/Manifest.plist > hash.txt

$ cat hash.txt 
$itunes_backup$*9*892dba473d7ad9486741346d009b0deeccd32eea6937ce67070a0500b723c871a454a81e569f95d9*10000*0834c7493b056222d7a7e382a69c0c6a06649d9a**
```

Everything was given to hashcat. `-a 3 2?d?d?d?d?d?d?d` means to use a PIN
pattern for cracking: a `2` followed by 7 arbitrary digits. `-m 14700` is the
mode for iTunes Backups before version 10. It took about an hour or so to find
the PIN.

```sh
$ hashcat -a 3 2?d?d?d?d?d?d?d -m 14700 -o PIN.txt hash.txt
$ cat PIN.txt 
$itunes_backup$*9*892dba473d7ad9486741346d009b0deeccd32eea6937ce67070a0500b723c871a454a81e569f95d9*10000*0834c7493b056222d7a7e382a69c0c6a06649d9a**:20201225
```

The PIN is: `20201225`


### Part 2: the mysterious numbers of the mysterious Shamir

The mac application _iMazing_ was used to look into the Backup. After having it
pointed to the backup (via its settings), it asked for and accepted Santa's PIN.

Apart from a hilarious cat video and a RickRoll-QR-code nothing much could be
found. There were two entries in the _Contacts_ that seemed strange:

![](m_and_n.png)

Each entry had nothing but a long number in the _Notes_ section:

M: `6344440980251505214334711510534398387022222632429506422215055328147354699502`\
N: `77534090655128210476812812639070684519317429042401383232913500313570136429769`

I don't no really why but I almost instantly thought of [RSA Cryptosystem]()
numbers. `M` for _Message_ and `N` as the modulus number created from
multiplying `p` and `q`.

[RSA Cryptosystem]: https://en.wikipedia.org/wiki/RSA_(cryptosystem)

Under normal circumstances these numbers cannot be factorized because, well the
whole cryptosystem is based on how hard it is to do this factorization. But these 
are not normal circumstances this is hackvent. And of course there is a database
of factors available on the intertubes that contains numbers often used for
examples.

Searching for N on the database was an instant [hit] and gave `p` and `q`:

P: `250036537280588548265467573745565999443`
Q: `310091043086715822123974886007224132083`

[hit]: http://factordb.com/index.php?query=77534090655128210476812812639070684519317429042401383232913500313570136429769

Thanks to a hint from _jokker_, I learned that for `E` one [usually uses]() 
`65537`.

[usually uses]: https://en.wikipedia.org/wiki/RSA_(cryptosystem)#Faulty_key_generation

E: `65537`

And with that everything was together to try a decryption of the message `M`.
The [RsaCtfTool]() was used to do this task:

[RsaCtfTool]: https://github.com/Ganapati/RsaCtfTool

```sh
# ./RsaCtfTool.py -p 250036537280588548265467573745565999443 -q 310091043086715822123974886007224132083 -e 65537 --private --uncipher 6344440980251505214334711510534398387022222632429506422215055328147354699502

Results for /tmp/tmpgufl4_ul:

Private key :
-----BEGIN RSA PRIVATE KEY-----
MIGrAgEAAiEAq2q9e3Wm0yNQrHKo5ereNF44+P+ald8v2i7eABPuFMkCAwEAAQIh
AKoxX5Jt3MXzYUzmxtUInbbElmM0L6K2hHJNHOILDIw1AhEAvBtJEjMrLQkRLms0
w8ahUwIRAOlJXM80fOQw6KafwCrj4fMCECkwGEnh5lxQFfECDGWpwn0CEQDWXRhQ
Oj3s/Vg7DB5sCvyrAhBs5D2xC7TgJxYHf+zEawX0
-----END RSA PRIVATE KEY-----

Unciphered data :
HEX : 0x0000000000485632307b73307272795f6e305f67616d335f746f5f706c61797d
INT (big endian) : 29757593747455483525592829184976151422656862335100602522242480509
INT (little endian) : 56753566960650598288217394598913266125073984765818621753275514254169309446144
STR : b'\x00\x00\x00\x00\x00HV20{s0rry_n0_gam3_to_play}'
```

Aw yiss! Sweet flag.

--------------------------------------------------------------------------------

Flag: `HV20{s0rry_n0_gam3_to_play}`

[← Day 22](../day22/) / [↑ TOC](../README.md) / [→ Day 24](../day24/)
