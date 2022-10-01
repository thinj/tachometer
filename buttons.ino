#include "buttons.h"

// Common 'ground' for buttons:
#define COMMON_BUTTON 18
#define UP_BUTTON 17
#define DOWN_BUTTON 19

Buttons::Buttons() {
}

void Buttons::setup() {
  // Button setup:
  pinMode(COMMON_BUTTON, OUTPUT);
  digitalWrite(COMMON_BUTTON, LOW);
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
}

void Buttons::loop() {
  // TODO
}

int Buttons::get() {
  return (digitalRead(UP_BUTTON) == HIGH ? 2 : 0) + (digitalRead(DOWN_BUTTON) == HIGH ? 1 : 0);
}