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
  if (millis() - lastPressTime < DEBOUNCE_DELAY) {
    return;
  }

  int debounce_counter = 0;
  for(int i=0; i < DEBOUNCE_MAX; i++) {
      if(digitalRead(pin) == HIGH) {
        debounce_counter++;
      }
  }

  if (debounce_counter == DEBOUNCE_MAX) {
      button_pressed = true;
  }
}
