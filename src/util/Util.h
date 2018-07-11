#pragma once

#include <Arduino.h>

class Util
{
public:
  static void encodeAndSendJsonData();
  static String getUptime();
};
