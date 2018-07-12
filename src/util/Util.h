#pragma once

#include <Arduino.h>
#include <inttypes.h>

class Util
{
public:
  static String getUptime();
  static uint8_t *copyOfRange(uint8_t *original, int from, int to);
};
