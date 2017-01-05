#include <publish.hpp>

Publish::Publish(const char *user_name, const char *user_password): _mqtt_client(&_wifi_client, "io.adafruit.com", 1883, user_name, user_password) {
  strncpy(_user_name, user_name, PUBLISH_STRING_SIZE);
}

int Publish::begin() {
  int status = 1;
  if (_mqtt_client.connected()) {
    return SUCCESS;
  }

  for (int retries = 3; retries > 0; retries--) {
    if (_mqtt_client.connect() == 0) {
      return SUCCESS;
    }

    _mqtt_client.disconnect();
    delay(5000);
  }

  return FAILURE;
}

int Publish::push_to_topic(const char *topic, float value) {
  Adafruit_MQTT_Publish publisher = Adafruit_MQTT_Publish(&_mqtt_client, topic);
  return publisher.publish(value);
}
