#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "DataManager.h"
#include "../module/BMP180.h"
#include "../module/DHT11.h"
#include "../module/GP2Y10.h"
#include "../module/LcdHelper.h"
#include "../config.h"

#define ESP_RX 5
#define ESP_TX 6

#define ESP_BAUDRATE 115200

SoftwareSerial esp(ESP_RX, ESP_TX); //RX TX

void DataManager::init()
{
    esp.begin(ESP_BAUDRATE);
    LcdHelper::init();
    BMP180::init();
    GP2Y10::init();
}

void DataManager::update()
{
    BMP180::readSensor();
    DHT11::readSensor();
    GP2Y10::readSensor();

    DynamicJsonBuffer jsonBuffer;
    JsonObject &root = jsonBuffer.createObject();
    root["fw_n"] = NAME;
    root["fw_v"] = VER;
    root["uptime"] = millis();

    JsonArray &sensorData = root.createNestedArray("sensors");
    BMP180::addJsonData(sensorData);
    DHT11::addJsonData(sensorData);
    GP2Y10::addJsonData(sensorData);

    root.printTo(Serial);
    Serial.println();

    root.printTo(esp);
    esp.println();
}