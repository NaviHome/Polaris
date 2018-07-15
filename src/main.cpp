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
#include "module/BH1750FVI.h"
#include "module/DHT11.h"
#include "module/LcdHelper.h"
#include "module/BMP180.h"
#include "module/GP2Y10.h"
#include "util/Util.h"
#include "util/DataManager.h"
#include "config.h"

void setup()
{
    DataManager::init();
}

void loop()
{
    long startTime = millis();

    LcdHelper::setDefalutValue();
    DataManager::update();

    TFT_22_ILI9225 display = LcdHelper::getDisplay();
    display.drawText(10, 50, "Temp: " + String(BMP180::getTemperature()) + " *C");//Temperature
    display.drawText(110, 50, "Pres: " + String(BMP180::getPressure()) + " Pa");//Pressure

    display.drawText(10, 70, "DT: " + String(DHT11::getTemperature()) + " *C");//Digital Temperature
    display.drawText(110, 70, "HR: " + String(DHT11::getHumidity()) + "%");//Relative Humidity

    display.drawText(10, 90, "DustDensity: " + String(GP2Y10::getDustDensity()) + " ug/m3   ");//Dust Density

    display.drawText(10, 110, "LightLevel: " + String(BH1750FVI::getLightLevel()) + " lx  ");

    display.drawText(10, 130, "LoopTime: " + String(millis() - startTime) + " ms   ");//Loop Time
    display.drawText(10, 140, "Uptime: " + Util::getUptime() + "  ");//Uptime

    display.drawText(10, 150, "Time: " + DataManager::getFormattedTime());//Current Time

    delay(MAIN_LOOP_DELAY);
}