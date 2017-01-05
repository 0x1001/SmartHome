#include <Arduino.h>
#include <DHT.h>

#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
  public:
    Sensor();
    void begin();
    void measure();
    float get_temperature();
    float get_humidity();
    float get_vbat();

  private:
    const int SENSOR_COMMUNICATION_PIN = 4;
    const int SENSOR_POWER_PIN = 5;
    float _temperature = 0.0;
    float _humidity = 0.0;
    float _vbat = 0.0;

    DHT _sensor;
};

#endif
