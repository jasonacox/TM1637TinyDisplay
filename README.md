# TM1637 Tiny Display
Arduino Library for the TM1637 Based LED Display Module

## Description
This is an Arduino library for 4-digit 7-segment display modules based on the TM1637 chip. Connect the display's CLK and DIO pins to your Arduino GPIO pins, include this library, initialize TM1637TinyDisplay and call easy to use functions like showNumber(), showString(), showLevel() and showAnimation(). Runs well on many tiny controllers including the ATtiny85.

## Hardware 
![TM1637](examples/tm1637.png)

Display modules based on the TM1637 chip are available from [HiLetgo](https://www.amazon.com/gp/product/B01DKISMXK/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1), [DX](https://dx.com/p/0-36-led-4-digit-display-module-for-arduino-black-blue-works-with-official-arduino-boards-254978) and [SeeedStudio](https://www.digikey.com/products/en?keywords=tm1637). 

![TM1637](examples/tm1637back.png)

The display has four connectors:
* CLK - Clock - attach to any GPIO output on the Arduino
* DIO - Data  - attach to any GPIO output on the Arduino
* VCC - Power 5v
* GND - Ground

## Installation
Copy this repository into your Arduino library folder as set by the Arduino IDE "sketchbook location" preferences (e.g. `~/Documents/Arduino/libraries`).  

## Usage
The library provides a single class named TM1637TinyDisplay with the following functions:

* `showNumber` - Display an integer number (positive or negative)
* `showNumberDec` - Display a number with ability to set decimal points or colon
* `showNumberHex` - Display a number in hexadecimal format and set decimal point or colon
* `showString` - Display a ASCII string of text with optional scrolling  
* `showLevel` - Use display LEDs to simulate a level indicator (vertical or horizontal)  
* `showAnimation` - Display a sequence of frames to render an animation
* `setSegments` - Directly set the value of the LED segments in each digit
* `setBrightness` - Sets the brightness of the display

Please refer to [TM1637TinyDisplay.h](TM1637TinyDisplay.h) for more information. An [example sketch](examples) is included which demonstrates the operation of the above functions.

## References and Credit
* This library is based on the great work by Avishay Orpaz - https://github.com/avishorp/TM1637
* SevenSegmentTM1637 Arduino Library by Bram Harmsen - https://github.com/bremme/arduino-tm1637 
* Arduino - https://playground.arduino.cc/Main/TM1637/

