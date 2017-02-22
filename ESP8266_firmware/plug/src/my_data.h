//COMMON
#define MQTT_SERVER "192.168.0.4"
#define MQTT_PORT 1883
#define MQTT_USER "user"
#define MQTT_KEY "pass"

#define WIFI_SSID "ssid"
#define WIFI_PASSWORD "pass"

#define SLEEP_TIME 5 * 60000000

#define PLUG_PIN 4
#define BUTTON_PIN 5
#define ON_STATE "ON"
#define OFF_STATE "OFF"

// DEVICE SPECIFIC
#define DEVICE 1

#if DEVICE == 0
  #define ONOFFTOPIC "home/plug1"
#endif

#if DEVICE == 1
  #define ONOFFTOPIC "home/plug2"
#endif
