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

#include <BH1750.h>
#include "BH1750FVI.h"

unsigned long BH1750FVI::lightLevel = 0;

BH1750 bh(0x23);

void BH1750FVI::init()
{
    bh.begin(BH1750::CONTINUOUS_HIGH_RES_MODE_2);
}

void BH1750FVI::readSensor(){
    BH1750FVI::lightLevel = bh.readLightLevel();
}

unsigned long BH1750FVI::getLightLevel(){
    return BH1750FVI::lightLevel;
}

void BH1750FVI::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["n"] = "BH1750FVI";
    data["l"] = BH1750FVI::lightLevel;
}