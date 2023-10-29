#include <Arduino.h>
#include <DHT.h>

class DhtSensor
{
    DHT *dhtSensor;
    int pin;

protected:
    static enum SensorMode {
        LOW_MODE,
        HIGH_MODE,
    } powerMode;

public:
    DhtSensor(DHT sensor);
    int mode();
    void powerLow();
    void powerHigh();
    float readTemp();
    float readHumidity();
};

DhtSensor::DhtSensor(DHT sensor)
{
    this->dhtSensor = &sensor;
    this->dhtSensor->begin();
    this->pin = pin;
}

int DhtSensor::mode()
{
    return powerMode;
}

void DhtSensor::powerLow()
{
    digitalWrite(this->pin, LOW);
    pinMode(this->pin, INPUT);
}

void DhtSensor::powerHigh()
{
    digitalWrite(this->pin, HIGH);
    // this->dhtSensor.begin();
    delay(1000);
}

float DhtSensor::readHumidity()
{
    return 0;
    // return this->dhtSensor.readHumidity();
}

float DhtSensor::readTemp()
{
    return 0;
    // return this->dhtSensor.readTemperature();
}