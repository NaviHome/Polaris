#include <ArduinoJson.h>
#include <MQ135.h>
#include "MQS135.h"
#include "../config.h"

float MQS135::ratio;
unsigned long MQS135::ppm;

MQ135 mq(MQ135_PIN);

void MQS135::init()
{
    mq.calibrate();
}

void MQS135::readSensor()
{
    MQS135::ratio = mq.readRatio();
    MQS135::ppm = mq.readCO2();
}

float MQS135::getRatio()
{
    return MQS135::ratio;
}

unsigned long MQS135::getPpm()
{
    return MQS135::ppm;
}

void MQS135::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["n"] = "MQ135";
    data["r"] = MQS135::ratio;
    data["p"] = MQS135::ppm;
}
