#include <SmartHomeConfig.h>

SmartHomeConfig::SmartHomeConfig() {

}

void SmartHomeConfig::begin(void) {
  SPIFFS.begin();
}

void SmartHomeConfig::set_wifi_ssid(char * wifi_ssid) {
  strncpy(this->wifi_ssid, wifi_ssid, 255);
}

void SmartHomeConfig::get_wifi_ssid(char * wifi_ssid) {
  strncpy(wifi_ssid, this->wifi_ssid, 255);
}

void SmartHomeConfig::load() {
  DynamicJsonBuffer buffer;

  if (SPIFFS.exists(CONFIG_FILE)) {
    File config_file = SPIFFS.open(CONFIG_FILE, "r");
    String contents = config_file.readString();
    config_file.close();
    JsonObject& database = buffer.parseObject(contents);

    read(database, WIFI_AP_SSID, wifi_ssid);
  }
}

void SmartHomeConfig::save() {
  DynamicJsonBuffer buffer;

  JsonObject& database = buffer.createObject();

  write(database, WIFI_AP_SSID, wifi_ssid);

  File config_file = SPIFFS.open(CONFIG_FILE, "w");

  if (!config_file) {
    return;
  }

  database.printTo(config_file);
  config_file.close();
}

void SmartHomeConfig::read(JsonObject& database, const String param_name, char * param_value) {
  if (database.containsKey(param_name)) {
    strncpy(param_value, database[param_name], 255);
  } else {
    strncpy(param_value, "", 255);
  }
}

void SmartHomeConfig::write(JsonObject& database, const String param_name, char * param_value) {
  database[param_name] = param_value;
}
