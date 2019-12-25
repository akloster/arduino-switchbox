# Flip Switch Box based on Arduino

This is a simple project I made in 2019 as a Christmas present for my brother. It is a box with
four Double Push Double Throw (DPDT) switches and four round LEDs on top. This project contains
the FreeCAD Source Files, STLs for 3D printing and the Arduino source code.

## BOM

-3D printed parts
    - Top plate
    - Bottom plate
    - Walls 
- Four DPDT switches
- Four screwable LED things
- 1x"Arduino Pro Micro", which is probably an Arduino Micro Clone. Important is
that it has the Atmega32u4 MCU because most 8 bit Arduino compatible boards can not emulate
the USB HID standard. Many 32 bit variants also can do that.
- A perf board
- 8 threaded inserts for 2 or 2.5mm screws (for mounting the top and bottom plate)
- 4 (potentially shorter) threaded inserts for mounting the perf board on the bottom plate.
- 12 2.5mm screws of some type. You may need to figure out the right length yourself.
- Whatever cables or fixtures you need to connect the LEDs and switches to the Arduino board.

## Assembly

- The top plate has a thin solid bottom layer, even where there are supposed to be holes.
This makes the printing of the first one or two layers much smoother and even a bit faster, but
can be easily removed.
- The walls contain a rectangular cutout for the USB cable. At least on my printer this
didn't need any support material.
- Push the 8 inserts into the holes in the corners of the walls. I do this with a soldering iron
at 230°C. I recommend using a solder tip you don't use for normal soldering. It's very important
that the inserts are exactly vertical. Otherwise the screws and plates won't fit right. Pushing
them down a little bit deeper than the top of the hole/wall is advisable.
- Testfit the top and bottom plate by screwing them on lightly, then take them off again.
- Screw the LEDs and the Switches into the holes in the top plate.
- Ensure that they are screwed on tight and don't easily turn.
- Now it's time to connect them to the Arduino. This can be done in various ways, depending on
your skill, preference and available tools.
- DPDT switches have three rows of two contacts. I used a thin silver wire to wire the top row together,
then did the same thing with the bottom row.
- I cut dupont jumper wires to the appropriate length and soldered the stripped end one each onto
the top and bottom rows, then one each to the middle contacts of the switches. (Altogether 6 wires)
- I soldered the Arduino board with its headers directly onto the perf board.
- I soldered headers onto the perf boards and connected those to digital pins. The exact ordering isn't
important. I used D2 and D3 for the top/bottom connection, and D4-D7 for the individual switches.
- The LEDs can be connected in a similar manner. They need one Digital pin each, the ground wires can
be joined together. The Pro Micro doesn't have many PWM pins, so I didn't even bother and used SoftPWM.
- Push inserts into the bottom plate and mount perf board on plate using screws.
- Put together the box by screwing the top plate on top, and then, keeping the connections intact,
screw on the bottom board.

## Firmware
- "main.ino" is the Source File.
- Connect the board to a Computer via USB.
- In the Arduino IDE choose the "Arduino/Genuino Micro" Board.
- In the library manager download and install "SoftPWM".
- Select the correct Serial Port.
- Upload and Compile.