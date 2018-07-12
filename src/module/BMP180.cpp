#include "BMP180.h"
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void BMP180::init()
{
    bmp.begin();
}

Adafruit_BMP085 BMP180::getSensor()
{
    return bmp;
}

void BMP180::writeDataToStream(BinaryStream &stream)
{
    stream.putFloat(bmp.readTemperature());
    stream.putInt(bmp.readPressure());
    stream.putFloat(bmp.readAltitude());
    stream.putInt(bmp.readSealevelPressure());
}