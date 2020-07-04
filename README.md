# TM1637 Tiny Display # 
[![arduino-library-badge](https://www.ardu-badge.com/badge/TM1637TinyDisplay.svg?)](https://www.ardu-badge.com/TM1637TinyDisplay)
[![Build Status](https://travis-ci.org/jasonacox/TM1637TinyDisplay.svg?branch=master)](https://travis-ci.org/github/jasonacox/TM1637TinyDisplay)

Arduino Library for the TM1637 Based LED Display Module

## Description
This is an Arduino library for 4-digit 7-segment display modules based on the TM1637 chip. 
Connect the TM1637 display CLK and DIO pins to your Arduino GPIO pins, include this library, initialize TM1637TinyDisplay and call easy to use functions like showNumber(), showString(), showLevel() and showAnimation(). Display will scroll text for larger strings. Functions support screen splitting for easy number + text formatting. Library also runs well on tiny controllers including the ATtiny85.

## Hardware 
![TM1637](examples/tm1637.png)

Display modules based on the TM1637 chip are available from [HiLetgo](https://www.amazon.com/gp/product/B01DKISMXK/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1), [DX](https://dx.com/p/0-36-led-4-digit-display-module-for-arduino-black-blue-works-with-official-arduino-boards-254978) and [SeeedStudio](https://www.digikey.com/products/en?keywords=tm1637). 

![TM1637](examples/tm1637back.png)

The display has four connectors:
* CLK - Clock - attach to any GPIO output on the Arduino
* DIO - Data  - attach to any GPIO output on the Arduino
* VCC - Power 5v
* GND - Ground

Power Note: Steady clean power is important for circuit stability. If you are seeing display artifacts during high frequency updates or animation sequences, you may be experiencing power fluctuations that are impacting signal timing and communication with the TM1637. This is especially true with standalone microprocessor applications that lack any power conditioning (e.g. ATtiny85). A polarized 100uF electrolytic capacitor inserted across VCC and GND can help smooth out the spikes.

## Installation
This library is available via the Arduino IDE.  Install this library via `Tools`, `Manage Libraries`, search for "TM1637TinyDisplay" and click `Install`.

Alternatively, you can install this manually by cloning this repo into your Arduino library folder which is set by the Arduino IDE "sketchbook location" preferences (e.g. `~/Documents/Arduino/libraries`).  

## Usage
The library provides a single class named TM1637TinyDisplay with the following functions:

* `showNumber` - Display an integer number (positive or negative)
* `showNumberDec` - Display a number with ability to set decimal points or colon
* `showNumberHex` - Display a number in hexadecimal format and set decimal point or colon
* `showString` - Display a ASCII string of text with optional scrolling for long strings
* `showLevel` - Use display LEDs to simulate a level indicator (vertical or horizontal)  
* `showAnimation` - Display a sequence of frames to render an animation
* `setSegments` - Directly set the value of the LED segments in each digit
* `setBrightness` - Sets the brightness of the display
* `setScrolldelay` - Sets the speed for text scrolling

```cpp
#include <Arduino.h>
#include <TM1637TinyDisplay.h>

// Define Digital Pins
#define CLK 1
#define DIO 2

// Initialize TM1637TinyDisplay
TM1637TinyDisplay display(CLK, DIO);

void setup() {
  display.setBrightness(0x0f);
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

Refer to [TM1637TinyDisplay.h](TM1637TinyDisplay.h) for information on available functions. See also the [TM1637Test sketch](examples) for a demonstration including animation.

## Animation and Animator Tool
The showAnimation() function projects a sequence of frames (patterns) onto the display.  This works by provide the function a multi-dimensional array of patterns.  

You can use the javascript based interactive [7-Segment LED Animator Tool](https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator.html) to help build your animation. The source code is in the [Examples](examples) folder.  This tool will let you set up the LED sequences you want, save each frame and copy the final code (a static array) directly into your sketch to use for the `showAnimation(data, frames, timing)` function.  Here is an example:

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

## References and Credit
* This library is based on the great work by Avishay Orpaz - https://github.com/avishorp/TM1637
* SevenSegmentTM1637 Arduino Library by Bram Harmsen - https://github.com/bremme/arduino-tm1637 
* Arduino - https://playground.arduino.cc/Main/TM1637/

