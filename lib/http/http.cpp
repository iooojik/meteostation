#include <http.h>
#define SOURCE "E4A4DCBD-F50F-4BDD-B4D9-3F7A4A5A86F3"

ESP8266WiFiMulti WiFiMulti;

void (*resetFunc)(void) = 0;

bool connect(const char *ssid, const char *password){
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);
  delay(1000);
  if ((WiFiMulti.run() == WL_CONNECTED))
  {
    Serial.println("Connected");
    return true;
  }
  else
  {
    Serial.println("Unable to connect");
    return false;
  }
}

void runHandler(const char *ssid, const char *password)
{
  Serial.println();
  Serial.print("Running in wifi client mode...");
  for (size_t i = 0; i < 5; i++)
  {
    bool connected = connect(ssid, password);
    if (connected){
      return;
    }
  }
  resetFunc();
}

void sendData(float value, String valueType)
{
  Serial.println(value);
  WiFiClient client;
  HTTPClient http;

  Serial.print("[HTTP] begin...\n");
  if (http.begin(client, "http://api.brightbyte.ru:444/api/set/humidity"))
  {
    http.addHeader("Content-Type", "application/json");
    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header
    // const int capacity = JSON_OBJECT_SIZE(200);
    StaticJsonDocument<128> doc;
    doc["valueType"] = valueType;
    doc["value"] = value;
    doc["sourceId"] = SOURCE;
    int len1 = measureJson(doc);
    // Serial.println(len1);
    char output[len1];
    serializeJson(doc, output, sizeof(output));
    Serial.println(String(output));
    int httpCode = http.POST(String(output));
    // httpCode will be negative on error
    if (httpCode > 0)
    {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)
      {
        String payload = http.getString();
        Serial.println(payload);
      }
    }
    else
    {
      Serial.printf("[HTTP] POST... failed, error: %s %d\n", http.errorToString(httpCode).c_str(), httpCode);
    }

    http.end();
  }
}
