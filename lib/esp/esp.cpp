#include <esp.h>

#define SSID_NAME 0

Mode EspMode::espMode = ACCESS_POINT;

void setupWifiMode()
{
    Serial.println();
    String storedSsid = readFromEeprom(SSID_NAME);
    String storedPass = readFromEeprom(storedSsid.length()+1+SSID_NAME);
    if (storedSsid == "" || storedPass == "")
    {
        EspMode::espMode = ACCESS_POINT;
        run();
        return;
    }
    EspMode::espMode = HTTP_CLIENT;
    runHandler(storedSsid.c_str(), storedPass.c_str());
}