[← Day -1](../day-1/) / [↑ TOC](../README.md) / [→ Day 02](../day02/)


# Day 1 / HV20.01 Happy HACKvent 2020



## Challenge

<!-- ...10....:...20....:...30....:...40....:...50....:...60....:...70....:. -->
* Author: mij-the-dj ([@janicmikes](https://twitter.com/janicmikes)
* Tags:   #forensic
* Level:  easy

Welcome to this year's HACKvent.

Attached you can find the "Official" invitation to the HackVent.

![](day1_1.png)

One of my very young Cyber Elves cut some parts of the card with his alpha 
scissors.

Have a great HACKvent,

– Santa



## Solution

The PNG image format can store alpha channel information for each pixel. A look
into the file with Gimp confirms the hunch: the missing areas in the picture
have transparency set to 100%. Reverting the transparency reveals the flag.

|![](day1_1_solution.png)
|-

--------------------------------------------------------------------------------

Flag: `HV20{7vxFXB-ItHnqf-PuGNqZ}`

[← Day -1](../day-1/) / [↑ TOC](../README.md) / [→ Day 02](../day02/)
