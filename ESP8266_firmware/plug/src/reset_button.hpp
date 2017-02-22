#include <Arduino.h>

#ifndef RESET_BUTTON_H
#define RESET_BUTTON_H

class ResetButton {
  public:
    ResetButton(int pin);
    void begin(void(*func)());
    void button_interrupt();
    bool pressed();
    void reset();

  private:
    int pin;
    bool button_pressed = false;
};

#endif //RESET_BUTTON_H
