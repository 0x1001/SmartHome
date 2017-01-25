//COMMON

#define MQTT_USER "user_name"
#define MQTT_KEY "user_key"

#define WIFI_SSID "wifi_ssid"
#define WIFI_PASSWORD "password"

#define SLEEP_TIME 5 * 60000000

// DEVICE SPECIFIC

#define DEVICE 0

#if DEVICE == 0
  #define TEMPERATURE_TOPIC "0x1001/feeds/temperature1"
  #define HUMIDITY_TOPIC "0x1001/feeds/humidity1"
  #define VBAT_TOPIC "0x1001/feeds/vbat1"
#endif

#if DEVICE == 1
  #define TEMPERATURE_TOPIC "0x1001/feeds/temperature2"
  #define HUMIDITY_TOPIC "0x1001/feeds/humidity2"
  #define VBAT_TOPIC "0x1001/feeds/vbat2"
#endif