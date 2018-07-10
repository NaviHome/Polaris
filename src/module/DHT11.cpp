#include <Arduino.h>
#include <ArduinoJson.h>
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

void DHT11::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["name"] = "DHT11";
    data["temperature"] = temperature;
    data["humidity"] = humidity;
}