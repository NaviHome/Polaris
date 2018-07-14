#include <Arduino.h>
#include <ArduinoJson.h>
#include "GP2Y10.h"

#define LED_PIN 2
#define VOUT_PIN A0

#define SAMPLEING_TIME 280
#define DELTA_TIME 40
#define SLEEP_TIME 9680

int GP2Y10::voMeasured = 0;
float GP2Y10::calcVoltage = 0;
float GP2Y10::dustDensity = 0;
float GP2Y10::dustDensityAverage = 0;

float GP2Y10::dustDensityHistory[DENSITY_HISTROY_COUNT];

void GP2Y10::init()
{
    pinMode(LED_PIN, OUTPUT);
    for (int i = 0; i < 10; i++)
    {
        GP2Y10::dustDensityHistory[i] = 0;
    }
}

float GP2Y10::getDustDensityNow()
{
    digitalWrite(LED_PIN, LOW); // power on the LED
    delayMicroseconds(SAMPLEING_TIME);

    GP2Y10::voMeasured = analogRead(VOUT_PIN); // read the dust value

    delayMicroseconds(DELTA_TIME);
    digitalWrite(LED_PIN, HIGH); // turn the LED off
    delayMicroseconds(SLEEP_TIME);

    // 0 - 5V mapped to 0 - 1023 integer values
    // recover voltage
    GP2Y10::calcVoltage = (float)GP2Y10::voMeasured * (5.0 / 1024.0);

    // linear eqaution taken from http://www.howmuchsnow.com/arduino/airquality/
    // Chris Nafis (c) 2012
    if (GP2Y10::calcVoltage >= 0.6)
    {
        GP2Y10::dustDensity = 0.17 * GP2Y10::calcVoltage - 0.1;
    }
    else
    {
        GP2Y10::dustDensity = 0;
    }

    return GP2Y10::dustDensity * 1000.00;
}

void GP2Y10::readSensor()
{
    for (int i = 0; i < DENSITY_HISTROY_COUNT - 1; i++)
    {
        GP2Y10::dustDensityHistory[i] = GP2Y10::dustDensityHistory[i + 1];
    }
    GP2Y10::dustDensityHistory[DENSITY_HISTROY_COUNT - 1] = getDustDensityNow();

    float total = 0;
    for (int i = 0; i < DENSITY_HISTROY_COUNT; i++)
    {
        total += GP2Y10::dustDensityHistory[i];
    }
    GP2Y10::dustDensityAverage = total / DENSITY_HISTROY_COUNT;
}

float GP2Y10::getDustDensity(){
    return GP2Y10::dustDensityAverage;
}

float GP2Y10::getCalcVoltage()
{
    return GP2Y10::calcVoltage;
}

void GP2Y10::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["n"] = "GP2Y10";
    data["d"] = GP2Y10::dustDensity;
    data["a"] = GP2Y10::dustDensityAverage;
    data["c"] = GP2Y10::calcVoltage;
    data["m"] = GP2Y10::voMeasured;
}
