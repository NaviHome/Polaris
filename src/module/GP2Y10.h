#pragma once

#include "util/BinaryStream.h"

class GP2Y10
{
public:
  static void init();
  static float getDustDensityNow();
  static float getDustDensity();
  static float getCalcVoltage();
  static void writeDataToStream(BinaryStream &stream);
};
