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
#include <SoftwareSerial.h>
#include <time.h>
#include "DataManager.h"
#include "../module/BH1750FVI.h"
#include "../module/BMP180.h"
#include "../module/DHT11.h"
#include "../module/GP2Y10.h"
#include "../module/LcdHelper.h"
#include "../util/Configuration.h"
#include "../config.h"

#define CMD_WIFI_MODULE_INFO 0
#define CMD_REINIT_DISPLAY 1
#define CMD_UPDATE_TIME 2
#define CMD_GET_INFO 3
#define CMD_SET_WIFI_INFO 4

#define RESP_TICK_INFO 0
#define RESP_INFO 1

unsigned long DataManager::startTime = 0;
String DataManager::wifiModuleFirmwareInfo = "UKN WM FW";

#if SOFTWARE_SERIAL
SoftwareSerial wifi(SOFTWARE_SERIAL_RX, SOFTWARE_SERIAL_TX);
#else
HardwareSerial &wifi = Serial1;
#endif

#if DEBUG
HardwareSerial &ser = Serial;
#else
#if SOFTWARE_SERIAL
SoftwareSerial &ser = wifi;
#else
HardwareSerial &ser = Serial1;
#endif
#endif

void DataManager::init()
{
    pinMode(13, OUTPUT); //LED PIN

    digitalWrite(13, HIGH);

    Serial.begin(SERIAL_BAUDRATE);
    Serial.setTimeout(SERIAL_READ_TIMEOUT);
    wifi.begin(WIFI_MODULE_BAUDRATE);
    wifi.setTimeout(SERIAL_READ_TIMEOUT);

    BMP180::init(); //init I2C
    BH1750FVI::init();
    DHT11::init();
    GP2Y10::init();
    LcdHelper::init();

    Configuration::init();

    LcdHelper::load();

    digitalWrite(13, LOW);
}

boolean DataManager::update()
{
    BH1750FVI::readSensor();
    BMP180::readSensor();
    DHT11::readSensor();
    GP2Y10::readSensor();

    DynamicJsonBuffer jsonBuffer(256);
    JsonObject &root = jsonBuffer.createObject();
    root["r"] = RESP_TICK_INFO;

    JsonArray &sensorData = root.createNestedArray("s");
    BH1750FVI::addJsonData(sensorData);
    BMP180::addJsonData(sensorData);
    DHT11::addJsonData(sensorData);
    GP2Y10::addJsonData(sensorData);

    root.printTo(ser);
    ser.println();

    jsonBuffer.clear();
    char json[64];
    ser.readBytes(json, sizeof(json));
    JsonObject &command = jsonBuffer.parseObject(json);
    if (!command.success())
    {
        return false;
    }
    /*
    commands:
        0: WiFi Module Information
            {"c":0,"n":"Chronos","v":"0.1.0"}
            n: Firmware Name
            v: Firmware Version
        1: Re-init Display
            {"c":1}
        2: Update Time
            {"c":2,"t":"1531615194"}
            t: Current Unix Timestamp
        3: Get Information (Firmware info, WiFi info)
            {"c":3}
        4: Set WiFi Info
            {"c":4,"s":"SSIDofWiFi","p":"password"}
            s: SSID
            p: Password
    */
    if (command.containsKey("c")) //process command and send response(optional)
    {
        digitalWrite(13, HIGH);
        int cmd = command["c"];
        switch (cmd)
        {
        case CMD_WIFI_MODULE_INFO:
            wifiModuleFirmwareInfo = String(command["n"].asString()) + " " + String(command["v"].asString());
            LcdHelper::printHeader();
            break;
        case CMD_REINIT_DISPLAY:
            LcdHelper::load();
            break;
        case CMD_UPDATE_TIME:
            startTime = command["t"].as<long>() - millis() / 1000;
            break;
        case CMD_GET_INFO:
        {
            jsonBuffer.clear();
            JsonObject &resp = jsonBuffer.createObject();
            resp["r"] = RESP_INFO;
            resp["n"] = NAME;
            resp["v"] = VER;
            resp["t"] = millis();
            resp["s"] = startTime;

            resp["d"] = Configuration::WIFI_SSID;
            resp["p"] = Configuration::WIFI_PASS;

            resp.printTo(ser);
            ser.println();
        }
        break;
        case CMD_SET_WIFI_INFO:
            Configuration::setSsid(command["s"]);
            Configuration::setPass(command["p"]);
            LcdHelper::printHeader();
            break;
        }
        digitalWrite(13, LOW);
        return true;
    }
    if (command.containsKey("r")) //process response
    {
        int resp = command["r"];
        switch (resp)
        {
        }
        return true;
    }
    return false;
}

String DataManager::getFormattedTime()
{
#if MINIMIZE
    return F("Not Supported");
#else
    char time[30];
    time_t t = DataManager::startTime + millis() / 1000 - UNIX_OFFSET;
    set_zone(8 * ONE_HOUR);
    strftime(time, 30, "%Y-%m-%d %H:%M:%S", localtime(&t));
    return String(time);
#endif
}