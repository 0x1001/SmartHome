#include <reset_button.hpp>

ResetButton::ResetButton(int pin) {
  this->pin = pin;
}

void ResetButton::begin(void(*func)()) {
  pinMode(pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin), func, RISING);
}

bool ResetButton::pressed() {
  return button_pressed;
}

void ResetButton::reset() {
  button_pressed = false;
}

void ResetButton::button_interrupt() {
  static unsigned long last_interrupt = 0;
  unsigned long current_interrupt = millis();

  if (current_interrupt - last_interrupt > 200 ) {
    button_pressed = true;
  }
  last_interrupt = current_interrupt;
}
