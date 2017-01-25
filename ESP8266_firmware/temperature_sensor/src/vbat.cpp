#include "vbat.hpp"

ADC_MODE(ADC_VCC);

VBAT::VBAT() {
}

void VBAT::begin() {
}

float VBAT::get_vbat() {
  return ESP.getVcc()/1024.0;
}
