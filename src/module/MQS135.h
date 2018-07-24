#pragma once

//MQ Sensor 135
class MQS135
{
private:
  static float ratio;
  static unsigned long ppm;
public:
  static void init();
  static void readSensor();
  static float getRatio();
  static unsigned long getPpm();
  static void addJsonData(JsonArray &array);
};