//  TM1637TinyDisplay TEST Sketch for 4 and 6-Digit Displays
//  This is a test countdown sketch for the Arduino TM1637TinyDisplay LED Display library
//  
//  4-Digit Display:  [>1hr] hh:mm then [<1hr] mm:ss
//  6-Digit Display:  [>1hr] hh:mm:ss then [<1hr] mm:ss:hs (hundredth of seconds)
//
//  Author: Jason A. Cox - @jasonacox - https://github.com/jasonacox
//  Date: 20 May 2021
//

/* Set Display Digits - 4 or 6 */
#define DIGITS 4

/* Digital Pins to TM1637 */
#define CLK 4
#define DIO 5

/* Set up 6-Digit Display */
#if DIGITS == 6
  #include <TM1637TinyDisplay6.h>
  TM1637TinyDisplay6 display(CLK, DIO);
  uint8_t dots = 0b01010000; // Add dots or colons (depends on display module)
#else

/* Set up 4-Digit Display */
  #include <TM1637TinyDisplay.h>
  TM1637TinyDisplay display(CLK, DIO);
  uint8_t dots = 0b01000000; // Add dots or colons (depends on display module)
#endif

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

/* Global Variables in milliseconds */
unsigned long startTime;
unsigned long lastLoopTime;
unsigned long countDown;

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
  countDown = hmsToMillis(Hour, Min, Sec);
}

void loop()
{
  unsigned long timeNow = millis();
  unsigned long timeElapsed = timeNow - startTime;  // amount of time since start
  unsigned long counter = countDown - timeElapsed; // current state of countdown

  // Update Display - every 10ms
  if (timeNow - lastLoopTime >= 10) {
    lastLoopTime = timeNow; // remember last time we displayed

    if (timeElapsed >= countDown) {
      // If we hit zero - flash every second
      unsigned long since = (long)((timeElapsed - countDown) / 500);
      if (since % 2) {
        display.clear();
      }
      else {
        display.showNumberDec(000000, dots, true);
      }
    }
    else {
      // Compute the values
      unsigned long HOURS = numberOfHours(counter / 1000);
      unsigned long MINUTES = numberOfMinutes(counter / 1000);
      unsigned long SECONDS = numberOfSeconds(counter / 1000);
      unsigned long MILLISECONDS = (counter % 1000) / 10;

      // Convert time values to integer to display
      if (HOURS <= 0) {
        // Display M:S.hs if timer is below one hour
        display.showNumberDec(MINUTES, dots, true, 2, 0);
        display.showNumberDec(SECONDS, dots, true, 2, 2);
#if DIGITS == 6
        display.showNumberDec(MILLISECONDS, 0, true, 2, 4);
#endif
      } else {
        // Display H:M:S if timer is above one hour
        display.showNumberDec(HOURS, dots, true, 2, 0);
        display.showNumberDec(MINUTES, dots, true, 2, 2);
#if DIGITS == 6
        display.showNumberDec(SECONDS, 0, true, 2, 4);
#endif
      }
    }
  }
}
