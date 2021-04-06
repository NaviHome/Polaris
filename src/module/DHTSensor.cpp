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
#include <DHT.h>
#include "DHTSensor.h"
#include "../config.h"

byte DHTSensor::temperature = 0;
byte DHTSensor::humidity = 0;

DHT dht11(DHT11_PIN, DHT11);

void DHTSensor::init()
{
    dht11.begin();
}

void DHTSensor::readSensor()
{
    DHTSensor::temperature = dht11.readTemperature();
    DHTSensor::humidity = dht11.readHumidity();
}

byte DHTSensor::getTemperature()
{
    return DHTSensor::temperature;
}

byte DHTSensor::getHumidity()
{
    return DHTSensor::humidity;
}

void DHTSensor::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["n"] = "DHT11";
    data["t"] = DHTSensor::temperature;
    data["h"] = DHTSensor::humidity;
}