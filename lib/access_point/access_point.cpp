#include <access_point.h>
#include <eprom.h>
#include <json.h>

#define POINT_ID "123456789"

ESP8266WebServer server(80);

void handleWifiSettings()
{
    StaticJsonDocument<MAX_BUFF_SIZE * 3> doc;
    DeserializationError error = deserializeJson(doc, server.arg("plain"));
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }
    const char *ssid = doc["ssid"];
    int result = write2Eeprom(0, ssid);
    if (result)
    {
        const char *pass = doc["pass"];
        result = write2Eeprom(result, pass);
        Serial.println("saved new ssid and pass");
    }
    const int capacity = JSON_OBJECT_SIZE(1);
    StaticJsonDocument<capacity> respDoc;
    if (result)
    {
        respDoc["status"] = "saved";
    }
    else
    {
        respDoc["status"] = "error";
    }
    int len = measureJson(respDoc);
    char output[len];
    serializeJson(respDoc, output, sizeof(output));
    server.send(200, "application/json", output);
}

void handleInfoPath()
{
    const int capacity = JSON_OBJECT_SIZE(2);
    StaticJsonDocument<capacity> doc;
    doc["key"] = POINT_ID;
    int len = measureJson(doc);
    char output[len];
    serializeJson(doc, output, sizeof(output));
    server.send(200, "application/json", output);
}

void run()
{
    Serial.println("Running in access point mode(AP)...");
    WiFi.softAP("sensor_access_point", NULL);
    IPAddress myIP = WiFi.softAPIP();
    Serial.println("AP IP address: ");
    Serial.println(myIP);
    server.on("/", handleInfoPath);
    server.on("/set", handleWifiSettings);
    server.begin();
    Serial.println("Server listening");
}

void handle()
{
    server.handleClient();
}
