#include <Arduino.h>
#include <unity.h>
#include <FS.h>
#include <SmartHomeConfig.h>

#ifdef UNIT_TEST

void test_config(void) {
  char * wifi_ssid = new char[255];

  SmartHomeConfig config = SmartHomeConfig();
  config.begin();
  config.load();
  config.set_wifi_ssid("no_internet");
  config.save();

  config.load();
  config.get_wifi_ssid(wifi_ssid);

  TEST_ASSERT_EQUAL_STRING(wifi_ssid, "no_internet");
  TEST_ASSERT_TRUE(SPIFFS.exists("/configuration.json"));
}

void setup() {

}

void loop() {
  UNITY_BEGIN();
  RUN_TEST(test_config);
  UNITY_END(); // stop unit testing
}

#endif //UNIT_TEST
