#include <Arduino.h>
#include <eprom.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <json.h>

void runHandler(const char *ssid, const char *password);

void sendData(float value, String valueType);