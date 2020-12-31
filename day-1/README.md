# Day -1 / HV20.(-1) Twelve steps of christmas



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: Bread ([@nonsxd](https://twitter.com/nonsxd))
* Tags:   #fun
* Level:  easy

On the third day of christmas my true love sent to me...

three caesar salads,\
two to (the) six basic arguments,\
one quick response.

[Message](Message.txt)



## Solution

It's written right there \(\^-\^\)

> three casear salads

meaning do a [Caesar Cipher] shift by 3 on the message text. The leading
sentence in the message is readable after that.

[Caesar Cipher]: https://en.wikipedia.org/wiki/Caesar_cipher

> two to (the) six basic arguments,

i.e. 2^6 = 64, together with the word _basic_ meaning do a [base64] decoding.
You than have to notice that the resulting binary is a [PNG] image file.

[PNG]: https://en.wikipedia.org/wiki/Portable_Network_Graphics
[base64]: https://en.wikipedia.org/wiki/Base64
[QR code]: https://en.wikipedia.org/wiki/QR_code

> one quick response

meaning scan the [QR code] in the file. But its just a white square ?! Well it
not _absolutly_ white. You have to first stretch out the grey levels of the
image (with Gimp) to make the QR code visible:

![](decoded.png) -> ![](adjusted_levels.png)

The flag is obtained by scanning the QR code.

--------------------------------------------------------------------------------

Flag: `HV20{34t-sl33p-haxx-rep34t}`

