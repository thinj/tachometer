#include <LiquidCrystal.h>
#include <FreqMeasure.h>
#include "buttons.h"


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// make some custom characters:
byte bx[6][8] = {
  {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00000
}, {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
}, {
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
  0b11000,
}, {
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
  0b11100,
}, {
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
  0b11110,
}, {
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


// Pin for generated test signal:
int FREQ_OUT = 9;

// Pin for backlight (PWM):
int BACKLIGHT = 6;

// Common 'ground' for buttons:
int COMMON_BUTTON = 18;
int UP_BUTTON = 17;
int DOWN_BUTTON = 19;

Buttons buttons(COMMON_BUTTON, UP_BUTTON, DOWN_BUTTON);

void setup() {
  // initialize LCD and set up the number of columns and rows:
  lcd.begin(16, 2);

  for (int i = 0; i < 6; i++) {
      // create a new character
      lcd.createChar(i, bx[i]);
  }

  showRPM(true);

  FreqMeasure.begin();
  Serial.begin(115200);

  // Test frequency setup:
  pinMode(FREQ_OUT, OUTPUT);
  digitalWrite(FREQ_OUT, LOW);

  // Backlight setup:
  pinMode(BACKLIGHT, OUTPUT);

  buttons.setup();
}
  
int rpm = 0;
unsigned long loopCount = 0;

unsigned long loopWhen = 0;
#define UPDATE_INTERVAL_MILLIS 1000

////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  unsigned long now = millis();  
  loopCount++;
  bool update = false;
  if (now >= loopWhen + UPDATE_INTERVAL_MILLIS) {
    update = true;
  }
  if (update) {
    loopWhen += UPDATE_INTERVAL_MILLIS;
  }
  measureRPM(update);
  showRPM(update);
  backlight(update);
  
  generateTestSignal();  

  if (update) {
    loopCount = 0;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void backlight(bool update) {
  if (update) {
      analogWrite(BACKLIGHT, 255);
  }
  //analogWrite(BACKLIGHT, 250);
//  digitalWrite(BACKLIGHT, LOW);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void showRPM(bool update) {
  if (update) {
    lcd.setCursor(0, 0);
    char buffer[30];
    sprintf(buffer, "RPM:%04d", rpm);
    lcd.print(buffer);
    // 100 RPM  / pixel
    int len = rpm / 100;
    for (int i = 0; i < 8; i++) {
        byte b = len >= 5 ? 5 : len;
        lcd.write((byte)b);      
        len -= b;
    }
    lcd.setCursor(0, 1);
    int lc = loopCount / 1000;
    sprintf(buffer, "H1:%4d,H2:%3dk",  buttons.get(),lc);
    lcd.print(buffer);
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
double sum=0;
int count=0;

void measureRPM(bool update) {
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
  }

  if (update) {
    if (count > 0) {
      // Round and not trunc:
      rpm = (int) (0.5 + 60 * FreqMeasure.countToFrequency(sum / count));
      Serial.println(sum);
      Serial.println(count);
      sum = 0;
      count = 0;
    } else {
      rpm = 0;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
float when = 0;
int generatedRPM = 3747;
int signal = LOW;
void generateTestSignal() {
  float millisBetween = 30000.0 / generatedRPM;
  float now = millis();
  if (now >= when + millisBetween) {
    when += millisBetween;
    if (signal == LOW) {
      signal = HIGH;
    } else {
      signal = LOW;
    }
    digitalWrite(FREQ_OUT, signal);
  }
}
