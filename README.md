# TM1637 Tiny Display
Arduino tiny library for TM1637 LED Display

## Description
This is an Arduino library for a 4-digit 7-segment display modules based on the TM1637 chip.

## Hardware 
![TM1637](examples/tm1637.png)

Modules based on the TM1637 chip are available from [HiLetgo](https://www.amazon.com/gp/product/B01DKISMXK/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1), [DX](https://dx.com/p/0-36-led-4-digit-display-module-for-arduino-black-blue-works-with-official-arduino-boards-254978) and [SeeedStudio](https://www.digikey.com/products/en?keywords=tm1637). 

![TM1637](examples/tm1637back.png)

The display has four connectors:
* CLK - Clock - attach to any digital output on the Arduino
* DIO - Data line - attach to any digital output on the Arduino
* VCC - Power 5v
* GND - Ground

## Installation
Copy this repository into your Arduino library as defined by the Arduino IDE sketchbook location preferences (e.g. `~/Arduino/libraries`).  

## Usage
The library provides a single class named TM1637TinyDisplay. An instance of this class provides the following functions:

* `setSegments` - Set the raw value of the segments of each digit
* `showNumberDec` - Display a decimal number
* `showNumberDecEx` - Display a decimal number with decimal points or colon
* `showString` - Display a ASCII string of text with scrolling  
* `setBrightness` - Sets the brightness of the display

Please refer to TM1637TinyDisplay.h for more information. An [example sketch](examples) is included which demonstrates the operation of the above functions.

## References and Credit
* This library is based on the great work by Avishay Orpaz - https://github.com/avishorp/TM1637
* SevenSegmentTM1637 Arduino Library by Bram Harmsen - https://github.com/bremme/arduino-tm1637 
* Arduino - https://playground.arduino.cc/Main/TM1637/

