#include <Arduino.h>
#include "GP2Y10.h"

#define DENSITY_HISTROY_COUNT 10

#define LED_PIN 2
#define VOUT_PIN A0

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
    pinMode(LED_PIN, OUTPUT);
    for (int i = 0; i < 10; i++)
    {
        dustDensityHistory[i] = 0;
    }
}

float GP2Y10::getDustDensityNow()
{
    digitalWrite(LED_PIN, LOW); // power on the LED
    delayMicroseconds(samplingTime);

    voMeasured = analogRead(VOUT_PIN); // read the dust value

    delayMicroseconds(deltaTime);
    digitalWrite(LED_PIN, HIGH); // turn the LED off
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

void GP2Y10::writeDataToStream(BinaryStream &stream)
{
    stream.putFloat(dustDensity);
    stream.putFloat(dustDensityAverage);
    stream.putFloat(calcVoltage);
    stream.putInt(voMeasured);
}
