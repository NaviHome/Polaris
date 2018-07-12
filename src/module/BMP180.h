#pragma once

#include <ArduinoJson.h>
#include <Adafruit_BMP085.h>

class BMP180
{
private:
  static float temperature;
  static long pressure;

public:
  static void init();
  static void readSensor();
  static float getTemperature();
  static long getPressure();
  static void addJsonData(JsonArray &array);
};
