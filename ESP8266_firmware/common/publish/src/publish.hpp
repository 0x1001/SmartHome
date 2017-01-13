#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#ifndef PUBLISH_H
#define PUBLISH_H

#define PUBLISH_STRING_SIZE 255
#define PUBLISH_SUCCESS 1
#define PUBLISH_FAILURE 0

class Publish {
  public:
    Publish(const char *user_name, const char *user_password);
    int begin();
    int push_to_topic(const char *topic, float value);

  private:
    char _user_name[PUBLISH_STRING_SIZE];

    WiFiClient _wifi_client;
    Adafruit_MQTT_Client _mqtt_client;

};

#endif
