#include <Arduino.h>
#include <dht_sensor.h>
#include <access_point.h>
#include <esp.h>

#define DHT_PIN 2
#define CHECK_PERIOD 300e6 // in seconds

DhtSensor* dhtSensor;

void setup()
{
  Serial.begin(115200);
  DHT d(DHT_PIN, DHT11);
  DhtSensor sensor = DhtSensor(d);
  dhtSensor = &sensor;
  setupWifiMode();
  delay(1000);
}

void loop()
{
  switch (EspMode::espMode)
  {
  case Mode::ACCESS_POINT:
    handle();
    return;
  case Mode::HTTP_CLIENT:
    break;
  }

  static enum State {
    SLEEP,
    MEASURING
  } state = MEASURING;

  switch (state)
  {
  case SLEEP:
    ESP.deepSleep(CHECK_PERIOD);
    break;
  case MEASURING:
    float temp = dhtSensor->readTemp();
    sendData(temp, "temperature");
    float humid = dhtSensor->readTemp();
    sendData(humid, "humidity");
    state = SLEEP;
    break;
  }
  delay(1000);
}
