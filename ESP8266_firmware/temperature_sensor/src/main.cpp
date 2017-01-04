#include <Arduino.h>
#include <FS.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "my_data.h"
#include "config.hpp"
#include "sensor.hpp"

#ifndef UNIT_TEST

Config config;
Sensor sensor;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, "io.adafruit.com", 1883, MQTT_USER, MQTT_KEY);
Adafruit_MQTT_Publish temperature_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_USER "/feeds/temperature2");
Adafruit_MQTT_Publish humidity_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_USER "/feeds/humidity2");
Adafruit_MQTT_Publish vbat_pub = Adafruit_MQTT_Publish(&mqtt, MQTT_USER "/feeds/vbat2");

void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}

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

  SPIFFS.begin();
}

void loop() {
  MQTT_connect();

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

  Serial.print("Publishing temperature to /feeds/temperature... ");
  if (! temperature_pub.publish(t)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.print("Publishing humidity to /feeds/humidity... ");
  if (! humidity_pub.publish(h)) {
    Serial.println("Failed");
  } else {
    Serial.println("OK!");
  }

  Serial.println("Publishing vbat to /feeds/vbat... OK!");
  vbat_pub.publish(vbat);

  Serial.println("Going to deep sleep");
  ESP.deepSleep(5 * 60000000, WAKE_RF_DEFAULT);
}

#endif //UNIT_TEST
