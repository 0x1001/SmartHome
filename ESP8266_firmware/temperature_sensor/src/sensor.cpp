#include <sensor.hpp>

Sensor::Sensor(): _sensor(SENSOR_COMMUNICATION_PIN, DHT22) {
}

void Sensor::begin() {
  _sensor.begin();
}

void Sensor::measure() {
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  digitalWrite(SENSOR_POWER_PIN, HIGH);
  delay(2000);

  _temperature = _sensor.readTemperature();
  _humidity = _sensor.readHumidity();

  digitalWrite(SENSOR_POWER_PIN, LOW);
  pinMode(SENSOR_POWER_PIN, INPUT);
}

float Sensor::get_temperature() {
  return _temperature;
}

float Sensor::get_humidity() {
  return _humidity;
}
