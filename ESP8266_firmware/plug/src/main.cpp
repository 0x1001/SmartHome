#include <Arduino.h>
#include <network.hpp>
#include <my_data.h>
#include <mqtt.hpp>
#include <plug.hpp>
#include <reset_button.hpp>

#ifndef UNIT_TEST

Network network(WIFI_SSID, WIFI_PASSWORD);
MQTT mqtt(MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_KEY);
Plug plug(PLUG_PIN);
ResetButton button(BUTTON_PIN);

void interrupt_handler(){
  button.button_interrupt();
}

void stop() {
  Serial.println("Stopping program! Waiting for watchdog reset!");
  while(1);
}

void setup() {
  Serial.begin(74880);

  delay(1);
  Serial.println("");
  Serial.println("*** Smart Plug ***");

  if (network.begin() == NETWORK_SUCCESS) {
    Serial.println("WiFi connected: " WIFI_SSID);
  } else {
    Serial.println("WiFi failed to connect to " WIFI_SSID);
    stop();
  }

  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (mqtt.begin() == MQTT_SUCCESS){
    Serial.println("Connected to MQTT server as " MQTT_USER);
  }
  else {
    Serial.println("Faild to connect to MQTT server with user name " MQTT_USER);
    stop();
  }

  plug.begin();
  button.begin(&interrupt_handler);
}

void loop() {
  char last_state[MQTT_MAX_CHAR_NUM];
  int status = mqtt.read_subscription(ONOFFTOPIC, last_state, 100);

  if (status == MQTT_SUCCESS) {
    if (strcmp(last_state, ON_STATE) == 0) {
      Serial.println("Plug is turned ON.");
      plug.turn_on();
    }
    if (strcmp(last_state, OFF_STATE) == 0) {
      Serial.println("Plug is turned OFF.");
      plug.turn_off();
    }
  } else if (status == MQTT_NO_MESSAGE) {
    //Serial.print("Nothing to do. Last value: ");
    //Serial.println(last_state);
  } else {
    Serial.println("Error happend while reading subscription " ONOFFTOPIC);
    stop();
  }

  if (button.pressed()) {
    Serial.println("Button has been pressed.");
    if (strcmp(last_state, ON_STATE) == 0) {
      plug.turn_off();
      mqtt.publish(ONOFFTOPIC, OFF_STATE);
    } else {
      plug.turn_on();
      mqtt.publish(ONOFFTOPIC, ON_STATE);
    }
    button.reset();
  }
}

#endif //UNIT_TEST
