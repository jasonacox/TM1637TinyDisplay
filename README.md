# TM1637 Tiny Display

[![arduino-library-badge](https://www.ardu-badge.com/badge/TM1637TinyDisplay.svg?)](https://www.ardu-badge.com/TM1637TinyDisplay)
[![Build Status](https://github.com/jasonacox/TM1637TinyDisplay/actions/workflows/sketch.yml/badge.svg)](https://github.com/jasonacox/TM1637TinyDisplay/actions/workflows/sketch.yml)

Arduino Library for the TM1637 Based LED Display Module

## Description

This is an Arduino library for 4 and 6 digit 7-segment LED display modules based on the TM1637 chip.
Connect the TM1637 display CLK and DIO pins to your Arduino GPIO pins, include this library, initialize TM1637TinyDisplay and call easy to use functions like `showNumber()`, `showString()`, `showLevel()` and `showAnimation()`. Display will scroll text for larger strings. Functions support screen splitting for easy number + text formatting. Library also runs well on tiny controllers including the ATtiny85.

## Hardware

![TM1637](https://raw.githubusercontent.com/jasonacox/TM1637TinyDisplay/master/examples/tm1637.png)

* 4-Digit Display modules based on the TM1637 chip are available from [HiLetgo](https://www.amazon.com/gp/product/B01DKISMXK/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1), [DX](https://dx.com/p/0-36-led-4-digit-display-module-for-arduino-black-blue-works-with-official-arduino-boards-254978) and [SeeedStudio](https://www.digikey.com/products/en?keywords=tm1637).
* 6-Digit Display modules - see [here](https://github.com/jasonacox/TM1637TinyDisplay#tm1637-6-digit-display---tm1637tinydisplay6).

![TM1637](https://raw.githubusercontent.com/jasonacox/TM1637TinyDisplay/master/examples/tm1637back.png)

The display has four connectors:

* CLK - Clock - attach to any GPIO output
* DIO - Data  - attach to any GPIO output
* VCC - Power 5v
* GND - Ground

**Power Note:** Steady clean power is important for circuit stability. If you are seeing display artifacts during high frequency updates or animation sequences, you may be experiencing power fluctuations that are impacting signal timing and communication with the TM1637. This is especially true with standalone microprocessor applications that lack any power conditioning (e.g. ATtiny85). A polarized 100uF electrolytic capacitor inserted across VCC and GND can help smooth out the spikes.

**Decimals and Colons:** Some TM1637 displays come equipped with a middle colon LED (like above) as used in digital clocks but with no decimal points. Some displays come with decimal point LEDS for each digit. Some come with both but often the decimal point LEDs are not connected. These extra LEDs are activated by setting the upper eighth bit (0x80) for the digit to the left of the dot. This library will handle setting that for you via the `showNumber()` function when you specify floating point numbers, or you can do it manually via the `showNumberDec()` function where you can set the decimal points/colon yourself.

## Installation

This library is available via the Arduino IDE.  Install this library via `Tools`, `Manage Libraries`, search for "TM1637TinyDisplay" and click `Install`.

Alternatively, you can install this manually by cloning this repo into your Arduino library folder (e.g. `~/Documents/Arduino/libraries`).

## Example Code

<p align="center">
  <a href="examples/4-digit-display-basic.fzz"><img src="examples/4-digit-display-basic_bb.svg" width="40%" /></a><br />
  Basic connection schematic done with <a href="https://fritzing.org">Fritzing</a>
</p>

```cpp
#include <Arduino.h>
#include <TM1637TinyDisplay.h>

// Define Digital Pins
#define CLK 2
#define DIO 3

// Instantiate TM1637TinyDisplay Class
TM1637TinyDisplay display(CLK, DIO);

void setup() {
  // Initialize Display
  display.begin();
}

void loop() {
  // Say Hello
  display.showString("HELLO");
  delay(500);

  // Clear Screen
  display.clear();

  // We can count!
  for (int x = -100; x <= 100; x++) {
    display.showNumber(x);
  }

  // Level indicator
  for (int x = 0; x <= 100; x = x + 10) {
    display.showLevel(x, false);
    delay(20);
  }
  for (int x = 100; x >= 0; x = x - 10) {
    display.showLevel(x, false);
    delay(20);
  }

  // Split screen for temperature
  display.showString("\xB0", 1, 3);        // Degree Mark, length=1, position=3 (right)
  for (int x = -90; x < 200; x++) {
    display.showNumber(x, false, 3, 0);    // Number, length=3, position=0 (left)
    delay(10);
  }

  // The end
  display.showString("End");
  delay(1000);
}
```

## Animation and Animator Tool

The `showAnimation()` function projects a sequence of frames (patterns) onto the display.  This works by defining the animation sequence through a multi-dimensional array of patterns.

You can use the included javascript based interactive [7-Segment LED Animator Tool](https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator.html) to help build your animation. The source code is in the [Examples](examples) folder. This tool will let you set up the LED sequences you want, save each frame and copy the final code (a static array) directly into your sketch to use for the `showAnimation(data, frames, timing)` function. Here is an example:

```cpp
// Data from Animator Tool
const uint8_t ANIMATION[12][4] = {
  { 0x08, 0x00, 0x00, 0x00 },  // Frame 0
  { 0x00, 0x08, 0x00, 0x00 },  // Frame 1
  { 0x00, 0x00, 0x08, 0x00 },  // Frame 2
  { 0x00, 0x00, 0x00, 0x08 },  // Frame 3
  { 0x00, 0x00, 0x00, 0x04 },  // Frame 4
  { 0x00, 0x00, 0x00, 0x02 },  // Frame 5
  { 0x00, 0x00, 0x00, 0x01 },  // Frame 6
  { 0x00, 0x00, 0x01, 0x00 },  // Frame 7
  { 0x00, 0x01, 0x00, 0x00 },  // Frame 8
  { 0x01, 0x00, 0x00, 0x00 },  // Frame 9
  { 0x20, 0x00, 0x00, 0x00 },  // Frame 10
  { 0x10, 0x00, 0x00, 0x00 }   // Frame 11
};

  // Display Animation sequence
  display.showAnimation(ANIMATION, FRAMES(ANIMATION), TIME_MS(50));

```
## TM1637 6-Digit Display - TM1637TinyDisplay6

![TM1637-6](https://raw.githubusercontent.com/jasonacox/TM1637TinyDisplay/master/examples/tm1637-6.png)

6-Digit Display modules based on the TM1637 chip are available from [Amazon](https://smile.amazon.com/diymore-Display-Digital-Decimal-Segments/dp/B08G4BYR2B/ref=sr_1_2?crid=2ZNMBUFWRVDIL&dchild=1&keywords=tm1637%2B6%2Bdigit&qid=1617163070&sprefix=tm1637%2B%2Caps%2C218&sr=8-2&th=1) and [AliExpress](https://www.aliexpress.com/item/1005002060120661.html?spm=a2g0s.9042311.0.0.47454c4dYpnXsR). 

![TM1637-6-Back](https://raw.githubusercontent.com/jasonacox/TM1637TinyDisplay/master/examples/tm1637-6-back.png)

This library now supports the 6-digit display as well as the 4-digit display.  The 6-digit display requires additional handling.  Specifically, the display digits are not sequential (requires a map) and the 7-segment LED data must be uploaded in reverse order.

TM1637TinyDisplay6 handles this for you but you must initialize the display using the TM1637TinyDisplay6 class:

```cpp
// Includes
#include <Arduino.h>
#include <TM1637TinyDisplay6.h>       // Include 6-Digit Display Class Header

// Define Digital Pins
#define CLK 2
#define DIO 3

TM1637TinyDisplay6 display(CLK, DIO); // 6-Digit Display Class

void setup()
{
  display.begin();
  display.showString("digits");
  delay(1000);
  display.showNumber(123456);
  delay(1000);
  display.showNumber(123.456);
  delay(1000);
}
```

## Functions

The library provides a single class named TM1637TinyDisplay with the following functions:

* `begin()` - Initialize display memory and hardware (call in `setup()`)
* `clear()` - Display an integer and floating point numbers (positive or negative)
* `showNumber(..)` - Display a number
* `showNumberDec(..)` - Display a number with ability to manually set decimal points or colon
* `showNumberHex(..)` - Display a number in hexadecimal format and set decimal point or colon
* `showString(..)` - Display a ASCII string of text with optional scrolling for long strings
* `startStringScroll(..)` - Begins a non-blocking scrolling of a string message
* `showLevel(..)` - Use display LEDs to simulate a level indicator (vertical or horizontal)  
* `showAnimation(..)` - Display a sequence of frames to render an animation
* `startAnimation(..)` - Begins a non-blocking animation of a sequence of frames
* `Animate()` - Worker routine to be called regularly which handles animations and scrolling in a non-blocking manner
* `stopAnimation(..)` - Stops non-blocking animation
* `setSegments(..)` - Directly set the value of the LED segments in each digit
* `setBrightness(..)` - Sets the brightness of the display
* `setScrolldelay(..)` - Sets the speed for text scrolling
* `flipDisplay(..)` - Sets/flips the orientation of the display
* `isflipDisplay()` - Returns orientation of the display (True = flip)
* `readBuffer(..)` - Returns current display segment values

PROGMEM functions: Large string or animation data can be left in Flash instead of being loaded in to SRAM to save memory.

* `showAnimation_P(..)` - Display a sequence of frames to render an animation (in PROGMEM)
* `showString_P(..)` - Display a ASCII string of text with optional scrolling for long strings (in PROGMEM)
* `startAnimation_P(..)` - Begins a non-blocking animation of a sequence of frames stored in PROGMEM
* `startStringScroll_P(..)` - Begins a non-blocking scrolling of a string message stored in PROGMEM

Refer to [TM1637TinyDisplay.h](TM1637TinyDisplay.h) for information on available functions. See also [Examples](examples) for more demonstration.

## Arduino Library

* Library: https://www.arduinolibraries.info/libraries/tm1637-tiny-display
* Scan Logs: http://downloads.arduino.cc/libraries/logs/github.com/jasonacox/TM1637TinyDisplay/

## References and Credit

* This library is based on the great work by Avishay Orpaz - https://github.com/avishorp/TM1637
* SevenSegmentTM1637 Arduino Library by Bram Harmsen - https://github.com/bremme/arduino-tm1637 
* Arduino - https://playground.arduino.cc/Main/TM1637/
* Titan Micro Electronics Datasheet for TM1637 - [View](docs/TM1637.pdf) [\[Download\]](http://www.titanmec.com/index/article/download.html?file=aHR0cDovL3R3ZHotYXNzZXRzLmRqd2VpbGFpLmNvbS90d2R6X2VuLzIwMjQwMzA5LzIwMjQwMzA5MTQxNjM3OTkxLnBkZg%3D%3D&name=TM1637)
* TM16xx - Library for entire TM16xx chip family include maxint-rd's own [display-modules](https://github.com/maxint-rd/arduino-modules#display-modules) - https://github.com/maxint-rd/TM16xx
