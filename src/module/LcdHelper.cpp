#include "LcdHelper.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C display(0x3F, 16, 4);

void LcdHelper::init()
{
    display.begin();
    display.backlight();
}

LiquidCrystal_I2C LcdHelper::getLcd()
{
    return display;
}

void LcdHelper::printFromStart(String str)
{
    display.home();
    display.print(str);
}

void LcdHelper::printSecondLine(String str)
{
    display.setCursor(0, 1);
    display.print(str);
}

void LcdHelper::clear()
{
    String str = "                "; //16 chars
    printFromStart(str);
    printSecondLine(str);
}