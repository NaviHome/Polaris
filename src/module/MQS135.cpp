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
#include <MQ135.h>
#include "MQS135.h"
#include "../config.h"

float MQS135::ratio;
unsigned long MQS135::ppm;
unsigned long MQS135::ppmAverage;
unsigned long MQS135::ppmHistory[PPM_HISTORY_COUNT];

MQ135 mq(MQ135_PIN);

void MQS135::init()
{
    mq.calibrate();
    for (int i = 0; i < PPM_HISTORY_COUNT; i++)
    {
        MQS135::ppmHistory[i] = 0;
    }
}

void MQS135::readSensor()
{
    MQS135::ratio = mq.readRatio();
    MQS135::ppm = mq.readCO2();

    for (int i = 0; i < PPM_HISTORY_COUNT - 1; i++)
    {
        MQS135::ppmHistory[i] = MQS135::ppmHistory[i + 1];
    }
    MQS135::ppmHistory[PPM_HISTORY_COUNT - 1] = MQS135::ppm;

    float total = 0;
    for (int i = 0; i < PPM_HISTORY_COUNT; i++)
    {
        total += MQS135::ppmHistory[i];
    }
    MQS135::ppmAverage = total / PPM_HISTORY_COUNT;
}

float MQS135::getRatio()
{
    return MQS135::ratio;
}

unsigned long MQS135::getPpm()
{
    return MQS135::ppmAverage;
}

void MQS135::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["n"] = "MQ135";
    data["r"] = MQS135::ratio;
    data["p"] = MQS135::ppm;
    data["a"] = MQS135::ppmAverage;
}
