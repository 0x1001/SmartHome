#include <sensor.hpp>

ADC_MODE(ADC_VCC);

Sensor::Sensor(): _sensor(SENSOR_COMMUNICATION_PIN, DHT11) {
}

void Sensor::begin() {
  _sensor.begin();
}

void Sensor::measure() {
  pinMode(SENSOR_POWER_PIN, OUTPUT);
  digitalWrite(SENSOR_POWER_PIN, HIGH);
  delay(2000);

  _temperature = _sensor.readHumidity();
  _humidity = _sensor.readTemperature();
  _vbat = ESP.getVcc()/1024.0;

  digitalWrite(SENSOR_POWER_PIN, LOW);
  pinMode(SENSOR_POWER_PIN, INPUT);
}

float Sensor::get_temperature() {
  return _temperature;
}

float Sensor::get_humidity() {
  return _humidity;
}

float Sensor::get_vbat() {
  return _vbat;
}
