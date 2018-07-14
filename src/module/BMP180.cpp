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

#include <Adafruit_BMP085.h>
#include <ArduinoJson.h>
#include "BMP180.h"

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
    data["n"] = "BMP180";
    data["t"] = BMP180::temperature;
    data["p"] = BMP180::pressure;
}