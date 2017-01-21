//COMMON

#define MQTT_USER "0x1001"
#define MQTT_KEY "f53d016ddb384cafbb85942a30e43b2a"

#define WIFI_SSID "no_internet"
#define WIFI_PASSWORD "m0n1ka123"

#define SLEEP_TIME 5 * 60000000

// DEVICE SPECIFIC

#define DEVICE 1

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
