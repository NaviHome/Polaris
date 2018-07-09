#include "BMP180.h"
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void BMP180::init()
{
    bmp.begin();
}

Adafruit_BMP085 BMP180::getBmp(){
    return bmp;
}
