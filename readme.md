## BakeryQuest!

As a project for my kids, I made it possible for the MagiQuest wants to be used in
our house with various outcomes. There are a number of projects like this out there,
but where most people make one thing work, I wanted to make 8. 

This is a C++ library that wraps the ESP8266 and IR sensor libraries with
a nicer interface for building a wand sensor and handler. It's the foundation that I 
used for all 8 of my projects.

It's designed specifically to work with an [Adafruit Feather Huzzah](https://www.adafruit.com/product/2821), but it
should easily work with any other ESP8266 board.

The IR sensor I use is the [TSOP38236](https://www.digikey.com/product-detail/en/vishay-semiconductor-opto-division/TSOP38236/TSOP38236-ND/4073518), which is a 36hz sensor and seems to be
the right choice vs the more common 38hz sensors. The TSOP38238 worked, but 
wasn't getting readings that were as reliable.

### Installation

To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder. You can delete the ./examples folder.

When installed, this library should look like:

```
Arduino/lib/targets/libraries/BakeryQuest                     (this library's folder)
Arduino/lib/targets/libraries/BakeryQuest/BakeryQuest.cpp     (the library implementation file)
Arduino/lib/targets/libraries/BakeryQuest/BakeryQuest.h       (the library description file)
Arduino/lib/targets/libraries/BakeryQuest/keywords.txt        (the syntax coloring file)
Arduino/lib/targets/libraries/BakeryQuest/readme.txt          (this file)
```

### Building

After this library is installed, you just have to start the Arduino application.
You may see a few warning messages as it's built.

To use this library in a sketch, go to the Sketch | Import Library menu and
select BakeryQuest.  This will add a corresponding line to the top of your sketch:
#include <BakeryQuest.h>

To stop using this library, delete that line from your sketch.

#### Geeky information:

After a successful build of this library, a new file named "BakeryQuest.o" will appear
in "Arduino/lib/targets/libraries/BakeryQuest". This file is the built/compiled library
code.

If you choose to modify the code for this library (i.e. "BakeryQuest.cpp" or "BakeryQuest.h"),
then you must first 'unbuild' this library by deleting the "BakeryQuest.o" file. The
new "BakeryQuest.o" with your code will appear after the next press of "verify"

