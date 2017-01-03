#include <FS.h>
#include <ArduinoJson.h>

#ifndef SMARTHOMECONFIG_H
#define SMARTHOMECONFIG_H

#define CONFIG_STRING_SIZE 255

class SmartHomeConfig {
  public:
   SmartHomeConfig();
   void begin(void);
   void set_wifi_ssid(char *wifi_ssid);
   void get_wifi_ssid(char *wifi_ssid);

 private:
   const String CONFIG_FILE = "/configuration.json";
   const String WIFI_AP_SSID = "wifi_ap_ssid";
   DynamicJsonBuffer buffer;

 protected:
   void write(JsonObject &database, const String param_name, char *param_value);
   void read(JsonObject &database, const String param_name, char *param_value);
   void save(JsonObject &database);
   JsonObject *load(void);
};

#endif //SMARTHOMECONFIG_H
