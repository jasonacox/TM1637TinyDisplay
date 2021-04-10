# Release Notes for TM1637TinyDisplay

## v1.0.0
- Initial Release.

## v1.1.0 
- Added interactive [Animator Tool](https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator.html) to create frame data for the showAnimation() function.
- Added demo sketch to showcase functions and animation features.

## v1.1.1
- Added yield() call to example Demo sketch for esp8266 watchdog timer.

## v1.2.0
- Added floating number support to showNumber() for TM1637 displays with decimal points.

## v1.3.0
- Converted global digitToSegment[] and asciiToSegment[] lookup tables to PROGMEM space to save RAM.
- Fixed comparison between signed and unsigned integer expressions warning #5 
- Saves ~1.5kB in the ATtiny85 example by using showNumber() instead of sprintf() #6
- Fixed implicit case fallthrough and signed/unsigned comparison warnings #7

## v1.4.0 
- Added support for 6-digit displays using `TM1637TinyDisplay6` class (see [README](https://github.com/jasonacox/TM1637TinyDisplay#tm1637-6-digit-display---tm1637tinydisplay6))
- Update showString() for variable display size and optimized code.
- Created global digits[] scratch storage for all functions.
- Update showNumber() to handle long integers.

## v.1.4.1
- Bug Fix for 6-digit display - Changed to `long num` for showNumberDec() and `uint32_t num` showNumberBaseEx() to display values > 32,768.  See Issue #10
- Updated 6-digit test to include > 32,768 value tests with decimal settings.
```python
  display.showNumberDec(987654, 0b10101000, false);       // Expect: 3.03.03.
  display.showNumberDec(123456, 0b11111100, false);       // Expect: 1.2.3.4.5.6.
```