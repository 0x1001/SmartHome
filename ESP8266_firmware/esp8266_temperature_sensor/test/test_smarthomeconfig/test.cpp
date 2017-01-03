#include <Arduino.h>
#include <unity.h>
#include <FS.h>
#include <SmartHomeConfig.h>
#include <config.h>

#ifdef UNIT_TEST

void test_smart_home_config(void) {
  char * wifi_ssid = new char[CONFIG_STRING_SIZE];

  SmartHomeConfig config = SmartHomeConfig();
  config.begin();
  config.set_wifi_ssid("no_internet");
  config.get_wifi_ssid(wifi_ssid);

  TEST_ASSERT_EQUAL_STRING(wifi_ssid, "no_internet");
  TEST_ASSERT_TRUE(SPIFFS.exists("/configuration.json"));
}

void test_config(void) {
  char * temperature_topic = new char[CONFIG_STRING_SIZE];

  Config cfg = Config();
  cfg.begin();
  cfg.set_temperature_topic("/feeds/temperature");
  cfg.get_temperature_topic(temperature_topic);
  TEST_ASSERT_EQUAL_STRING(temperature_topic, "/feeds/temperature");
}

void setup() {

}

void loop() {
  UNITY_BEGIN();
  RUN_TEST(test_smart_home_config);
  RUN_TEST(test_config);
  UNITY_END(); // stop unit testing
}

#endif //UNIT_TEST
