# Day 10 / HV20.10 Be patient with the adjacent


## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: Bread ([@nonsxd](https://twitter.com/nonsxd))
* Tags:   #programming
* Level:  medium

Ever wondered how Santa delivers presents, and knows which groups of friends
should be provided with the best gifts? It should be as great or as large as
possible! Well, here is one way.

Hmm, I cannot seem to read the file either, maybe the internet knows?

[Download](download.col.b)


### Hints

* Hope this cliques for you
* `bin2asc` will help you with this, but ...
* segfaults can be fixed - maybe read the source
* If you are using Windows for this challenge, make sure to add a `b` to to the 
  `fopen` calls on lines 37 and 58
* There is more than one thing you can do with this type of file! Try other 
  options...
* Groups, not group



## Solution

The basic idea was the cliques in a graph are groups of nodes within which
every node is connected to every other node. The aim is to find the biggest 
cliques.

To be able to do that first the file format had to be converted from `col.b` 
to `col`. `col.b` is the more compact binary variant of `col` and is intended
for archival purposes.

After that the [NetworkX] software had to be used to identify the biggest
cliques.

[NetworkX]: https://en.wikipedia.org/wiki/NetworkX

The indiviual member count of the longest cliques could then be interpreted as
byte values which gave the flag.

```sh
$ cat cliques_max.txt | sed "s/'[0-9]*'/X/g" | sed 's/[^X]//g' | while read -r line; do echo "$(echo "$line" | wc -c | xargs) - 1 " | bc; done | xxd -p | sed 's/\(..\)/\1/g' | sed 's/0a/20/g' | xxd -p -r
72 86 50 48 123 77 97 120 49 109 97 108 95 67 108 49 113 117 51 95 69 110 117 109 51 114 64 116 49 48 110 95 70 117 110 33 125
```

The values are decimal representations of ASCII characters.

--------------------------------------------------------------------------------

Flag: `HV20{Max1mal_Cl1qu3_Enum3r@t10n_Fun!}`

