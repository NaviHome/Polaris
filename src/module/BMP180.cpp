#include "BMP180.h"
#include <Adafruit_BMP085.h>
#include <ArduinoJson.h>

Adafruit_BMP085 bmp;

float BMP180::temperature = 0;
long BMP180::pressure = 0;

void BMP180::init()
{
    bmp.begin();
}

void BMP180::readSensor()
{
    BMP180::temperature = bmp.readTemperature();
    BMP180::pressure = bmp.readPressure();
}

float BMP180::getTemperature()
{
    return BMP180::temperature;
}

long BMP180::getPressure()
{
    return BMP180::pressure;
}

void BMP180::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["name"] = "BMP180";
    data["temp"] = BMP180::temperature;
    data["pres"] = BMP180::pressure;
}