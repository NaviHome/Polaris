#pragma once

#include <ArduinoJson.h>

class DHT11
{
private:
  static byte temperature;
  static byte humidity;

public:
  static bool readSensor();
  static byte getTemperature();
  static byte getHumidity();
  static void addJsonData(JsonArray &array);
};
