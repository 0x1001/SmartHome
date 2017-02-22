#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

#ifndef MQTT_H
#define MQTT_H

#define MQTT_SUCCESS 1
#define MQTT_FAILURE 0
#define MQTT_NO_MESSAGE 2

#define MQTT_MAX_CHAR_NUM SUBSCRIPTIONDATALEN
#define MQTT_MAX_SUBSCRIPTIONS MAXSUBSCRIPTIONS

class MQTT {
  public:
    MQTT(const char *server_address, const int server_port, const char *user_name, const char *user_password);
    int begin();
    int publish(const char *topic, float value);
    int publish(const char *topic, const char *value);
    int read_subscription(const char *topic, char *value, int timeout = 5000);
    void set_retry(int count);

  private:
    WiFiClient _wifi_client;
    Adafruit_MQTT_Client _mqtt_client;
    int retry = 1;
    const char *subscriptions[MQTT_MAX_SUBSCRIPTIONS];
    int _connect();
    int _disconnect();
    int _reconnect();
    bool _is_subscribed(const char *topic);
    int _add_subscription(const char *topic);
};

#endif //MQTT_H
