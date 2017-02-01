#include <mqtt.hpp>

MQTT::MQTT(const char *server_address, const int server_port, const char *user_name, const char *user_password):
  _mqtt_client(&_wifi_client, server_address, server_port, user_name, user_password) {
  for(int i=0; i < MQTT_MAX_SUBSCRIPTIONS; i++) {
      subscriptions[i] = 0;
  }
}

int MQTT::begin() {
  return _connect();
}

int MQTT::publish(const char *topic, float value) {
  if (_connect() != MQTT_SUCCESS) {
    return MQTT_FAILURE;
  }
  Adafruit_MQTT_Publish publisher = Adafruit_MQTT_Publish(&_mqtt_client, topic);
  return publisher.publish(value);
}

int MQTT::read_subscription(const char *topic, char *value) {
  Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&_mqtt_client, topic);
  Adafruit_MQTT_Subscribe *subscription;

  if (!_is_subscribed(topic)) {
    if (_add_subscription(topic) != MQTT_SUCCESS) {
      return MQTT_FAILURE;
    }

    _mqtt_client.subscribe(&onoffbutton);

    if (_reconnect() != MQTT_SUCCESS) {
      return MQTT_FAILURE;
    }
  }

  if (_connect() != MQTT_SUCCESS) {
    return MQTT_FAILURE;
  }

  while (subscription = _mqtt_client.readSubscription(5000)) {
    if (subscription == &onoffbutton) {
      strncpy(value, (char *)onoffbutton.lastread, MQTT_MAX_CHAR_NUM);
      return MQTT_SUCCESS;
    }
  }
  return MQTT_NO_MESSAGE;
}

int MQTT::_connect() {
  if (_mqtt_client.connected()) {
    return MQTT_SUCCESS;
  }

  for (int retries = 10; retries > 0; retries--) {
    if (_mqtt_client.connect() == 0) {
      return MQTT_SUCCESS;
    }
    _mqtt_client.disconnect();
    delay(1000);
  }

  return MQTT_FAILURE;
}

int MQTT::_disconnect() {
  if (_mqtt_client.connected()) {
    _mqtt_client.disconnect();
  }
}

int MQTT::_reconnect() {
  _disconnect();
  return _connect();
}

bool MQTT::_is_subscribed(const char * topic) {
  for(int i=0; i < MQTT_MAX_SUBSCRIPTIONS; i++) {
    if (topic == subscriptions[i]) {
      return true;
    }
  }
  return false;
}

int MQTT::_add_subscription(const char * topic) {
  for(int i=0; i < MQTT_MAX_SUBSCRIPTIONS; i++) {
    if (subscriptions[i] == 0) {
      subscriptions[i] = topic;
      return MQTT_SUCCESS;
    }
  }
  return MQTT_FAILURE;
}
