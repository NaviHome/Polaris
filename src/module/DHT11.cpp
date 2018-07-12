#include <Arduino.h>
#include <SimpleDHT.h>
#include "DHT11.h"

const int DHT11_PIN = 4;

byte temperature = 0;
byte humidity = 0;

SimpleDHT11 dht11;

bool DHT11::readSensor()
{
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(DHT11_PIN, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess)
    {
        return false;
    }
    return true;
}

byte DHT11::getTemperature()
{
    return temperature;
}

byte DHT11::getHumidity()
{
    return humidity;
}

void DHT11::writeDataToStream(BinaryStream &stream)
{
    stream.putByte(temperature);
    stream.putByte(humidity);
}