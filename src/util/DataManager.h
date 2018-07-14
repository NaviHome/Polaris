#pragma once

#include <Arduino.h>

class DataManager
{
public:
  static unsigned long startTime;
  static String wifiModuleFirmwareInfo;
  static void init();
  static void update();
  static unsigned long getTimeNow();
};
