#pragma once

#include "TFT_22_ILI9225.h"

class LcdHelper
{
public:
  static void init();
  static TFT_22_ILI9225 getDisplay();
  static void setDefalutValue(bool force = false);
  static void printHeader();
};
