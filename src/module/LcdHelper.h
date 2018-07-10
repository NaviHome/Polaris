#ifndef LCD_HELPER_H
#define LCD_HELPER_H

#include "TFT_22_ILI9225.h"

class LcdHelper
{
public:
  static void init();
  static TFT_22_ILI9225 getDisplay();
  static void setDefalutValue(bool force = false);
};

#endif