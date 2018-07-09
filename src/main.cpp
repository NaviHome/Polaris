#include <Arduino.h>
#include <ArduinoJson.h>
#include "module/DHT11.h"
#include "module/LcdHelper.h"
#include "module/BMP180.h"
#include "util/Util.h"

const String NAME = "Polaris";
const String VER = "0.1.0";

const int LOOP_DELAY = 500;

void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT); //led on board
    digitalWrite(13, HIGH);

    LcdHelper::init();
    LcdHelper::printFromStart(NAME + " " + VER);
    LcdHelper::printSecondLine("Now loading...");
    delay(LOOP_DELAY * 2);
    LcdHelper::clear();
    digitalWrite(13, LOW);

    BMP180::init();
}

void loop()
{
    long startTime = millis();
    digitalWrite(13, HIGH); //one loop

    LcdHelper::printFromStart(String(BMP180::getSensor().readTemperature()) + "C/" + String(BMP180::getSensor().readPressure()) + "Pa");

    DHT11::readSensor();
    LcdHelper::printSecondLine(String(DHT11::getTemperature()) + "C / " + String(DHT11::getHumidity()) + "% " + String(millis() - startTime) + "ms");

    Util::encodeAndSendJsonData(NAME, VER);

    delay(LOOP_DELAY / 2);
    digitalWrite(13, LOW);
    delay(LOOP_DELAY / 2);
}
