#include "BMP180.h"
#include <Adafruit_BMP085.h>
#include <ArduinoJson.h>

Adafruit_BMP085 bmp;

void BMP180::init()
{
    bmp.begin();
}

Adafruit_BMP085 BMP180::getSensor()
{
    return bmp;
}

void BMP180::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["name"] = "BMP180";
    data["temperature"] = bmp.readTemperature();
    data["pressure"] = bmp.readPressure();
    data["altitude"] = bmp.readAltitude();
    data["seaLevelPressure"] = bmp.readSealevelPressure();
}