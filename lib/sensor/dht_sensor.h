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
    DhtSensor(int pin);
    ~DhtSensor();
    int mode();
    void powerLow();
    void powerHigh();
    float readTemp();
    float readHumidity();
};

DhtSensor::~DhtSensor()
{
    delete this->dhtSensor;
}

DhtSensor::DhtSensor(int pin)
{
    this->dhtSensor = new DHT(pin, DHT11);
    this->pin = pin;
    this->powerHigh();
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
    delay(4000);
    this->dhtSensor->begin();
}

float DhtSensor::readHumidity()
{
    // return 0;
    float humid = this->dhtSensor->readHumidity();
    Serial.print("Humidity: ");
    Serial.print(humid);
    Serial.println(" %");
    return humid;
}

float DhtSensor::readTemp()
{
    // return 0;
    float temp = this->dhtSensor->readTemperature();
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.println(" °C");
    return temp;
}