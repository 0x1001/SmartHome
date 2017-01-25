#include <Arduino.h>

#ifndef VBAT_H
#define VBAT_H

class VBAT {
  public:
    VBAT();
    void begin();
    float get_vbat();
};

#endif //VBAT_H
