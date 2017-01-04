#include <config.hpp>

void Config::get_temperature_topic(char * topic) {
  JsonObject *database = load();
  read(*database, TEMPERATURE_TOPIC, topic);
}

void Config::set_temperature_topic(char * topic) {
  JsonObject *database = load();
  write(*database, TEMPERATURE_TOPIC, topic);
  save(*database);
}
