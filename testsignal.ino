#include "testsignal.h"

TestSignal::TestSignal() {
  aWhen = 0;
  aSignal = LOW;
}

// Pin for generated test signal:
#define FREQ_OUT 9

void TestSignal::setup() {
  // Test frequency setup:
  pinMode(FREQ_OUT, OUTPUT);
  digitalWrite(FREQ_OUT, LOW);
}

void TestSignal::loop() {
  float millisBetween = 30000.0 / aGeneratedRPM;
  float now = millis();
  if (now >= aWhen + millisBetween) {
    aWhen += millisBetween;
    if (aSignal == LOW) {
      aSignal = HIGH;
    } else {
      aSignal = LOW;
    }
    digitalWrite(FREQ_OUT, aSignal);
  }
}