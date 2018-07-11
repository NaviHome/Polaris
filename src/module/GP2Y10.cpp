#include <Arduino.h>
#include <ArduinoJson.h>
#include "GP2Y10.h"

#define DENSITY_HISTROY_COUNT 10

int ledPin = 2;
int voutPin = A0;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
int voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
float dustDensityAverage = 0;

float dustDensityHistory[DENSITY_HISTROY_COUNT];

void GP2Y10::init()
{
    pinMode(ledPin, OUTPUT);
    for (int i = 0; i < 10; i++)
    {
        dustDensityHistory[i] = 0;
    }
}

float GP2Y10::getDustDensityNow()
{
    digitalWrite(ledPin, LOW); // power on the LED
    delayMicroseconds(samplingTime);

    voMeasured = analogRead(voutPin); // read the dust value

    delayMicroseconds(deltaTime);
    digitalWrite(ledPin, HIGH); // turn the LED off
    delayMicroseconds(sleepTime);

    // 0 - 5V mapped to 0 - 1023 integer values
    // recover voltage
    calcVoltage = (float)voMeasured * (5.0 / 1024.0);

    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012
    if (calcVoltage >= 0.6)
    {
        dustDensity = 0.17 * calcVoltage - 0.1;
    }
    else
    {
        dustDensity = 0;
    }

    return dustDensity * 1000.00;
}

float GP2Y10::getDustDensity()
{
    for (int i = 0; i < DENSITY_HISTROY_COUNT - 1; i++)
    {
        dustDensityHistory[i] = dustDensityHistory[i + 1];
    }
    dustDensityHistory[DENSITY_HISTROY_COUNT - 1] = getDustDensityNow();

    float total = 0;
    for (int i = 0; i < DENSITY_HISTROY_COUNT; i++)
    {
        total += dustDensityHistory[i];
    }
    dustDensityAverage = total / DENSITY_HISTROY_COUNT;
    return dustDensityAverage;
}

float GP2Y10::getCalcVoltage()
{
    return calcVoltage;
}

void GP2Y10::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["name"] = "GP2Y10";
    data["density"] = dustDensity;
    data["densityAvg"] = dustDensityAverage;
    data["calcVoltage"] = calcVoltage;
    data["voMeasured"] = voMeasured;
}
