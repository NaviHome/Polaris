#pragma once

#include <ArduinoJson.h>

class GP2Y10
{
public:
  static void init();
  static float getDustDensity(); //unit mg/cm3
  static float getCalcVoltage();
  static void addJsonData(JsonArray &array);
};
