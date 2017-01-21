#include <plug.hpp>

Plug::Plug(int pin) {
  this->pin = pin;
}

void Plug::begin() {
  pinMode(pin, OUTPUT);
}

void Plug::turn_on() {
  digitalWrite(pin, HIGH);
}

void Plug::turn_off() {
  digitalWrite(pin, LOW);
}
