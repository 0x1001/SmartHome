#include <FS.h>
#include <ArduinoJson.h>

#ifndef SMARTHOMECONFIG_H
#define SMARTHOMECONFIG_H

class SmartHomeConfig {
  public:
   SmartHomeConfig();
   void begin(void);
   void save(void);
   void load(void);
   void set_wifi_ssid(char * wifi_ssid);
   void get_wifi_ssid(char * wifi_ssid);

 private:
   const String CONFIG_FILE = "/configuration.json";
   const String WIFI_AP_SSID = "wifi_ap_ssid";

   char * wifi_ssid = new char[255];

   void read(JsonObject& database, const String param_name, char * param_value);
   void write(JsonObject& database, const String param_name, char * param_value);
};

#endif //SMARTHOMECONFIG_H
