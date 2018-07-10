#include <Arduino.h>
#include <ArduinoJson.h>
#include "GP2Y10.h"

int ledPin = 2;
int voutPin = A0;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
int voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void GP2Y10::init()
{
    pinMode(ledPin, OUTPUT);
}

float GP2Y10::readSensor()
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

    return dustDensity;
}

void GP2Y10::addJsonData(JsonArray &array)
{
    JsonObject &data = array.createNestedObject();
    data["name"] = "GP2Y10";
    data["dustDensity"] = dustDensity;
    data["calcVoltage"] = calcVoltage;
    data["voMeasured"] = voMeasured;
}
