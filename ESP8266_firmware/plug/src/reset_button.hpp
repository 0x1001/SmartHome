#include <Arduino.h>

#ifndef RESET_BUTTON_H
#define RESET_BUTTON_H

#define DEBOUNCE_MAX 40000
#define DEBOUNCE_DELAY 500

class ResetButton {
  public:
    ResetButton(int pin);
    void begin(void(*func)());
    void button_interrupt();
    bool pressed();
    void reset();

  private:
    int pin;
    volatile bool button_pressed = false;
    unsigned long lastPressTime = 0;
};

#endif //RESET_BUTTON_H
