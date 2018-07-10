#pragma once

#include <Arduino.h>

class Util
{
public:
  static void encodeAndSendJsonData(String name, String ver);
  static String getUptime();
};
