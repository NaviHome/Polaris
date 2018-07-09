#ifndef BMP180_H
#define BMP180_H

#include <ArduinoJson.h>
#include <Adafruit_BMP085.h>

class BMP180
{
  public:
    static void init();
    static Adafruit_BMP085 getSensor();
    static void addJsonData(JsonArray &array);
};

#endif