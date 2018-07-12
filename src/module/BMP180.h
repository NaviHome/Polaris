#pragma once

#include <Adafruit_BMP085.h>
#include "util/BinaryStream.h"

class BMP180
{
public:
  static void init();
  static Adafruit_BMP085 getSensor();
  static void writeDataToStream(BinaryStream &stream);
};
