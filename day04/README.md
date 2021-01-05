[← Day 03](../day03/) / [↑ TOC](../README.md) / [→ Day 05](../day05/)


# Day 04 / HV20.04 Br❤️celet



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: brp64 (with help of his daughter)
* Tags:   `#fun`
* Level:  Easy

Santa was given a nice bracelet by one of his elves. Little does he know that
the secret admirer has hidden a message in the pattern of the bracelet...

![](bracelet.jpg)

#### Hints

_[These hints were added hours later as it became apparent that the challenge
was too difficult for the Easy category.]_

1. No internet is required - only the bracelet
2. The message is encoded in binary
3. Violet color is the delimiter
4. Colors have a fixed order
5. Missing colors matter



## Solution

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
This challenge is hairier than it appears. The first step is to write down the
sequence of the bracelet's colored beads …

* `b` means `blue`
* `g` means `green`
* `p` means `purple`
* `r` means `red`
* `y` means `yellow`

```sh
$ printf "gprypgbprgpgbprgbypgbypgbpbypbypgbyprypbyppgbypgypgypbypbypgpgbprgbpbypgbypbypgp" > beads.txt
```

<!--gprypgbprgpgbprgbypgbypgbpbypbypgbyprypbyppgbypgypgypbypbypgpgbprgbpbypgbypbypgp-->
![](color_beads_1.png)


From this point on there are multiple _wrong_ rabbit holes luring …

#### Wrong rabbit holes

* Assuming the challenge is about a [base5]-system:\
  With 5 colors available, the beads could be grouped in bigrams (or pairs).
  For each bigram there would be `5 * 5 = 25` possibilities and that would make
  for a nice alphabet.

  [base5]: https://en.wikipedia.org/wiki/Quinary

  For example something like this …

  |       |  b  |  g  |  p  |  r  |  y  |
  |-------|-----|-----|-----|-----|-----|
  | **b** |  A  |  B  |  C  |  D  |  E  |
  | **g** |  F  |  G  |  H  | I/J |  K  |
  | **p** |  L  |  M  |  N  |  O  |  P  |
  | **r** |  Q  |  R  |  S  |  T  |  U  |
  | **y** |  V  |  W  |  X  |  Y  |  Z  |

  But no matter how the alphabet is arrange, only garbage comes out.

* There is a Wikipedia article about an encryption system using five
  characters. It's called [ADFGX] and was used by WWI soldiers.

  [ADFGX]: https://de.wikipedia.org/wiki/ADFGX

* Multiple meandering web searches where undertook by multifred `:-/`.


#### Getting out by going deeper

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
Things start to get better once `p` is assumed a delimiter (as suggested by
jokker, thx) and then stubbornly holding on to that strategy …

```sh
$ cat beads.txt | sed 's/p/_/g'
```

<!--g_ry_gb_rg_gb_rgby_gby_gb_by_by_gby_ry_by__gby_gy_gy_by_by_g_gb_rgb_by_gby_by_g_-->
![](color_beads_2.png)

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
Staring at this pattern for a while will help noticing that each delimited group
has the same internal ordering …

* `r` precedes `g`
* `g` precedes `b`
* `b` precedes `y`

Eventually the idea forms that each color `r`, `g`, `b`, `y` represents a
binary digit. Each digit is either present (meaning `1`) or missing (meaning
`0`). In other words each color stands for a power of 2 …

* `y` = `2^0` = `1`
* `b` = `2^1` = `2`
* `g` = `2^2` = `4`
* `r` = `2^3` = `8`

```sh
$ cat beads.txt | sed 's/p/_/g' \
  | sed 's/r/8/g' | sed 's/g/4/g' | sed 's/b/2/g' | sed 's/y/1/g'
```

<!--4_81_42_84_42_8421_421_42_21_21_421_81_21__421_41_41_21_21_4_42_842_21_421_21_4_-->
![](color_beads_3.png)

Each group of numbers is then added up (by hand) …

<!--4_9._6._12_6._15.._7.._6._3._3._7.._9._3.0_7.._5._5._3._3._4_6._14._3._7.._3._4_-->
![](color_beads_4.png)

… converted to hexadecimal digits …

<!--4_9._6._c._6._f..._7.._6._3._3._7.._9._3.0_7.._5._5._3._3._4_6._e.._3._7.._3._4_-->
![](color_beads_5.png)

… and the resulting bytes are being ASCII encoded …

<!--I_.._l._.._o_....._v.._.._3._.._y.._.._0.._u.._.._S._.._4._._n._..._7._.._4.._._-->
![](color_beads_6.png)

And there it is, the meat of the flag.

--------------------------------------------------------------------------------

Flag: `HV20{Ilov3y0uS4n74}`

[← Day 03](../day03/) / [↑ TOC](../README.md) / [→ Day 05](../day05/)
