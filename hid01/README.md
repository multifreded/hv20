# Hidden 01 / HV20.H1 It's a secret!



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
Who knows where this could be hidden... Only the best of the best shall find it!

* Level: easy



## Solution

This hidden challenge appeared on the 3rd day of Hackvent20. It seemed probable
that there was still something funky in that encrypted _Package2.zip_ from 
%%%%day03%%%.

While taking a closer look at the file list of _Package2.zip_ one file stood
out. It was the only one whose compression ratio was 12% compared to other's. 
Also the file was called _0042.bin_ it surely must contain _The Answer to the
Ultimate Question of Life, the Universe, and Everything_ ;-)

Its the same process as on the challenge of day 3.

``` shell
$ unzip -v Package2.zip | less
Archive:  Package2.zip
 Length   Method    Size  Cmpr    Date    Time   CRC-32   Name
--------  ------  ------- ---- ---------- ----- --------  ----
     172  Defl:N      159   8% 11-24-2020 09:07 12df6163  0000.bin
     172  Defl:N      158   8% 11-24-2020 09:07 2ec39f7a  0001.bin
[…]
     172  Defl:N      158   8% 11-24-2020 09:07 f66aa2d4  0040.bin
     172  Defl:N      158   8% 11-24-2020 09:07 13caa955  0041.bin
     172  Defl:N      152  12% 11-24-2020 09:07 073b6ebc  0042.bin
     172  Defl:N      159   8% 11-24-2020 09:07 c7431488  0043.bin
     172  Defl:N      159   8% 11-24-2020 09:07 af1a231d  0044.bin
[…]
$ bkcrack -C Package2.zip -c 0042.bin -k 2445b967 cfb14967 dceb769b -d 0042.comp
bkcrack 1.0.0 - 2020-11-11
Wrote deciphered text.
$ ./inflate.py < 0042.comp > 0042.bin
$ base64 -D 0042.bin 
ُ?F?U?>>>>   HV20{it_is_always_worth_checking_everywhere_and_congratulations,_you_have_found_a_hidden_flag}   <<<<???i?aO?^7
```

Noice! (\*_\*)

--------------------------------------------------------------------------------

Flag: `HV20{it_is_always_worth_checking_everywhere_and_congratulations,_you_have_found_a_hidden_flag}`

