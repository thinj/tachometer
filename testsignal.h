#ifndef TEST_SIGNAL_H
#define TEST_SIGNAL_H
class TestSignal {
public:
  TestSignal();
  void setup();
  void loop();
private:
  float aWhen = 0;
  int aGeneratedRPM = 3747;
  int aSignal = LOW;
};
#endif  // TEST_SIGNAL_H