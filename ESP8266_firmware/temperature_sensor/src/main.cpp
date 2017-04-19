#include <Arduino.h>
#include <my_data.h>
#include <sensor.hpp>
#include <mqtt.hpp>
#include <network.hpp>
#include <vbat.hpp>

#ifndef UNIT_TEST

Sensor sensor;
MQTT mqtt(MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_KEY);
Network network(WIFI_SSID, WIFI_PASSWORD);
VBAT vbat;

void setup() {
  Serial.begin(74880);

  delay(1);
  Serial.println("");
  Serial.println("*** Temperature and humidity sensor ***");

  if (network.begin() == NETWORK_SUCCESS) {
    Serial.println("WiFi connected: " WIFI_SSID);
  } else {
    Serial.println("WiFi failed to connect to " WIFI_SSID);
    Serial.print("Going to deep sleep for ");
    Serial.print(SLEEP_TIME_NO_WIFI);
    Serial.println(" us.");
    ESP.deepSleep(SLEEP_TIME_NO_WIFI);
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  sensor.begin();
  mqtt.begin();
}

void loop() {
  Serial.println("Reading Vbat value!");
  float vbat_value = vbat.get_vbat();

  Serial.print("Vbat: ");
  Serial.print(vbat_value);
  Serial.println(" V");

  Serial.print("Publishing vbat to " VBAT_TOPIC "... ");
  if (! mqtt.publish(VBAT_TOPIC, vbat_value)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.println("Reading DHT sensor!");
  sensor.measure();
  float humidity = sensor.get_humidity();
  float temperature = sensor.get_temperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    Serial.print("Going to deep sleep for ");
    Serial.print(SLEEP_TIME);
    Serial.println(" us.");
    ESP.deepSleep(SLEEP_TIME);
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C\t");

  Serial.print("Publishing temperature to " TEMPERATURE_TOPIC "... ");
  if (! mqtt.publish(TEMPERATURE_TOPIC, temperature)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.print("Publishing humidity to " HUMIDITY_TOPIC "... ");
  if (! mqtt.publish(HUMIDITY_TOPIC, humidity)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.print("Going to deep sleep for ");
  Serial.print(SLEEP_TIME);
  Serial.println(" us.");
  ESP.deepSleep(SLEEP_TIME);
}

#endif //UNIT_TEST
