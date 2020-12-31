#Hid 03 / HV20.H3 Hidden in Plain Sight


## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
Who knows where this could be hidden... Only the best of the best shall find it!

* Level: medium



## Solution

On day 23 in Santa's iOS backup there is a remenant probably from a former
challenge that was turned into a hidden challenge mid CTF.

In the SQLite address book database where `N` and `M` where stored, there is
some fragment as a base64 encoded HTTP-URL:

```sh
$ cd Decrypted_Backup/HomeDomain/Library/AddressBook

$ strings AddressBook.sqlitedb | less
[…]
ABGroup
ABPe
ABPersonLink_old
ABStore
N77534090655128210476812812639070684519317429042401383232913500313570136429769h
M6344440980251505214334711510534398387022222632429506422215055328147354699502
..KQ/E?G7
K19C
315422BB-B907-425D-9D68-7A4D94906B1B:ABPerson
50808F95-A166-4290-97D3-3B9FA17073EB:ABPerson
http://SFYyMHtpVHVuM3NfYmFja3VwX2YwcmVuc2l4X0ZUV30=C66731B8-44AE-469B-9086-18A3A1F796B0
0 98
D0 92
B0 91
-_$!<HomePage>!$_
_$!<HomePage>!$_
[…]
```

If the "domain" part or the URL is base64 decoded, the flag emerges:

```sh
$ printf "SFYyMHtpVHVuM3NfYmFja3VwX2YwcmVuc2l4X0ZUV30=" | base64 -D
HV20{iTun3s_backup_f0rensix_FTW}
```

--------------------------------------------------------------------------------

Flag: `HV20{iTun3s_backup_f0rensix_FTW}`

