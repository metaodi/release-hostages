# Release hostages
C implementation of the _classic_ hostages problem:

> There are 10 hostages in solitary cells.
> There's a central living room with one light bulb; this bulb is initially off.
> No hostage can see the light bulb from his or her own cell.
> Everyday, the warden picks a hostage equally at random, and that hostage visits the living room.
> While there, the hostage can toggle the bulb if he or she wishes.
> Also, the hostage has the option of asserting that all 10 hostages have been to the living room by now.
> If this assertion is false, all 10 hostages are shot.
> However, if it is indeed true, all hostages are set free.
> Thus, the assertion should only be made if the hostage is 100% certain of its validity.
> The hostages are allowed to get together one night in the courtyard, to discuss a plan.
> What plan should they agree on, so that eventually, someone will make a correct assertion?

Find more information about this code in [my blogpost from 2005](http://metaodi.ch/posts/2005/04/release-hostages/). Please note that this code is of my early days of C programming.

I really like the hostages problem, because there is no one clear solution to it and you always have the impression that maybe you can optimize it further to get the hostage out a little earlier.
Some time ago, I created the [hostages-repository](https://github.com/metaodi/hostages) to tackle the same problem in Python. And to actually compare different strategies against each other.
