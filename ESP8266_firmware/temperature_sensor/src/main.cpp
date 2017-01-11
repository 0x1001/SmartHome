#include <Arduino.h>
#include <my_data.h>
#include <sensor.hpp>
#include <publish.hpp>
#include <network.hpp>

#ifndef UNIT_TEST

Sensor sensor;
Publish publish(MQTT_USER, MQTT_KEY);
Network network(WIFI_SSID, WIFI_PASSWORD);

void setup() {
  Serial.begin(74880);

  delay(1);
  Serial.println("");
  Serial.println("*** Temperature and humidity sensor ***");

  if (network.begin() == NETWORK_SUCCESS) {
    Serial.println("WiFi connected: " WIFI_SSID);
  } else {
    Serial.println("WiFi failed to connect to " WIFI_SSID);
    Serial.println("Going to deep sleep.");
    ESP.deepSleep(SLEEP_TIME, WAKE_RF_DEFAULT);
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  sensor.begin();
  publish.begin();
}

void loop() {
  Serial.println("Reading DHT sensor!");
  sensor.measure();
  float humidity = sensor.get_humidity();
  float temperature = sensor.get_temperature();
  float vbat = sensor.get_vbat();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    Serial.println("Going to deep sleep.");
    ESP.deepSleep(SLEEP_TIME, WAKE_RF_DEFAULT);
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C\t");
  Serial.print("Vbat: ");
  Serial.print(vbat);
  Serial.println(" V");

  Serial.print("Publishing temperature to " TEMPERATURE_TOPIC "... ");
  if (! publish.push_to_topic(TEMPERATURE_TOPIC, temperature)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.print("Publishing humidity to " HUMIDITY_TOPIC "... ");
  if (! publish.push_to_topic(HUMIDITY_TOPIC, humidity)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.print("Publishing vbat to " VBAT_TOPIC "... ");
  if (! publish.push_to_topic(VBAT_TOPIC, vbat)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.println("Going to deep sleep.");
  ESP.deepSleep(SLEEP_TIME, WAKE_RF_DEFAULT);
}

#endif //UNIT_TEST
