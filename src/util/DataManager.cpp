#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include "DataManager.h"
#include "../module/BMP180.h"
#include "../module/DHT11.h"
#include "../module/GP2Y10.h"
#include "../module/LcdHelper.h"
#include "../config.h"

#define CMD_WIFI_MODULE_INFO 0
#define CMD_REINIT_DISPLAY 1

#define ESP_RX 5
#define ESP_TX 6

#define ESP_BAUDRATE 115200

unsigned long DataManager::startTime = 0;
String DataManager::wifiModuleFirmwareInfo = "UKN WM FW";

SoftwareSerial esp(ESP_RX, ESP_TX); //RX TX

void DataManager::init()
{
    Serial.begin(115200);
    Serial.setTimeout(200);
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

    DynamicJsonBuffer jsonBuffer(200); //no more than 200
    JsonObject &root = jsonBuffer.createObject();
    root["fn"] = NAME;
    root["fv"] = VER;
    root["ut"] = millis();

    JsonArray &sensorData = root.createNestedArray("s");
    BMP180::addJsonData(sensorData);
    DHT11::addJsonData(sensorData);
    GP2Y10::addJsonData(sensorData);

    char buffer[200];
    root.printTo(buffer);
    Serial.println(buffer);
    esp.println(buffer);
    //delete[] buffer;

    jsonBuffer.clear();
    JsonObject &command = jsonBuffer.parseObject(Serial);
    /*
    command types:
        0: WiFi Module Information
            {"c":0,"fn":"Chronos","fw":"0.1.0","t":"1531558467"}
        1: Re-init display
            {"c":1}
    */
    if (command.containsKey("c"))
    {
        int cmd = command["c"];
        switch (cmd)
        {
            case CMD_WIFI_MODULE_INFO:
                startTime = command["t"];
                wifiModuleFirmwareInfo = String(command["fn"].asString()) + " " + String(command["fw"].asString());
                LcdHelper::printHeader();
                break;
            case CMD_REINIT_DISPLAY:
                LcdHelper::setDefalutValue(true);
                break;
        }
    }
}

unsigned long DataManager::getTimeNow(){
    return startTime + millis() / 1000;
}