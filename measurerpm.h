#ifndef MEASURE_RPM_H
#define MEASURE_RPM_H
class MeasureRPM {
public:
  MeasureRPM();
  void setup();
  void loop();
  int getRPM();
private:
  double aSum = 0;
  int aCount = 0;
  int aRPM;
};
#endif  // MEASURE_RPM_H