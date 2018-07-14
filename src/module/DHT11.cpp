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