#include "buttons.h"

Buttons::Buttons(int common, int up, int down){
  aCommon = common;
  aUp = up;
  aDown = down;
}

void Buttons::setup(){
  // Button setup:
  pinMode(aCommon, OUTPUT);
  digitalWrite(aCommon, LOW);
  pinMode(aUp, INPUT_PULLUP);
  pinMode(aDown, INPUT_PULLUP);
}

void Buttons::loop(bool update){
   // TODO
}

int Buttons::get() {
  return (digitalRead(aUp) == HIGH ? 2 : 0) + (digitalRead(aDown) == HIGH ? 1 : 0);
}
