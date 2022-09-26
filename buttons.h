#ifndef BUTTONS_H
#define BUTTONS_H
class Buttons
{
   public:
      Buttons(int common, int up, int down);
      void setup();
      void loop(bool update);
      int get();
   private:
      int aCommon;
      int aUp;
      int aDown;
};
#endif // BUTTONS_H
