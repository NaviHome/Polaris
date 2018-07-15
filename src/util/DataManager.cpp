/*
 * Copyright (C) 2018 iTX Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <ArduinoJson.h>
#include <time.h>
#include "DataManager.h"
#include "../module/BMP180.h"
#include "../module/DHT11.h"
#include "../module/GP2Y10.h"
#include "../module/LcdHelper.h"
#include "../config.h"

#define CMD_WIFI_MODULE_INFO 0
#define CMD_REINIT_DISPLAY 1
#define CMD_UPDATE_TIME 2

unsigned long DataManager::startTime = 0;
String DataManager::wifiModuleFirmwareInfo = "UKN WM FW";

void DataManager::init()
{
    Serial.begin(SERIAL_BAUDRATE);
    Serial.setTimeout(SERIAL_READ_TIMEOUT);
    Serial1.begin(WIFI_MODULE_BAUDRATE);
    Serial1.setTimeout(SERIAL_READ_TIMEOUT);
    LcdHelper::init();
    DHT11::init();
    BMP180::init();
    GP2Y10::init();
}

void DataManager::update()
{
    BMP180::readSensor();
    DHT11::readSensor();
    GP2Y10::readSensor();

    DynamicJsonBuffer jsonBuffer(200);
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
    Serial1.println(buffer);

    jsonBuffer.clear();
#if DEBUG
    JsonObject &command = jsonBuffer.parseObject(Serial);
#else
    JsonObject &command = jsonBuffer.parseObject(wifi);
#endif
    /*
    commands:
        0: WiFi Module Information
            {"c":0,"fn":"Chronos","fv":"0.1.0"}
            fn: Firmware Name
            fv: Firmware Version
        1: Re-init Display
            {"c":1}
        2: Update Time
            {"c":2,"t":"1531615194"}
            t: Current Unix Timestamp
    */
    if (command.containsKey("c"))
    {
        int cmd = command["c"];
        switch (cmd)
        {
        case CMD_WIFI_MODULE_INFO:
            wifiModuleFirmwareInfo = String(command["fn"].asString()) + " " + String(command["fv"].asString());
            LcdHelper::printHeader();
            break;
        case CMD_REINIT_DISPLAY:
            LcdHelper::setDefalutValue(true);
            break;
        case CMD_UPDATE_TIME:
            startTime = command["t"].as<long>() - millis() / 1000;
            break;
        }
    }
}

String DataManager::getFormattedTime()
{
    char time[30];
    time_t t = DataManager::startTime + millis() / 1000 - UNIX_OFFSET;
    set_zone(8 * ONE_HOUR);
    strftime(time, 30, "%Y-%m-%d %H:%M:%S", localtime(&t));
    return String(time);
}