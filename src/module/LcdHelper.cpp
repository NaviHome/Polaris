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

#include <inttypes.h>
#include <TFT_22_ILI9225.h>
#include "LcdHelper.h"
#include "../util/Configuration.h"
#include "../util/DataManager.h"
#include "../config.h"

#define TFT_DEFAULT_BRIGHTNESS 50

#define BRIGHTNESS_LEVELS 10
static const uint16_t lightLevelList[] = {1, 2, 3, 5, 10, 20, 50, 100, 200, 300, 400, 500, 600, 700, 800, 1000, 1200, 1600, 2200, 3000, 4000};
static const uint8_t brightnessList[] = {1, 2, 4, 8, 12, 20, 30, 46, 49, 54, 61, 65, 70, 76, 82, 87, 98, 108, 131, 161, 230, 255};

TFT_22_ILI9225 display(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_DEFAULT_BRIGHTNESS);

unsigned long LcdHelper::lastUpdate = 0;

void LcdHelper::init()
{
    display.begin();
}

TFT_22_ILI9225 LcdHelper::getDisplay()
{
    return display;
}

void LcdHelper::load()
{
    display.clear();
    display.setOrientation(3);

    display.drawRectangle(0, 0, display.maxX() - 1, display.maxY() - 1, COLOR_ORANGE);
    display.setFont(Terminal6x8);
    //display.drawText(10, 10, "Now loading...", COLOR_GRAY);
    display.drawText(10, display.maxY() - 12, COPYRIGHT, COLOR_GRAY);
    display.setFont(Terminal12x16);
    display.drawText(70, 60, NAME, COLOR_LIGHTBLUE);
    display.setFont(Terminal11x16);
    display.drawText(85, 85, VER);
    delay(1500);
    display.clear();

    display.drawRectangle(0, 0, display.maxX() - 1, display.maxY() - 1, COLOR_GREEN);
    printHeader();
}

void LcdHelper::printHeader()
{
    display.setFont(Terminal6x8);
    display.drawText(10, 10, NAME + " " + VER);
    display.drawText(10, 20, DataManager::wifiModuleFirmwareInfo);
    display.drawText(110, 20, Configuration::WIFI_SSID);
    display.drawText(10, 30, COPYRIGHT);
}

void LcdHelper::updateBrightness(unsigned long lightLevel)
{
    if (millis() - lastUpdate > UPDATE_DELAY)
    {
        lastUpdate = millis();
        bool valid = false;
        for(int i = 0; i < BRIGHTNESS_LEVELS; i++){
            if(lightLevel <= lightLevelList[i])
            {
                valid = true;
                display.setBacklightBrightness(brightnessList[i]);
                break;
            }
        }
        if(!valid)
        {
            display.setBacklightBrightness(brightnessList[BRIGHTNESS_LEVELS + 1]);
        }
    }
}