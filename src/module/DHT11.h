#pragma once

#include "util/BinaryStream.h"

class DHT11
{
public:
  static bool readSensor();
  static byte getTemperature();
  static byte getHumidity();
  static void writeDataToStream(BinaryStream &stream);
};
