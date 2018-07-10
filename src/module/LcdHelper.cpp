#include <SPI.h>
#include "TFT_22_ILI9225.h"
#include "LcdHelper.h"
#include "config.h"

#define TFT_RST 8
#define TFT_RS  9
#define TFT_CS  10  // SS
#define TFT_SDI 11  // MOSI
#define TFT_CLK 13  // SCK
#define TFT_LED 3   // 0 if wired to +5V directly

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

void LcdHelper::setDefalutValue(bool force = false){
    if(force or !initiated){
        display.setOrientation(3);
        display.drawRectangle(0, 0, display.maxX() - 1, display.maxY() - 1, COLOR_GREEN);
        display.setFont(Terminal6x8);
        display.drawText(10, 10, NAME + " " + VER);
        display.drawText(10, 20, COPYRIGHT);
        initiated = true;
    }
}