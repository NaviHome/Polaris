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
#include "GP2Y10.h"
#include "../config.h"

#define SAMPLEING_TIME 280
#define DELTA_TIME 40
#define SLEEP_TIME 9680

int GP2Y10::voMeasured;
float GP2Y10::calcVoltage;
float GP2Y10::dustDensity;
float GP2Y10::dustDensityAverage;
float GP2Y10::dustDensityHistory[DENSITY_HISTROY_COUNT];

void GP2Y10::init()
{
    pinMode(LED_PIN, OUTPUT);
    for (int i = 0; i < DENSITY_HISTROY_COUNT; i++)
    {
        GP2Y10::dustDensityHistory[i] = 0;
    }
}

float GP2Y10::getDustDensityNow()
{
    digitalWrite(LED_PIN, LOW); // power on the LED
    delayMicroseconds(SAMPLEING_TIME);

    GP2Y10::voMeasured = analogRead(VOUT_PIN); // read the dust value

    delayMicroseconds(DELTA_TIME);
    digitalWrite(LED_PIN, HIGH); // turn the LED off
    delayMicroseconds(SLEEP_TIME);

    // 0 - 5V mapped to 0 - 1023 integer values
    // recover voltage
    GP2Y10::calcVoltage = (float)GP2Y10::voMeasured * (5.0 / 1024.0);

    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012
    if (GP2Y10::calcVoltage >= 0.6)
    {
        GP2Y10::dustDensity = 0.17 * GP2Y10::calcVoltage - 0.1;
    }
    else
    {
        GP2Y10::dustDensity = 0;
    }

    return GP2Y10::dustDensity * 1000.00;
}

void GP2Y10::readSensor()
{
    for (int i = 0; i < DENSITY_HISTROY_COUNT - 1; i++)
    {
        GP2Y10::dustDensityHistory[i] = GP2Y10::dustDensityHistory[i + 1];
    }
    GP2Y10::dustDensityHistory[DENSITY_HISTROY_COUNT - 1] = getDustDensityNow();

    float total = 0;
    for (int i = 0; i < DENSITY_HISTROY_COUNT; i++)
    {
        total += GP2Y10::dustDensityHistory[i];
    }
    GP2Y10::dustDensityAverage = total / DENSITY_HISTROY_COUNT;
}

float GP2Y10::getDustDensity()
{
    return GP2Y10::dustDensityAverage;
}

float GP2Y10::getCalcVoltage()
{
    return GP2Y10::calcVoltage;
}

void GP2Y10::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["n"] = "GP2Y10";
    data["d"] = GP2Y10::dustDensity;
    data["a"] = GP2Y10::dustDensityAverage;
    data["c"] = GP2Y10::calcVoltage;
    data["m"] = GP2Y10::voMeasured;
}
