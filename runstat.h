#ifndef RUNSTAT_H
#define RUNSTAT_H
class RunStat {
public:
  RunStat();
  void setup();
  void loop();
  unsigned long getLoopCount();
  bool isSecond();
private:
  bool aSec;
  int a100MillisCount;
  bool a100Millis;
  unsigned long aLoopCount;
  unsigned long aLoopWhen;
};
#endif  // RUNSTAT_H