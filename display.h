#ifndef DISPLAY_H
#define DISPLAY_H

#include <LiquidCrystal.h>
#include "runstat.h"
#include "measurerpm.h"

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2

// Pin for backlight (PWM):
#define _BACKLIGHT 6

class Display {
private:
  LiquidCrystal aLcd;
  void backlight();
  void showRPM();
public:
  Display();
  void setup();
  void loop();
};
#endif  // DISPLAY_H