#include <Arduino.h>

#ifndef PLUG_H
#define PLUG_H

class Plug {
  public:
    Plug(int pin);
    void begin();
    void turn_on();
    void turn_off();

  private:
    int pin;
};

#endif //PLUG_H
