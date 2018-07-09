#ifndef BMP180_H
#define BMP180_H

#include <Adafruit_BMP085.h>

class BMP180{
public:
    static void init();
    static Adafruit_BMP085 getBmp();
    static String getJsonData();
};

#endif