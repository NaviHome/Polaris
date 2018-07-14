#include <Arduino.h>
#include <ArduinoJson.h>
#include <SimpleDHT.h>
#include "DHT11.h"
#include "../config.h"

byte DHT11::temperature = 0;
byte DHT11::humidity = 0;

SimpleDHT11 dht11;

bool DHT11::readSensor()
{
    int err = SimpleDHTErrSuccess;
    if ((err = dht11.read(DHT11_PIN, &DHT11::temperature, &DHT11::humidity, NULL)) != SimpleDHTErrSuccess)
    {
        return false;
    }
    return true;
}

byte DHT11::getTemperature()
{
    return DHT11::temperature;
}

byte DHT11::getHumidity()
{
    return DHT11::humidity;
}

void DHT11::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["n"] = "DHT11";
    data["t"] = DHT11::temperature;
    data["h"] = DHT11::humidity;
}