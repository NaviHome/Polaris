#include <ArduinoJson.h>
#include "Util.h"
#include "module/BMP180.h"
#include "module/DHT11.h"

void Util::encodeAndSendJsonData(String name, String ver)
{
    DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["fw_name"] = name;
    root["fw_ver"] = ver;
    root["uptime"] = millis();

    JsonArray &sensorData = root.createNestedArray("sensors");
    BMP180::addJsonData(sensorData);
    DHT11::addJsonData(sensorData);

    root.printTo(Serial);
    Serial.println();
}
