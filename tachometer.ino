#include <LiquidCrystal.h>
#include "display.h"
#include "buttons.h"
#include "runstat.h"
#include "testsignal.h"
#include "measurerpm.h"


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// make some custom characters:
byte bx[6][8] = {
  { 0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000,
    0b00000 },
  {
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
    0b10000,
  },
  {
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
    0b11000,
  },
  {
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
    0b11100,
  },
  {
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
    0b11110,
  },
  {
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
    0b11111,
  }
};


// Pin for backlight (PWM):
int BACKLIGHT = 6;

Buttons buttons;
RunStat runStat;
TestSignal testSignal;
MeasureRPM measureRPM;

void setup() {
  runStat.setup();

  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);

  for (int i = 0; i < 6; i++) {
    // create a new character
    lcd.createChar(i, bx[i]);
  }

  // Backlight setup:
  pinMode(BACKLIGHT, OUTPUT);
  backlight(255);
  buttons.setup();
  testSignal.setup();
  measureRPM.setup();
}

void showRPM(RunStat *runStat);


////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  runStat.loop();
  testSignal.loop();
  measureRPM.loop(&runStat);

  showRPM(&runStat, &measureRPM);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void backlight(int level) {
  analogWrite(BACKLIGHT, level);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void showRPM(RunStat *runStat, MeasureRPM *measureRPM) {
  if (runStat->isSecond()) {
    lcd.setCursor(0, 0);
    char buffer[30];
    sprintf(buffer, "RPM:%04d", measureRPM->getRPM());
    lcd.print(buffer);
    // 100 RPM  / pixel
    int len = measureRPM->getRPM() / 100;
    for (int i = 0; i < 8; i++) {
      byte b = len >= 5 ? 5 : len;
      lcd.write((byte)b);
      len -= b;
    }
    lcd.setCursor(0, 1);
    int lc = runStat->getLoopCount() / 1000;
    sprintf(buffer, "H1:%4d,H2:%3dk", buttons.get(), lc);
    lcd.print(buffer);
  }
}