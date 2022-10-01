#include "runstat.h"

RunStat::RunStat() {
  aSec = false;
  a100Millis = false;
  aLoopCount = 0;
  a100MillisCount = 0;
  aLoopWhen = 0;
}

void RunStat::setup() {
}

void RunStat::loop() {
  if (aSec) {
    aLoopCount = 0;
  } else {
    aLoopCount++;
  }

  unsigned long now = millis();

  a100Millis = (now >= aLoopWhen + 100);
  if (a100Millis) {
    aLoopWhen += 100;
    a100MillisCount++;
  }

  aSec = (a100MillisCount >= 10);
  if (aSec) {
    a100MillisCount -= 10;
  }
}

unsigned long RunStat::getLoopCount() {
  return aLoopCount;
}

bool RunStat::isSecond() {
  return aSec;
}