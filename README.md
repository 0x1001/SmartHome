# smarthome
My smart home project

Temperature and humidity online sensor
--------------------------------------
Project is based on ESP8266 chip with DHT11/22 temperature and humidity sensor.
Every 5 min device connects to wifi and sends temperature and humidity readings to MQTT server.
Data is displaied on https://io.adafruit.com/0x1001/home
![Temperature and humidity sensor](/ESP8266_firmware/temperature_sensor/docs/schematic.png?raw=true "Temperature and humidity sensor")

Smart Plug
----------
Project is based on ESP8266 ESP-12E module and high power AC relay.
Smart plug subscribes to MQTT topic and waits for 'ON' and 'OFF' messages. Message 'ON' turns relay on, message 'OFF' turns relay off.
![Smart Plug](/ESP8266_firmware/plug/docs/schematic_plug.png?raw=true "Smart Plug")
