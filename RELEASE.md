# Release Notes for TM1637TinyDisplay

## v1.7.1 - Fix Compile Errors for ESP8266

* Fix compile errors and warnings on ESP8266 cores (type casts and erroneous defaults in functions) as reported in https://github.com/jasonacox/TM1637TinyDisplay/issues/26
* Fix function names for async animation/scroll in keywords.txt by @hackerceo in https://github.com/jasonacox/TM1637TinyDisplay/pull/25

## v1.7.0 - Add Non-Blocking Animation for 4-Digit

* Add non-blocking animation and string scrolling to 4-digit display by @hackerceo in https://github.com/jasonacox/TM1637TinyDisplay/pull/24

## v1.6.0 - Add Buffered Output
- Display values are kept in persistent buffer for easier updates.
- Fix colon and decimal display for flipDisplay(true) conditions
- setBrightness() immediately updates brightness level (no data refresh needed) by @stef-ladefense in https://github.com/jasonacox/TM1637TinyDisplay/pull/20
- flipDisplay() immediately flips current display (no data refresh needed)
- readBuffer() returns current display segment values

## v1.5.2 - Bug Fix for showNumber Negative Numbers
- Fix showNumber() but for negative numbers.  Solves issues #17 (thanks to @otpfiste).
- Fix showNumber() overflow condition for numbers (positive and negative) that do not fit within display length.
```cpp
  // Example of negative case that did not render correctly
  display.showNumber(-3.1, 1, 3, 1);  // (float num, decimal length, length, position)

  // Overflow Examples - will render a dash display e.g. "----" 
  display.showNumber(-1000);
  display.showNumber(10000000);
  display.showNumber(-333.1, 1, 3, 1);
```

## v1.5.0 - Added flipDisplay Function for Device Orientation
- Added support for device orientation, flipping display upside down if selected during
initialization or through a function call.
```cpp
  // Flip display
  display.flipDisplay(true);
```

## v1.4.4 - Bug Fix for showNumber Floating Point Placement
- Bug Fix for showNumber() for floating point numbers where position is greater than zero.  Fix for TM1637TinyDisplay and TM1637TinyDisplay6.
```cpp
  // showNumber(num, decimal_length, length, pos)
  display.showNumber(9.87, 2, 3, 0);
  display.showNumber(1.23, 2, 3, 3);
```

## v1.4.3 - Added 6-Digit Animation Support
- Updated `TM1637TinyDisplay6` to support 6-digit animation.
- Added interactive [Animator Tool](https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator6.html) for 6-Digit Display's showAnimation() function (See [Link](https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator6.html))
```cpp
const uint8_t ANIMATION[16][6] = {
  { 0x08, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 0
  { 0x00, 0x08, 0x00, 0x00, 0x00, 0x00 },  // Frame 1
  { 0x00, 0x00, 0x08, 0x00, 0x00, 0x00 },  // Frame 2
  { 0x00, 0x00, 0x00, 0x08, 0x00, 0x00 },  // Frame 3
  { 0x00, 0x00, 0x00, 0x00, 0x08, 0x00 },  // Frame 4
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x08 },  // Frame 5
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x04 },  // Frame 6
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x02 },  // Frame 7
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x01 },  // Frame 8
  { 0x00, 0x00, 0x00, 0x00, 0x01, 0x00 },  // Frame 9
  { 0x00, 0x00, 0x00, 0x01, 0x00, 0x00 },  // Frame 10
  { 0x00, 0x00, 0x01, 0x00, 0x00, 0x00 },  // Frame 11
  { 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 },  // Frame 12
  { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 13
  { 0x20, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 14
  { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 }   // Frame 15
};

display.showAnimation(ANIMATION, FRAMES(ANIMATION), TIME_MS(10));
```

## v1.4.1 - Large Number Display Fix
- Bug Fix for 6-digit display - Changed to `long num` for showNumberDec() and `uint32_t num` showNumberBaseEx() to display values > 32,768.  See Issue #10
- Updated 6-digit test to include > 32,768 value tests with decimal settings.
```cpp
  display.showNumberDec(987654, 0b10101000, false);       // Expect: 3.03.03.
  display.showNumberDec(123456, 0b11111100, false);       // Expect: 1.2.3.4.5.6.
```

## v1.4.2 - Add Dots Param to showString
- Added dots parameter to showString() and showString_P() functions.
```cpp
  // void showString(const char s[], uint8_t length = MAXDIGITS, uint8_t pos = 0, uint8_t dots = 0);
  
  display.showString("HHSS",4,0,0b01000000);  // Expect: HH:SS or HH.SS
  display.showString("1234",4,0,0b01000000);  // Expect: 12:34 or 12.34
```

## v1.4.0 - 6-Digit Display Support
- Added support for 6-digit displays using `TM1637TinyDisplay6` class (see [README](https://github.com/jasonacox/TM1637TinyDisplay#tm1637-6-digit-display---tm1637tinydisplay6))
- Update showString() for variable display size and optimized code.
- Created global digits[] scratch storage for all functions.
- Update showNumber() to handle long integers.

## v1.3.0 - Lookup Tables PROGMEM
- Converted global digitToSegment[] and asciiToSegment[] lookup tables to PROGMEM space to save RAM.
- Fixed comparison between signed and unsigned integer expressions warning #5 
- Saves ~1.5kB in the ATtiny85 example by using showNumber() instead of sprintf() #6
- Fixed implicit case fallthrough and signed/unsigned comparison warnings #7

## v1.2.0 - Floating Point Numbers
- Added floating number support to showNumber() for TM1637 displays with decimal points.

## v1.1.1
- Added yield() call to example Demo sketch for esp8266 watchdog timer.

## v1.1.0 - Animation Tool
- Added interactive [Animator Tool](https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator.html) to create frame data for the showAnimation() function.
- Added demo sketch to showcase functions and animation features.

## v1.0.0
- Initial Release.
