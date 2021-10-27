# halloween-lights

Simple lights effects driven by an ATTiny85 assembled with three gadgets grabbed from [Thingiverse](https://www.thingiverse.com/)

- [Halloween Tree Stump LED Candle](https://www.thingiverse.com/thing:4933855) [thing:4933855]
- [Little Ghost](https://www.thingiverse.com/thing:4966110) [thing:4966110]
- [Makies Jack-O-Lantern](https://www.thingiverse.com/thing:167043) [thing:167043]

[Here](https://www.instagram.com/p/CVbRZCXsROs/) you can have a look at those 3D printed three gadgets

First of all i made a PCB with the ATTiny85, a push button and three leds (two red and one yellow) to be put in the tree stump.  
[Here](https://www.instagram.com/p/CVVo74MMpb0/) you can have a look at it.

The ATTiny85 is responsible to drive the three leds in the tree stump plus two more: a white one put inside the ghost and another yellow one put inside the pumpkin.  
[Here](https://www.instagram.com/p/CVgq-2AIUDg/) you can have a look at how i assembled the pieces.

The ATTiny85 has only trhee pwm pins so i can drive only the three leds in the tree stump. To manage the one in the pumpkin, i conneted it to the orange one in the tree stump, and the white one in the ghost, has been connected to a standard digital pin with pwm simulation implemented in software. 

Pushing the button you can select only two effects: a breath like effect and a flickering one (Default).  

Look at the [Schema.png](/Schema.png) for the circuit details.
