#ifndef LCD_HELPER_H
#define LCD_HELPER_H

#include <LiquidCrystal_I2C.h>

class LcdHelper
{
public:
    static void init();
    static LiquidCrystal_I2C getLcd();
    static void printFromStart(String str);
    static void printSecondLine(String str);
    static void clear();
};

#endif