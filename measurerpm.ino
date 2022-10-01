#include <FreqMeasure.h>

#include "measurerpm.h"
#include "runstat.h"

MeasureRPM::MeasureRPM() {
}

void MeasureRPM::setup() {
  FreqMeasure.begin();
  Serial.begin(115200);
}

void MeasureRPM::loop(RunStat *runStat) {
  if (FreqMeasure.available()) {
    // average several reading together
    aSum += FreqMeasure.read();
    aCount++;
  }

  if (runStat->isSecond()) {
    if (aCount > 0) {
      // Round and not trunc:
      aRPM = (int)(0.5 + 60 * FreqMeasure.countToFrequency(aSum / aCount));
      Serial.println(aSum);
      Serial.println(aCount);
      aSum = 0;
      aCount = 0;
    } else {
      aRPM = 0;
    }
  }
}

int MeasureRPM::getRPM() {
  return aRPM;
}