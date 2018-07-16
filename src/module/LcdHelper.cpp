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

#include <SPI.h>
#include <TFT_22_ILI9225.h>
#include "LcdHelper.h"
#include "../util/DataManager.h"
#include "../config.h"

#define TFT_DEFAULT_BRIGHTNESS 100 //default brightness

TFT_22_ILI9225 display(TFT_RST, TFT_RS, TFT_CS, TFT_LED, TFT_DEFAULT_BRIGHTNESS);

bool initiated = false;

void LcdHelper::init()
{
    display.begin();
}

TFT_22_ILI9225 LcdHelper::getDisplay()
{
    return display;
}

void LcdHelper::setDefalutValue(bool force = false)
{
    if (force or !initiated)
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
        initiated = true;
    }
}

void LcdHelper::printHeader()
{
    display.setFont(Terminal6x8);
    display.drawText(10, 10, NAME + " " + VER);
    display.drawText(10, 20, DataManager::wifiModuleFirmwareInfo);
    display.drawText(10, 30, COPYRIGHT);
}