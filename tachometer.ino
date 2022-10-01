#include "display.h"
#include "buttons.h"
#include "runstat.h"
#include "testsignal.h"
#include "measurerpm.h"
#include "display.h"

// Note! Variables declared here are automatically global, due to the way the
// entire program is 'linked': All *.ino - files are contatenated, the first
// file is this file. Declaring these 'static' does not work then, due to 
// this behaviour!
Buttons buttons;
RunStat runStat;
TestSignal testSignal;
MeasureRPM measureRPM;
Display display;

void setup() {
  runStat.setup();
  display.setup();
  buttons.setup();
  measureRPM.setup();
  testSignal.setup();
}

void loop() {
  runStat.loop();
  display.loop();
  buttons.loop();
  measureRPM.loop();
  testSignal.loop();
}
