#include <Arduino.h>
#include <TM1637TinyDisplay.h>

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

// Example of defining an animation sequence for moving patterns
/* Set up 7-segment LED Binary Data

    |--A--|
    F     B
    |--G--|
    E     C
    |--D--|
           H - Decimal

    XGFEDCBA
  0b00000000
*/
const uint8_t SEG_ANIMATION[12][4] =
{
  {
    0b00001000,                                     // frame 0
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000000                                      //
  },
  {
    0b00000000,                                     // frame 1
    0b00001000,                                     //
    0b00000000,                                     //
    0b00000000                                      //
  }, {
    0b00000000,                                     // frame 2
    0b00000000,                                     //
    0b00001000,                                     //
    0b00000000                                      //
  }, {
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000000,                                     //
    0b00001000                                      //
  }, {
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000100                                      //
  }, {
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000010                                      //
  }, {
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000001                                      //
  }, {
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000001,                                     //
    0b00000000                                      //
  }, {
    0b00000000,                                     //
    0b00000001,                                     //
    0b00000000,                                     //
    0b00000000                                      //
  }, {
    0b00000001,                                     //
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000000                                      //
  }, {
    0b00100000,                                     //
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000000                                      //
  }, {
    0b00010000,                                     //
    0b00000000,                                     //
    0b00000000,                                     //
    0b00000000                                      //
  }
};

TM1637TinyDisplay display(CLK, DIO);

void setup()
{
}

void loop()
{
  int k;
  uint8_t data[] = { 0xff, 0xff, 0xff, 0xff };
  uint8_t blank[] = { 0x00, 0x00, 0x00, 0x00 };
  display.setBrightness(0x0f);

  // All segments on
  display.setSegments(data);
  delay(TEST_DELAY);

  // Example of selectively setting different digits
  data[0] = display.encodeDigit(0);
  data[1] = display.encodeDigit(1);
  data[2] = display.encodeDigit(2);
  data[3] = display.encodeDigit(3);
  display.setSegments(data);
  delay(TEST_DELAY);

  display.clear();
  display.setSegments(data + 2, 2, 2);
  delay(TEST_DELAY);

  display.clear();
  display.setSegments(data + 2, 2, 1);
  delay(TEST_DELAY);

  display.clear();
  display.setSegments(data + 1, 3, 1);
  delay(TEST_DELAY);

  // Show decimal numbers with/without leading zeros
  display.showNumber(0, false); // Expect: ___0
  delay(TEST_DELAY);
  display.showNumber(0, true);  // Expect: 0000
  delay(TEST_DELAY);
  display.showNumber(1, false); // Expect: ___1
  delay(TEST_DELAY);
  display.showNumber(1, true);  // Expect: 0001
  delay(TEST_DELAY);
  display.showNumber(301, false); // Expect: _301
  delay(TEST_DELAY);
  display.showNumber(301, true); // Expect: 0301
  delay(TEST_DELAY);
  display.clear();
  display.showNumber(14, false, 2, 1); // Expect: _14_
  delay(TEST_DELAY);
  display.clear();
  display.showNumber(4, true, 2, 2);  // Expect: __04
  delay(TEST_DELAY);
  display.showNumber(-1, false);  // Expect: __-1
  delay(TEST_DELAY);
  display.showNumber(-12);        // Expect: _-12
  delay(TEST_DELAY);
  display.showNumber(-999);       // Expect: -999
  delay(TEST_DELAY);
  display.clear();
  display.showNumber(-5, false, 3, 0); // Expect: _-5_
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

  // Run through all the dots
  for (k = 0; k <= 4; k++) {
    display.showNumberDec(0, (0x80 >> k), true);
    delay(TEST_DELAY);
  }

  // Brightness Test
  for (k = 0; k < 4; k++)
    data[k] = 0xff;
  for (k = 0; k < 7; k++) {
    display.setBrightness(k);
    display.setSegments(data);
    delay(TEST_DELAY);
  }

  // On/Off Examples
  for (k = 0; k < 4; k++) {
    display.setBrightness(7, false);  // Turn off
    display.setSegments(data);
    delay(TEST_DELAY);
    display.setBrightness(7, true); // Turn on
    display.setSegments(data);
    delay(TEST_DELAY);
  }

  // Level Examples
  //    horizontal
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
  //    vertical
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

  // String Usage Examples
  display.clear();
  display.showString("String Test 1234");
  delay(TEST_DELAY);
  display.clear();
  display.showString("25\xB0\C");   // display 25 + degree symbol + C
  delay(TEST_DELAY);
  display.clear();
  display.showString("abcdefghijklmnopqrstuvwxyz.-=ABCDEFGHIJKLMNOPQRSTUVWXYZ");
  delay(TEST_DELAY);
  display.clear();
  display.showString("The");
  delay(TEST_DELAY);
  display.clear();
  display.showString("End");
  delay(TEST_DELAY);

  // Animation sequence - Run 3 times
  display.clear();
  for (int count = 0; count < 3; count++) {
    display.showAnimation(SEG_ANIMATION, 12, 10);
  }
  display.clear();
  delay(TEST_DELAY);

  // Done!
  display.setSegments(SEG_DONE);

  delay(TEST_DELAY * 5);

}
