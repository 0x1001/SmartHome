#include <network.hpp>

Network::Network(const char *ssid, const char *password) {
  _ssid = ssid;
  _password = password;
}

int Network::begin() {
  return connect();
}

int Network::connect() {
  int WiFiCounter = 0;

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(_ssid, _password);

  while (WiFi.status() != WL_CONNECTED && WiFiCounter < NETWORK_RETRY) {
    delay(1000);
    WiFiCounter++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    return NETWORK_SUCCESS;
  } else {
    return NETWORK_FAILURE;
  }
}

IPAddress Network::get_local_ip() {
  return WiFi.localIP();
}
