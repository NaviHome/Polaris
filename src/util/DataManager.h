#pragma once

#include <Arduino.h>

class DataManager
{
public:
  static String timeNow;
  static String wifiModuleFirmwareInfo;
  static void init();
  static void update();
};
