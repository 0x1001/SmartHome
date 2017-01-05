#include <Arduino.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <my_data.h>
#include <config.hpp>
#include <sensor.hpp>
#include <publish.hpp>

#ifndef UNIT_TEST

Config config;
Sensor sensor;
Publish publish(MQTT_USER, MQTT_KEY);

void connect_wifi(const char* ssid, const char* password) {
  int WiFiCounter = 0;
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED && WiFiCounter < 30) {
    delay(1000);
    WiFiCounter++;
    Serial.println(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(74880);
  connect_wifi(WIFI_SSID, WIFI_PASSWORD);
  sensor.begin();
  publish.begin();
}

void loop() {
  Serial.println("Reading DHT sensor!");

  sensor.measure();
  float h = sensor.get_humidity();
  float t = sensor.get_temperature();
  float vbat = sensor.get_vbat()/1024.0;

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C\t");
  Serial.print("Vbat: ");
  Serial.print(vbat);
  Serial.println(" V");

  Serial.print("Publishing temperature to 0x1001/feeds/temperature... ");
  if (! publish.push_to_topic("0x1001/feeds/temperature", t)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.print("Publishing humidity to /feeds/humidity... ");
  if (! publish.push_to_topic("0x1001/feeds/humidity", h)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.print("Publishing vbat to 0x1001feeds/vbat... ");
  if (! publish.push_to_topic("0x1001/feeds/vbat", vbat)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.println("Going to deep sleep");
  ESP.deepSleep(5 * 60000000, WAKE_RF_DEFAULT);
}

#endif //UNIT_TEST
