//  TM1637TinyDisplay TEST Sketch for 4 and 6-Digit Displays
//  This is a test countdown sketch for the Arduino TM1637TinyDisplay LED Display library
//  that also includes 4 buttons to set the countdown timer: UP, DOWN, SELECT and START
//
//  4-Digit Display:  [>1hr] hh:mm then [<1hr] mm:ss
//  6-Digit Display:  [>1hr] hh:mm:ss then [<1hr] mm:ss:hs (hundredth of seconds)
//
//  Author: Jason A. Cox - @jasonacox - https://github.com/jasonacox
//  Date: 20 May 2021
//

/* Set Display Digits - 4 or 6 */
#define DIGITS 6

/* Set GPIO Pins */
#define CLK 4             // to TM1637 Display
#define DIO 5             // to TM1637 Display
#define BUTTON_UP     6   // Button to Increase Value
#define BUTTON_DOWN   7   // Button to Increase Value
#define BUTTON_SELECT 8   // Button to Toggle through fields h:m:s to Edit
#define BUTTON_START  9   // Button to Start/Reset

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
#define numberOfHours(_time_) ( _time_ / SECS_PER_HOUR)
#define elapsedDays(_time_) ( _time_ / SECS_PER_DAY)
#define hmsToMillis(_h_, _m_, _s_) ((_h_ * SECS_PER_HOUR) + (_m_ * SECS_PER_MIN) + _s_ ) * 1000ul;

/* Global Variables in milliseconds */
unsigned long startTime;
unsigned long countDown = 0;
int state = 0;
int Hour = 0;
int Min = 0;
int Sec = 0;

void setup()
{
  display.setBrightness(BRIGHT_HIGH);
  display.clear();

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_SELECT, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);
}

void loop()
{
  unsigned long timeNow = millis();
  unsigned long timeElapsed = timeNow - startTime;  // amount of time since start
  unsigned long counter = countDown - timeElapsed; // current state of countdown
  unsigned long since = (long)(timeNow / 500);

  // Grab state of pins
  bool up = digitalRead(BUTTON_UP);
  bool down = digitalRead(BUTTON_DOWN);
  bool sel = digitalRead(BUTTON_SELECT);
  bool go = digitalRead(BUTTON_START);

  switch (state) {
    case 0:     // RESET
      Hour = 0;
      Min = 0;
      Sec = 0;
      state = 1;
      break;
    case 1:     // CLEAR DISPLAY
      display.clear();
      state = 2;
      break;
    case 2:     // INPUT HOURS
      // Flash hours field
      if (since % 2 || up == LOW || down == LOW) {
        display.showNumberDec(Hour, dots, true, 2, 0);
      }
      else display.clear();
      if (go == LOW) {
        display.clear();
        while (digitalRead(BUTTON_START) == LOW); // Wait for user to let up
        state = 10;
        break;
      }
      if (sel == LOW) {
        while (digitalRead(BUTTON_SELECT) == LOW); // Wait for user to let up
        state++;
        break;
      }
      if (up == LOW) {
        delay(100);
        if (Hour < 99) Hour++;
        else Hour = 0;
      }
      if (down == LOW) {
        delay(100);
        if (Hour > 0) Hour--;
        else Hour = 99;
      }
      break;
    case 3:     // INPUT MINUTES
      // Flash minutes field
      display.showNumberDec(Hour, dots, true, 2, 0);
      if (since % 2 || up == LOW || down == LOW) {
        display.showNumberDec(Min, dots, true, 2, 2);
      }
      else display.showString("", 2, 2);
      if (go == LOW) {
        while (digitalRead(BUTTON_START) == LOW); // Wait for user to let up
        state = 10;
        break;
      }
      if (sel == LOW) {
        while (digitalRead(BUTTON_SELECT) == LOW); // Wait for user to let up
        state++;
        break;
      }
      if (up == LOW) {
        delay(100);
        if (Min < 59) Min++;
        else Min = 0;
      }
      if (down == LOW) {
        delay(100);
        if (Min > 0) Min--;
        else Min = 59;
      }
      break;
    case 4:     // INPUT SECONDS
      // Flash seconds field
#if DIGITS == 4
      display.showString("S", 2, 0);
      if (since % 2 || up == LOW || down == LOW) {
        display.showNumberDec(Sec, dots, true, 2, 2);
      }
      else display.showString("", 2, 2);
#else
      display.showNumberDec(Hour, dots, true, 2, 0);
      display.showNumberDec(Min, dots, true, 2, 2);
      if (since % 2) {
        display.showNumberDec(Sec, 0, true, 2, 4);
      }
      else display.showString("", 2, 4);
#endif
      if (go == LOW) {
        while (digitalRead(BUTTON_START) == LOW); // Wait for user to let up
        state = 10;
        break;
      }
      if (sel == LOW) {
        while (digitalRead(BUTTON_SELECT) == LOW); // Wait for user to let up
        state++;
        break;
      }
      if (up == LOW) {
        delay(100);
        if (Sec < 59) Sec++;
        else Sec = 0;
        break;
      }
      if (down == LOW) {
        delay(100);
        if (Sec > 0) Sec--;
        else Sec = 59;
        break;
      }
      break;
    case 5:
      state = 1;
      break;
    case 10:     // GO
      // Record Start Time and countDown
      display.clear();
      startTime = millis();
      countDown = hmsToMillis(Hour, Min, Sec);
      state = 20;
      break;
    case 20:    // COUNTDOWN
    default:
      if (go == LOW) {
        state = 1; // Start over
        while (digitalRead(BUTTON_START) == LOW);
        break;
      }
      if (sel == LOW) {
        state = 0; // Reset
        while (digitalRead(BUTTON_SELECT) == LOW);
        break;
      }

      if (timeElapsed >= countDown) {
        // If we hit zero - flash every second
        since = (long)((timeElapsed - countDown) / 500);
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
      break;
  }
}
