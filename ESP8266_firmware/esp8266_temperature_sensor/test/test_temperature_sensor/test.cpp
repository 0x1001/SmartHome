#include <Arduino.h>
#include <unity.h>
#include <FS.h>
#include <sensor.hpp>
#include <SmartHomeConfig.hpp>
#include <config.hpp>

#ifdef UNIT_TEST

void test_smart_home_config() {
  char * wifi_ssid = new char[CONFIG_STRING_SIZE];

  SmartHomeConfig config = SmartHomeConfig();
  config.begin();
  config.set_wifi_ssid("no_internet");
  config.get_wifi_ssid(wifi_ssid);

  TEST_ASSERT_EQUAL_STRING(wifi_ssid, "no_internet");
  TEST_ASSERT_TRUE(SPIFFS.exists("/configuration.json"));
}

void test_config() {
  char * temperature_topic = new char[CONFIG_STRING_SIZE];

  Config cfg = Config();
  cfg.begin();
  cfg.set_temperature_topic("/feeds/temperature");
  cfg.get_temperature_topic(temperature_topic);
  TEST_ASSERT_EQUAL_STRING(temperature_topic, "/feeds/temperature");
}

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
  RUN_TEST(test_smart_home_config);
  RUN_TEST(test_config);
  RUN_TEST(test_sensor);
  UNITY_END();
}

#endif //UNIT_TEST
