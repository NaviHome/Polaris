#pragma once

#include <ArduinoJson.h>
#include <Adafruit_BMP085.h>

class BMP180
{
public:
  static void init();
  static Adafruit_BMP085 getSensor();
  static void addJsonData(JsonArray &array);
};
