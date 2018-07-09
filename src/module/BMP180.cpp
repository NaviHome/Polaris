#include "BMP180.h"
#include <Adafruit_BMP085.h>
#include <ArduinoJson.h>

Adafruit_BMP085 bmp;

void BMP180::init(){
    bmp.begin();
}

Adafruit_BMP085 BMP180::getBmp(){
    return bmp;
}

String BMP180::getJsonData(){
    DynamicJsonBuffer JsonBuffer;
    JsonObject &data = JsonBuffer.createObject();
    data["name"] = "BMP180";
    data["temperature"] = bmp.readTemperature();
    data["pressure"] = bmp.readPressure();
    data["altitude"] = bmp.readAltitude();
    data["seaLevelPressure"] = bmp.readSealevelPressure();

    String result;
    data.printTo(result);
    return result;
}