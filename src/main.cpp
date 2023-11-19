#include <Arduino.h>
#include <dht_sensor.h>
#include <access_point.h>
#include <esp.h>

#define DHT_PIN 2
#define CHECK_PERIOD 5e6 // in seconds

DhtSensor *dhtSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("Setup starting...");

  Serial.println("Setup starting...");

  dhtSensor = new DhtSensor(DHT_PIN);
  Serial.println("Setup complete.");

  EEPROM.begin(MAX_BUFF_SIZE);
  setupWifiMode();
  delay(5 * 1000);
}

void measureAndPrint()
{
  float humidity = dhtSensor->readHumidity();
  float temperature = dhtSensor->readTemp();

  if (isnan(temperature))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  sendData(humidity, "humidity");
  sendData(temperature, "temperature");
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
    Serial.println("sleeping");
    ESP.deepSleep(CHECK_PERIOD);
    state = MEASURING;
    break;
  case MEASURING:
    Serial.println("Measuring");
    measureAndPrint();
    state = SLEEP;
    break;
  }
  delay(1000);
}
