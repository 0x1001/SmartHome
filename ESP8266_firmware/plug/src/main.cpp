#include <Arduino.h>
#include <network.hpp>
#include <my_data.h>
#include <mqtt.hpp>
#include <plug.hpp>

#ifndef UNIT_TEST

Network network(WIFI_SSID, WIFI_PASSWORD);
MQTT mqtt(MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_KEY);
Plug plug(PLUG_PINOUT);

void setup() {
  Serial.begin(74880);

  delay(1);
  Serial.println("");
  Serial.println("*** Smart Plug ***");

  if (network.begin() == NETWORK_SUCCESS) {
    Serial.println("WiFi connected: " WIFI_SSID);
  } else {
    Serial.println("WiFi failed to connect to " WIFI_SSID);
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (mqtt.begin() == MQTT_SUCCESS){
    Serial.println("Connected to MQTT server as " MQTT_USER);
  }
  else {
    Serial.println("Faild to connect to MQTT server with user name " MQTT_USER);
  }

  plug.begin();
}

void loop() {
  char last_read[MQTT_MAX_CHAR_NUM];
  int status;

  status = mqtt.read_subscription(ONOFFTOPIC, last_read);

  if (status == MQTT_SUCCESS) {
    if (strcmp(last_read, "ON") == 0) {
      Serial.println("Plug is turned ON.");
      plug.turn_on();
    }
    if (strcmp(last_read, "OFF") == 0) {
      Serial.println("Plug is turned OFF.");
      plug.turn_off();
    }
  } else if (status == MQTT_NO_MESSAGE) {
    Serial.print("Nothing to do. Last value: ");
    Serial.println(last_read);
  } else {
    Serial.println("Error happend while reading subscription " ONOFFTOPIC);
  }
}

#endif //UNIT_TEST
