//  TM1637TinyDisplay Non-Blocking Animation/Scrolling Sketch
//  This is a test sketch for the Arduino TM1637TinyDisplay LED Display library
//  demonstrating how to do non-blocking animations and scrolling.
//
//  Author: Nick Benik - @hackerceo - https://github.com/hackerceo
//  Date: 16 Sept 2022
//

// Includes
#include <Arduino.h>
#include <TM1637TinyDisplay.h>

// Module connection pins (Digital Pins)
#define CLK 4
#define DIO 5

// The amount of time (in milliseconds) between tests
#define TEST_DELAY   1000

// Example animation sequence for showAnimation() Test
//  Built with 7-Segment Animator Tool
//  https://jasonacox.github.io/TM1637TinyDisplay/examples/7-segment-animator.html

const uint8_t ANIMATION[48][4] = {
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
  { 0x10, 0x00, 0x00, 0x00 },  // Frame 11
  { 0x08, 0x00, 0x00, 0x00 },  // Frame 12
  { 0x00, 0x08, 0x00, 0x00 },  // Frame 13
  { 0x00, 0x00, 0x08, 0x00 },  // Frame 14
  { 0x00, 0x00, 0x00, 0x08 },  // Frame 15
  { 0x00, 0x00, 0x00, 0x04 },  // Frame 16
  { 0x00, 0x00, 0x00, 0x02 },  // Frame 17
  { 0x00, 0x00, 0x00, 0x01 },  // Frame 18
  { 0x00, 0x00, 0x01, 0x00 },  // Frame 19
  { 0x00, 0x01, 0x00, 0x00 },  // Frame 20
  { 0x01, 0x00, 0x00, 0x00 },  // Frame 21
  { 0x20, 0x00, 0x00, 0x00 },  // Frame 22
  { 0x10, 0x00, 0x00, 0x00 },  // Frame 23
  { 0x08, 0x00, 0x00, 0x00 },  // Frame 24
  { 0x00, 0x08, 0x00, 0x00 },  // Frame 25
  { 0x00, 0x00, 0x08, 0x00 },  // Frame 26
  { 0x00, 0x00, 0x00, 0x08 },  // Frame 27
  { 0x00, 0x00, 0x00, 0x04 },  // Frame 28
  { 0x00, 0x00, 0x00, 0x02 },  // Frame 29
  { 0x00, 0x00, 0x00, 0x01 },  // Frame 30
  { 0x00, 0x00, 0x01, 0x00 },  // Frame 31
  { 0x00, 0x01, 0x00, 0x00 },  // Frame 32
  { 0x01, 0x00, 0x00, 0x00 },  // Frame 33
  { 0x20, 0x00, 0x00, 0x00 },  // Frame 34
  { 0x10, 0x00, 0x00, 0x00 },  // Frame 35
  { 0x08, 0x00, 0x00, 0x00 },  // Frame 36
  { 0x00, 0x08, 0x00, 0x00 },  // Frame 37
  { 0x00, 0x00, 0x08, 0x00 },  // Frame 38
  { 0x00, 0x00, 0x00, 0x08 },  // Frame 39
  { 0x00, 0x00, 0x00, 0x04 },  // Frame 40
  { 0x00, 0x00, 0x00, 0x02 },  // Frame 41
  { 0x00, 0x00, 0x00, 0x01 },  // Frame 42
  { 0x00, 0x00, 0x01, 0x00 },  // Frame 43
  { 0x00, 0x01, 0x00, 0x00 },  // Frame 44
  { 0x01, 0x00, 0x00, 0x00 },  // Frame 45
  { 0x20, 0x00, 0x00, 0x00 },  // Frame 46
  { 0x10, 0x00, 0x00, 0x00 }   // Frame 47
};

// To save RAM space, we can store the animation sequences in PROGMEM read-only flash memory.
// This requires using the showAnimation_P() function to read from PROGMEM memory space.

/* Animation Data - HGFEDCBA Map */
const uint8_t ANIMATION2[26][4] PROGMEM = {
  { 0x00, 0x00, 0x00, 0x00 },  // Frame 0
  { 0x08, 0x00, 0x00, 0x00 },  // Frame 1
  { 0x04, 0x00, 0x00, 0x00 },  // Frame 2
  { 0x40, 0x00, 0x00, 0x00 },  // Frame 3
  { 0x20, 0x00, 0x00, 0x00 },  // Frame 4
  { 0x01, 0x00, 0x00, 0x00 },  // Frame 5
  { 0x00, 0x01, 0x00, 0x00 },  // Frame 6
  { 0x00, 0x02, 0x00, 0x00 },  // Frame 7
  { 0x00, 0x40, 0x00, 0x00 },  // Frame 8
  { 0x00, 0x10, 0x00, 0x00 },  // Frame 9
  { 0x00, 0x08, 0x00, 0x00 },  // Frame 10
  { 0x00, 0x00, 0x08, 0x00 },  // Frame 11
  { 0x00, 0x00, 0x04, 0x00 },  // Frame 12
  { 0x00, 0x00, 0x40, 0x00 },  // Frame 13
  { 0x00, 0x00, 0x20, 0x00 },  // Frame 14
  { 0x00, 0x00, 0x01, 0x00 },  // Frame 15
  { 0x00, 0x00, 0x00, 0x01 },  // Frame 16
  { 0x00, 0x00, 0x00, 0x02 },  // Frame 17
  { 0x00, 0x00, 0x00, 0x40 },  // Frame 18
  { 0x00, 0x00, 0x00, 0x10 },  // Frame 19
  { 0x00, 0x00, 0x00, 0x08 },  // Frame 20
  { 0x00, 0x00, 0x00, 0x04 },  // Frame 21
  { 0x00, 0x00, 0x00, 0x40 },  // Frame 22
  { 0x00, 0x00, 0x40, 0x00 },  // Frame 23
  { 0x00, 0x40, 0x00, 0x00 },  // Frame 24
  { 0x40, 0x00, 0x00, 0x00 }   // Frame 25
};

// Strings to be scrolled from PROGMEM as well as SRAM
const PROGMEM char FlashString[] = "Flash Test - 1234567890";
const char SRamString[] = "SRAM Test - 0987654321";


byte AnimationNum;

// Initialize TM1637TinyDisplay - 4 Digit Display
TM1637TinyDisplay display(CLK, DIO);
// Initialize TM1637TinyDisplay - 6 Digit Display
// TM1637TinyDisplay6 display(CLK, DIO);

void setup()
{
  Serial.begin(9600);
  display.setBrightness(BRIGHT_HIGH);
  AnimationNum = 0;
}

void loop()
{

  
  // ### this line is used to run a single tick of the animation/scroll
  bool isAnimationRunning = display.Animate();  
  // ### returns true if an animation is still running
  

  // if there is no animation/scrolling currently running then lets start one
  if (!isAnimationRunning) {
  	
    // clear display and pause before starting the non-blocking animation/scrolling
    display.clear();
    delay(TEST_DELAY);

    // switch to the next animation/scrolling to run
    AnimationNum++;

    // start it
    switch(AnimationNum) {
      case 1:
        Serial.println("");
        Serial.println("Animate from SRAM");
        // non-blocking animation from SRAM
		    display.startAnimation(ANIMATION, FRAMES(ANIMATION), TIME_MS(50));
        break;
      case 2:
        Serial.println("");
        Serial.println("Animate from PROGMEM");
        // non-blocking animation from PROGMEM
        display.startAnimation_P(ANIMATION2, FRAMES(ANIMATION2), TIME_MS(50));
        break;
      case 3:
        Serial.println("");
        Serial.println("Animated String Scroll from PROGMEM");
        // non-blocking scrolling of a long string
        display.startStringScroll_P(FlashString, 200); 
        break;
      case 4:
        Serial.println("");
        Serial.println("Animated String Scroll from SRAM");
        // non-blocking scrolling of a long string
        display.startStringScroll(SRamString, 200);
        break;
      default:
        display.showString("The");
        delay(TEST_DELAY);
        display.showString("End");
        delay(TEST_DELAY * 5);
        // start the sequence over again
        AnimationNum = 0;
    }
  }

  // do something while the animation is running
  Serial.print(".");
}