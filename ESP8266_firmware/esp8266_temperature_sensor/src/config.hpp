#include <SmartHomeConfig.hpp>

#ifndef CONFIG_H
#define CONFIG_H

class Config: public SmartHomeConfig {
public:
  void set_temperature_topic(char * topic);
  void get_temperature_topic(char * topic);

private:
  const String TEMPERATURE_TOPIC = "temperature_topic";

};

#endif //CONFIG_H
