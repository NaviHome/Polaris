#pragma once

#include <ArduinoJson.h>

class GP2Y10
{
  public:
    static void init();
    static float readSensor(); //unit mg/cm3
    static void addJsonData(JsonArray &array);
};
