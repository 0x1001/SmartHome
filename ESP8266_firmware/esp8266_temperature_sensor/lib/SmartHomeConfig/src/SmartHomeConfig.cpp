#include <SmartHomeConfig.hpp>

SmartHomeConfig::SmartHomeConfig() {

}

void SmartHomeConfig::begin(void) {
  SPIFFS.begin();
}

void SmartHomeConfig::set_wifi_ssid(char * wifi_ssid) {
  JsonObject *database = load();
  write(*database, WIFI_AP_SSID, wifi_ssid);
  save(*database);
}

void SmartHomeConfig::get_wifi_ssid(char * wifi_ssid) {
  JsonObject *database = load();
  read(*database, WIFI_AP_SSID, wifi_ssid);
}

JsonObject * SmartHomeConfig::load() {
  if (SPIFFS.exists(CONFIG_FILE)) {
    File config_file = SPIFFS.open(CONFIG_FILE, "r");
    String contents = config_file.readString();
    config_file.close();
    return &buffer.parseObject(contents);
  } else {
    return &buffer.createObject();
  }
}

void SmartHomeConfig::save(JsonObject &database) {
  File config_file = SPIFFS.open(CONFIG_FILE, "w");

  if (!config_file) {
    return;
  }

  database.printTo(config_file);
  config_file.close();
}

void SmartHomeConfig::read(JsonObject &database, const String param_name, char * param_value) {
  if (database.containsKey(param_name)) {
    strncpy(param_value, database[param_name], CONFIG_STRING_SIZE);
  } else {
    strncpy(param_value, "", CONFIG_STRING_SIZE);
  }
}

void SmartHomeConfig::write(JsonObject &database, const String param_name, char * param_value) {
  database[param_name] = param_value;
}
