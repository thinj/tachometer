#include <LiquidCrystal.h>
#include "display.h"
#include "runstat.h"



// make some custom characters:
byte abx[6][8] = {
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

Display::Display():aLcd(RS, EN, D4, D5, D6, D7) {
}

void Display::setup() {
  // initialize LCD and set up the number of columns and rows:
  aLcd.begin(16, 2);

  for (int i = 0; i < 6; i++) {
    // create a new character
    aLcd.createChar(i, abx[i]);
  }

  // Backlight setup:
  pinMode(_BACKLIGHT, OUTPUT);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Display::loop() {
  if (runStat.isSecond()) {
    showRPM();
    backlight();
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void Display::backlight() {
  analogWrite(_BACKLIGHT, 255);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void Display::showRPM() {
  aLcd.setCursor(0, 0);
  char buffer[30];
  sprintf(buffer, "RPM:%04d", measureRPM.getRPM());
  aLcd.print(buffer);
  // 100 RPM  / pixel
  int len = measureRPM.getRPM() / 100;
  for (int i = 0; i < 8; i++) {
    byte b = len >= 5 ? 5 : len;
    aLcd.write((byte)b);
    len -= b;
  }
  aLcd.setCursor(0, 1);
  int lc = runStat.getLoopCount() / 1000;
  sprintf(buffer, "H1:%4d,H2:%3dk", buttons.get(), lc);
  aLcd.print(buffer);
}
