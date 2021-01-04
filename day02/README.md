[← Day 01](../day01/) / [↑ TOC](../README.md) / [→ Day 03](../day03/)


# Day 2 / HV20.02 Chinese Animals


## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: The Compiler ([@the_compiler](https://twitter.com/the_compiler)
                         <https://bruhin.software/>)
* Tags:   `#fun`
* Level:  Easy

I've received this note from a friend, who is a Chinese CTF player:

>   恭喜！收旗爲：ＨＶ２０｛獭慬氭敬敧慮琭扵瑴敲晬礭汯癥猭杲慳猭浵搭桯牳ｅ｝

Unfortunately, Google Translate wasn't of much help: ![](otter.png)

![](translate.png)

I suspect the data has somehow been messed up while transmitting it.

Sadly, I can't ask my friend about more details. The Great Chinese Firewall is
thwarting our attempts to reach each other, and there's no way I'm going to
install WeChat on my phone.



## Solution

The challenge's topic is text encoding gone wrong. Usually wrong text encoding
results in obviously mangled text output. Sometimes though wrongly encoded text
seems to look OK, even more so in the eyes of someone who doesn't know the
language of the displayed glyphs – like multifred and Chinese symbols `:-)`.

The text from the CTF player can be split up in …

>   恭喜！收旗爲：

… which means something like "Congratulations! Here is the flag:",

>   ＨＶ２０｛

… which is the well known beginning of a flag. But for some confusing reason
it is written in [full width glyphs] \(which makes no sense IMO),

[full width glyphs]: https://en.wikipedia.org/wiki/Halfwidth_and_fullwidth_forms

>   獭慬氭敬敧慮琭扵瑴敲晬礭汯癥猭杲慳猭浵搭桯牳

… which doesn't mean anything but instead is a part of the flag with wrong text
encoding. And finally …

>   ｅ｝

… which is the end of the flag, again in [full width glyphs].


### Trying out different encodings

The following shell script goes through all available text encodings and tries
to decode a given text string. Using it let's you discover a fitting encoding
scheme …

``` sh
#!/bin/bash 

if [ -z "$1" ]; then >&2 echo "Missing text string."; exit 1; fi

# Iterates through list of encodings of iconv(1)
for enc in $(iconv -l); do 
        echo "Encoding: $enc"

        echo -n "$1" \
        | iconv -t "$enc" 2>/dev/null || echo -n "ERROR"

        read -r                   # Waits for key press
done
```

Running the script with the supposedly wrongly encoded string …

``` sh
$ ./try_all_the_encodings.sh "獭慬氭敬敧慮琭扵瑴敲晬礭汯癥猭杲慳猭浵搭桯牳"
Encoding: ANSI_X3.4-1968
ERROR
Encoding: ANSI_X3.4-1986
ERROR
Encoding: ASCII
ERROR
Encoding: CP367
ERROR
Encoding: IBM367
ERROR
Encoding: ISO-IR-6
ERROR
Encoding: ISO646-US
ERROR
Encoding: ISO_646.IRV:1991
ERROR
Encoding: US
ERROR
Encoding: US-ASCII
ERROR
Encoding: CSASCII
ERROR
Encoding: UTF-8
獭慬氭敬敧慮琭扵瑴敲晬礭汯癥猭杲慳猭浵搭桯牳
Encoding: UTF8
獭慬氭敬敧慮琭扵瑴敲晬礭汯癥猭杲慳猭浵搭桯牳
Encoding: UTF-8-MAC
獭慬氭敬敧慮琭扵瑴敲晬礭汯癥猭杲慳猭浵搭桯牳
Encoding: UTF8-MAC
獭慬氭敬敧慮琭扵瑴敲晬礭汯癥猭杲慳猭浵搭桯牳
Encoding: ISO-10646-UCS-2
small-elegant-butterfly-loves-grass-mud-hors
Encoding: UCS-2
small-elegant-butterfly-loves-grass-mud-hors
Encoding: CSUNICODE
small-elegant-butterfly-loves-grass-mud-hors
Encoding: UCS-2BE
small-elegant-butterfly-loves-grass-mud-hors
Encoding: UNICODE-1-1
small-elegant-butterfly-loves-grass-mud-hors
Encoding: UNICODEBIG
small-elegant-butterfly-loves-grass-mud-hors
Encoding: CSUNICODE11
small-elegant-butterfly-loves-grass-mud-hors
Encoding: UCS-2LE
msla-llegena-tubttrelf-yolev-srgsa-sum-dohsr
Encoding: UNICODELITTLE
msla-llegena-tubttrelf-yolev-srgsa-sum-dohsr
Encoding: ISO-10646-UCS-4
small-elegant-butterfly-loves-grass-mud-hors
…
```

The string is _UCS-2_ (or _UTF-16BE_ or similar) encoded text that is wrongly
decoded as UTF-8. The given string has a pretty nifty property: It's a byte
sequence that gives sensible glyphs in _UCS-2_ and _UTF-8_ encoding at the same
time. That's why there are no non printable characters.

The flag can be pieced together manually now.

--------------------------------------------------------------------------------

Flag: `HV20{small-elegant-butterfly-loves-grass-mud-horse}`

[← Day 01](../day01/) / [↑ TOC](../README.md) / [→ Day 03](../day03/)
