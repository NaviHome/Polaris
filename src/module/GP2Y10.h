/*
 * Copyright (C) 2018 iTX Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <ArduinoJson.h>

#define DENSITY_HISTROY_COUNT 10

class GP2Y10
{
private:
  static int voMeasured;
  static float calcVoltage;
  static float dustDensity;
  static float dustDensityAverage;

  static float dustDensityHistory[DENSITY_HISTROY_COUNT];

public:
  static void init();
  static void readSensor();
  static float getDustDensityNow();
  static float getDustDensity();
  static float getCalcVoltage();
  static void addJsonData(JsonArray &array);
};
