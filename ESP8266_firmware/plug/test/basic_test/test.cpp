#include <Arduino.h>
#include <unity.h>
#include <plug.hpp>


#ifdef UNIT_TEST

void test_plug() {
  Plug plug(4);

  plug.begin();
  plug.turn_on();
  delay(5000);
  plug.turn_off();
}

void setup() {

}

void loop() {
  UNITY_BEGIN();
  RUN_TEST(test_plug);
  UNITY_END();
}

#endif //UNIT_TEST
