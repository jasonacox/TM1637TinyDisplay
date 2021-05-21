//  TM1637TinyDisplay TEST Sketch for 6-Digit Display
//  This is a test countdown sketch for the Arduino TM1637TinyDisplay LED Display library
//
//  Author: Jason A. Cox - @jasonacox - https://github.com/jasonacox
//  Date: 20 May 2021
//

// Includes
#include <TM1637TinyDisplay6.h>

/* Digital Pins to TM1637 */
#define CLK 4
#define DIO 5

/* Useful Constants */
#define SECS_PER_MIN  (60UL)
#define SECS_PER_HOUR (3600UL)
#define SECS_PER_DAY  (SECS_PER_HOUR * 24L)

/* Useful Macros for time (s) */
#define numberOfSeconds(_time_) (_time_ % SECS_PER_MIN)
#define numberOfMinutes(_time_) ((_time_ / SECS_PER_MIN) % SECS_PER_MIN)
#define numberOfHours(_time_) (( _time_% SECS_PER_DAY) / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)
#define hmsToMillis(_h_, _m_, _s_) ((_h_ * SECS_PER_HOUR) + (_m_ * SECS_PER_MIN) + _s_ ) * 1000ul;

/* Set up Display */
TM1637TinyDisplay6 display(CLK, DIO);

/* Global Variables in milliseconds */
unsigned long startTime;
unsigned long lastLoopTime;
unsigned long startCount;
unsigned long dispout;

void setup()
{
  display.setBrightness(BRIGHT_HIGH);
  display.clear();

  // Record Epoch - Same as Timer Reset
  startTime = millis();

  // Set countdown timer in h, m, s
  int Hour = 1;
  int Min = 0;
  int Sec = 10;
  startCount = hmsToMillis(Hour, Min, Sec);
}

void loop()
{
  unsigned long timeNow = millis();
  unsigned long timeElapsed = timeNow - startTime;  // amount of time since start
  unsigned long counter = startCount - timeElapsed; // current state of countdown

  // Update Display - every 10ms
  if (timeNow - lastLoopTime >= 10) {
    lastLoopTime = timeNow; // remember last time we displayed

    // Compute the values
    unsigned long HOURS = numberOfHours(counter / 1000);
    unsigned long MINUTES = numberOfMinutes(counter / 1000);
    unsigned long SECONDS = numberOfSeconds(counter / 1000);
    unsigned long MILLISECONDS = (counter % 1000) / 10;

    // Convert time values to integer to display
    if (HOURS <= 0) {
      // Display M:S.ms if timer is below one hour
      dispout = ((MINUTES * 10000) + (SECONDS * 100) + MILLISECONDS);
    } else {
      // Display H:M:S if timer is above one hour
      dispout = ((HOURS * 10000) + (MINUTES * 100) + SECONDS);
    }
    // Add dots or colons (depends on display module)
    uint8_t dots = 0b01010000;
    display.showNumberDec(dispout, dots);
  }
}
