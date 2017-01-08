#include <Arduino.h>
#include <unity.h>
#include <FS.h>
#include <sensor.hpp>

#ifdef UNIT_TEST

void test_sensor() {
  Sensor sensor;

  sensor.measure();
  sensor.get_vbat();
  sensor.get_humidity();
  sensor.get_temperature();
}

void setup() {

}

void loop() {
  UNITY_BEGIN();
  RUN_TEST(test_sensor);
  UNITY_END();
}

#endif //UNIT_TEST
