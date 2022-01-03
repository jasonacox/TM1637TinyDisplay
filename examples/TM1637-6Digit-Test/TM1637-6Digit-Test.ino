//  TM1637TinyDisplay TEST Sketch for 6-Digit Display
//  This is a test sketch for the Arduino TM1637TinyDisplay LED Display library
//
//  Author: Jason A. Cox - @jasonacox - https://github.com/jasonacox
//  Date: 29 March 2021
//

// Includes
#include <Arduino.h>
#include <TM1637TinyDisplay6.h>

// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 5

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   1000

// Example of manually defining a display pattern
const uint8_t SEG_DONE[] = {
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,           // d
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,   // O
  SEG_C | SEG_E | SEG_G,                           // n
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G            // E
};

// Example animation sequence for showAnimation() Test
//  Built with 7-Segment Animator Tool for 6-Digit Displays
//  https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator6.html

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

// To save RAM space, we can store the animation sequences in PROGMEM read-only flash memory.
// This requires using the showAnimation_P() function to read from PROGMEM memory space.

const uint8_t ANIMATION2[92][6] PROGMEM = {
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
  { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 15
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 16
  { 0x80, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 17
  { 0x80, 0x80, 0x00, 0x00, 0x00, 0x00 },  // Frame 18
  { 0x80, 0x80, 0x80, 0x00, 0x00, 0x00 },  // Frame 19
  { 0x80, 0x80, 0x80, 0x80, 0x00, 0x00 },  // Frame 20
  { 0x80, 0x80, 0x80, 0x80, 0x80, 0x00 },  // Frame 21
  { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },  // Frame 22
  { 0x80, 0x80, 0x80, 0x80, 0x80, 0x81 },  // Frame 23
  { 0x80, 0x80, 0x80, 0x80, 0x81, 0x80 },  // Frame 24
  { 0x80, 0x80, 0x80, 0x81, 0x80, 0x80 },  // Frame 25
  { 0x80, 0x80, 0x81, 0x80, 0x80, 0x80 },  // Frame 26
  { 0x80, 0x81, 0x80, 0x80, 0x80, 0x80 },  // Frame 27
  { 0x81, 0x80, 0x80, 0x80, 0x80, 0x80 },  // Frame 28
  { 0x80, 0x80, 0x80, 0x80, 0x80, 0x80 },  // Frame 29
  { 0xb0, 0x80, 0x80, 0x80, 0x80, 0x80 },  // Frame 30
  { 0x06, 0x80, 0x80, 0x80, 0x80, 0x80 },  // Frame 31
  { 0x00, 0xb0, 0x80, 0x80, 0x80, 0x80 },  // Frame 32
  { 0x00, 0x06, 0x80, 0x80, 0x80, 0x80 },  // Frame 33
  { 0x00, 0x00, 0xb0, 0x80, 0x80, 0x80 },  // Frame 34
  { 0x00, 0x00, 0x06, 0x80, 0x80, 0x80 },  // Frame 35
  { 0x00, 0x00, 0x00, 0xb0, 0x80, 0x80 },  // Frame 36
  { 0x00, 0x00, 0x00, 0x06, 0x80, 0x80 },  // Frame 37
  { 0x00, 0x00, 0x00, 0x00, 0xb0, 0x80 },  // Frame 38
  { 0x00, 0x00, 0x00, 0x00, 0x06, 0x80 },  // Frame 39
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0xb0 },  // Frame 40
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x06 },  // Frame 41
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 42
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 },  // Frame 43
  { 0x00, 0x00, 0x00, 0x00, 0x46, 0x00 },  // Frame 44
  { 0x00, 0x00, 0x00, 0x46, 0x00, 0x00 },  // Frame 45
  { 0x00, 0x00, 0x46, 0x00, 0x00, 0x00 },  // Frame 46
  { 0x00, 0x46, 0x00, 0x00, 0x00, 0x00 },  // Frame 47
  { 0x46, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 48
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 49
  { 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 50
  { 0x40, 0x01, 0x00, 0x00, 0x00, 0x00 },  // Frame 51
  { 0x08, 0x40, 0x01, 0x00, 0x00, 0x00 },  // Frame 52
  { 0x01, 0x08, 0x40, 0x01, 0x00, 0x00 },  // Frame 53
  { 0x40, 0x01, 0x08, 0x40, 0x01, 0x00 },  // Frame 54
  { 0x08, 0x40, 0x01, 0x08, 0x40, 0x01 },  // Frame 55
  { 0x00, 0x08, 0x40, 0x01, 0x08, 0x40 },  // Frame 56
  { 0x00, 0x00, 0x08, 0x40, 0x01, 0x08 },  // Frame 57
  { 0x00, 0x00, 0x00, 0x08, 0x40, 0x01 },  // Frame 58
  { 0x00, 0x00, 0x00, 0x00, 0x08, 0x40 },  // Frame 59
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x08 },  // Frame 60
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 61
  { 0x4f, 0x00, 0x00, 0x00, 0x00, 0x66 },  // Frame 62
  { 0x5b, 0x4f, 0x00, 0x00, 0x66, 0x6d },  // Frame 63
  { 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d },  // Frame 64
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 65
  { 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d },  // Frame 66
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 67
  { 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d },  // Frame 68
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 69
  { 0x63, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 70
  { 0x00, 0x5c, 0x00, 0x00, 0x00, 0x00 },  // Frame 71
  { 0x00, 0x00, 0x63, 0x00, 0x00, 0x00 },  // Frame 72
  { 0x00, 0x00, 0x00, 0x5c, 0x00, 0x00 },  // Frame 73
  { 0x00, 0x00, 0x00, 0x00, 0x63, 0x00 },  // Frame 74
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c },  // Frame 75
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 76
  { 0x79, 0x00, 0x00, 0x00, 0x00, 0x00 },  // Frame 77
  { 0x54, 0x79, 0x00, 0x00, 0x00, 0x00 },  // Frame 78
  { 0x5c, 0x54, 0x79, 0x00, 0x00, 0x00 },  // Frame 79
  { 0x5e, 0x5c, 0x54, 0x79, 0x00, 0x00 },  // Frame 80
  { 0x00, 0x5e, 0x5c, 0x54, 0x79, 0x00 },  // Frame 81
  { 0x00, 0x5e, 0x5c, 0x54, 0x79, 0x00 },  // Frame 82
  { 0x00, 0x4e, 0x5c, 0x54, 0x79, 0x00 },  // Frame 83
  { 0x00, 0x06, 0x5c, 0x54, 0x30, 0x00 },  // Frame 84
  { 0x00, 0x00, 0x5c, 0x54, 0x00, 0x00 },  // Frame 85
  { 0x00, 0x00, 0x4c, 0x50, 0x00, 0x00 },  // Frame 86
  { 0x00, 0x00, 0x04, 0x10, 0x00, 0x00 },  // Frame 87
  { 0x00, 0x00, 0x10, 0x04, 0x00, 0x00 },  // Frame 88
  { 0x00, 0x10, 0x00, 0x00, 0x04, 0x00 },  // Frame 89
  { 0x10, 0x00, 0x00, 0x00, 0x00, 0x04 },  // Frame 90
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }   // Frame 91
};

// Text string constants can be stored in PROGMEM read-only flash memory.
// This requires using the showString_P() function to read from PROGMEM memory space.
// PROGMEM space strings are globally defined.

const PROGMEM char FlashString[] = "Flash Test - 1234567890";
const PROGMEM char FlashString2[] = "good";

TM1637TinyDisplay6 display(CLK, DIO);

void setup()
{
  display.setBrightness(BRIGHT_HIGH);
  display.clear();
}

void loop()
{
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };    // Test Pattern - All
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };   // Test Pattern - Blank
  display.setBrightness(BRIGHT_HIGH);

  // Announce Testing
  display.showString("test");
  delay(TEST_DELAY);

  // Test Basics
  display.showString("digits"); // 6 digits
  delay(TEST_DELAY);
  display.showNumber(1234567);  // overflow
  delay(TEST_DELAY);
  display.showNumber(123.456);  // decimal
  delay(TEST_DELAY);
  display.showNumber(123456.0); // decimal
  delay(TEST_DELAY);
  display.showNumber(1234567.0);// decimal
  delay(TEST_DELAY);
  display.showNumber(PI);       // decimal
  delay(TEST_DELAY);

  // All segments on
  display.setSegments(data);
  delay(TEST_DELAY);

  // Test setting different digits
  data[0] = display.encodeDigit(1);
  data[1] = display.encodeDigit(2);
  data[2] = display.encodeDigit(3);
  data[3] = display.encodeDigit(4);
  data[4] = display.encodeDigit(5);
  data[5] = display.encodeDigit(6);
  display.setSegments(data);
  delay(TEST_DELAY);

  // Test display splitting with position
  display.clear();
  display.setSegments(data + 2, 2, 2);    // Length 2, Position 2
  delay(TEST_DELAY);
  display.clear();
  display.setSegments(data + 2, 2, 1);    // Length 2, Position 1
  delay(TEST_DELAY);
  display.clear();
  display.setSegments(data + 1, 3, 1);    // Length 3, Position 1
  delay(TEST_DELAY);

  // Test decimal numbers with/without leading zeros in different positions
  display.showNumber(0, false);         // Expect: ___0
  delay(TEST_DELAY);
  display.showNumber(0, true);          // Expect: 0000
  delay(TEST_DELAY);
  display.showNumber(1, false);         // Expect: ___1
  delay(TEST_DELAY);
  display.showNumber(1, true);          // Expect: 0001
  delay(TEST_DELAY);
  display.showNumber(301, false);       // Expect: _301
  delay(TEST_DELAY);
  display.showNumber(301, true);        // Expect: 0301
  delay(TEST_DELAY);
  display.showNumber(3001, false);      // Expect: 3001
  delay(TEST_DELAY);
  display.showNumber(30001, false);     // Expect: 30001
  delay(TEST_DELAY);
  display.showNumber(300001, false);    // Expect: 300001
  delay(TEST_DELAY);
  display.clear();
  display.showNumber(14, false, 2, 1);  // Expect: _14_
  delay(TEST_DELAY);
  display.clear();
  display.showNumber(4, true, 2, 2);    // Expect: __04
  delay(TEST_DELAY);
  display.showNumber(-1, false);        // Expect: __-1
  delay(TEST_DELAY);
  display.showNumber(-12);              // Expect: _-12
  delay(TEST_DELAY);
  display.showNumber(-999);             // Expect: -999
  delay(TEST_DELAY);
  display.showNumber(-9999);            // Expect: -9999
  delay(TEST_DELAY);
  display.showNumber(-99999);           // Expect: -99999
  delay(TEST_DELAY);
  display.clear();
  display.showNumber(-5, false, 3, 0);  // Expect: _-5_
  delay(TEST_DELAY);
  display.showNumberHex(0xf1af);        // Expect: f1Af
  delay(TEST_DELAY);
  display.showNumberHex(0x2c);          // Expect: __2C
  delay(TEST_DELAY);
  display.showNumberHex(0xd1, 0, true); // Expect: 00d1
  delay(TEST_DELAY);
  display.clear();
  display.showNumberHex(0xd1, 0, true, 2); // Expect: d1__
  delay(TEST_DELAY);

  // Floating point tests
  display.showNumber(1.234);  // Floating point number
  delay(TEST_DELAY);

  display.showNumber(1.234, 2); // Format to 2 decimal places
  delay(TEST_DELAY);

  display.showNumber(-1.23456); // Negative floating point number
  delay(TEST_DELAY);

  display.showNumber(-0.5); // Zero prefix floating point number
  delay(TEST_DELAY);

  display.showNumber(0.4);
  delay(TEST_DELAY);

  display.showNumber(1005.3);
  delay(TEST_DELAY);

  display.showNumber(1000005.3);  // Overflow test
  delay(TEST_DELAY);

  display.showNumber(0.52345, 1);
  delay(TEST_DELAY);

  display.showNumber(0.255, 2); // Test rounding up
  delay(TEST_DELAY);

  display.clear();
  display.showString("\xB0", 1, 5);   // Test with suffix
  display.showNumber(12.3456, 4, 5, 0);
  delay(TEST_DELAY);

  for (int x = -100; x < 100; x = x + 1) {  // Count
    display.showNumber((float)x / 10.0);
  }

  // Test all the dots
  for (k = 0; k <= 6; k++) {
    display.showNumberDec(0, (0x80 >> k), true);
    delay(TEST_DELAY);
  }
  uint8_t dots = 0b10101000;
  for (int x = 0; x < 8; x++) {
    display.showNumberDec(987654, dots >> x, false);       // Expect: 3.03.03.
    delay(TEST_DELAY);
  }
  dots = 0b11111100;
  for (int x = 0; x < 8; x++) {
    display.showNumberDec(123456, dots << x, false);       // Expect: 1.2.3.4.5.6.
    delay(TEST_DELAY);
  }

  // Test Brightness Levels
  for (k = 0; k < 6; k++)
    data[k] = 0xff;
  for (k = 0; k < 7; k++) {
    display.setBrightness(k);
    display.setSegments(data);
    delay(TEST_DELAY);
  }

  // Test Display On/Off
  for (k = 0; k < 4; k++) {
    display.setBrightness(7, false);    // Turn off
    display.setSegments(data);
    delay(TEST_DELAY);
    display.setBrightness(7, true);     // Turn on
    display.setSegments(data);
    delay(TEST_DELAY);
  }

  // Test Horizontal Level Meter
  for (int count = 0; count < 3; count++) {
    for (int x = 0; x <= 100; x = x + 10) {
      display.showLevel(x, true);
      delay(20);
    }
    for (int x = 100; x > 0; x = x - 10) {
      display.showLevel(x, true);
      delay(20);
    }
  }
  // Test Vertical Level Meter
  for (int count = 0; count < 3; count++) {
    for (int x = 0; x <= 100; x = x + 10) {
      display.showLevel(x, false);
      delay(20);
    }
    for (int x = 100; x > 0; x = x - 10) {
      display.showLevel(x, false);
      delay(20);
    }
  }

  // Test Numbers and Strings  Using Positions
  display.clear();
  char degree[] = "\xB0";
  display.showString(degree, 1, 5);     // Position 5 (right) and 1 char length
  for (int x = -50; x < 1500; x = x + 5) {
    display.showNumber(x, false, 5, 0); // Postion 0 (left) and 5 char length
    delay(10);
  }
  delay(TEST_DELAY);

  // Test String Display
  display.clear();
  display.showString("String Test 1234"); // Test literal string
  delay(TEST_DELAY);
  display.clear();
  char stringb[10];                 // Test dynamic string
  sprintf(stringb, "25%cC", '\xB0'); // Display 25 + degree symbol + C
  display.showString(stringb);
  delay(TEST_DELAY);
  display.clear();                  // Long string test
  display.showString("abcdefghijklmnopqrstuvwxyz.-=ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  delay(TEST_DELAY);

  // Test Strings in PROGMEM flash memory
  display.showString_P(FlashString);
  delay(1000);
  display.showString_P(FlashString2);
  delay(1000);

  // Animation Sequence Test in SRAM - Run 3 times
  display.clear();
  for (int count = 0; count < 3; count++) {
    display.showAnimation(ANIMATION, FRAMES(ANIMATION), TIME_MS(10));
  }
  display.clear();
  delay(TEST_DELAY);

  // Animation Sequence Test in PROGMEM flash memory
  display.clear();
  display.showAnimation_P(ANIMATION2, FRAMES(ANIMATION2), TIME_MS(50));

  // Done!
  display.clear();
  display.showString("The");
  delay(TEST_DELAY);
  display.showString("   End");
  delay(TEST_DELAY);
  display.setSegments(SEG_DONE);
  delay(TEST_DELAY * 5);

}
