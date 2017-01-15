#include <Arduino.h>
#include <network.hpp>
#include <my_data.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#ifndef UNIT_TEST

Network network(WIFI_SSID, WIFI_PASSWORD);

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, "io.adafruit.com", 1883, MQTT_USER, MQTT_KEY);


/****************************** Feeds ***************************************/

// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, MQTT_USER "/feeds/plug1");

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

  mqtt.subscribe(&onoffbutton);
  pinMode(4, OUTPUT);
}

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

void loop() {
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    // Check if its the onoff button feed
    if (subscription == &onoffbutton) {
      Serial.print(F("On-Off button: "));
      Serial.println((char *)onoffbutton.lastread);

      if (strcmp((char *)onoffbutton.lastread, "ON") == 0) {
        digitalWrite(4, HIGH);
      }
      if (strcmp((char *)onoffbutton.lastread, "OFF") == 0) {
        digitalWrite(4, LOW);
      }
    }
  }

  // ping the server to keep the mqtt connection alive
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }

}

#endif //UNIT_TEST
