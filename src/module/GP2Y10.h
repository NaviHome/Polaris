#pragma once

#include <ArduinoJson.h>

#define DENSITY_HISTROY_COUNT 10

class GP2Y10
{
private:
  static int voMeasured;
  static float calcVoltage;
  static float dustDensity;
  static float dustDensityAverage;

  static float dustDensityHistory[DENSITY_HISTROY_COUNT];

public:
  static void init();
  static void readSensor();
  static float getDustDensityNow();
  static float getDustDensity();
  static float getCalcVoltage();
  static void addJsonData(JsonArray &array);
};
