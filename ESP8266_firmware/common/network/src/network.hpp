#include <ESP8266WiFi.h>

#ifndef NETWORK_H
#define NETWORK_H

#define NETWORK_RETRY 15
#define NETWORK_SUCCESS 1
#define NETWORK_FAILURE 0

class Network {
  public:
    Network(const char *ssid, const char *password);
    int begin();
    IPAddress get_local_ip();

  private:
    int connect();
    const char *_ssid;
    const char *_password;
};

#endif //NETWORK_H
