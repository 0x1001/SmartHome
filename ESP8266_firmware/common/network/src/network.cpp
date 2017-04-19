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
	connected = true;
    return NETWORK_SUCCESS;
  } else {
    connected = false;
    return NETWORK_FAILURE;
  }
}

bool Network::is_connected() {
	return connected;
}

IPAddress Network::get_local_ip() {
  return WiFi.localIP();
}
