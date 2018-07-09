#include <Arduino.h>
#include "modules/LcdHelper.h"
#include "modules/BMP180.h"

const String NAME = "Polaris";
const String VER = "0.1.0";

const int LOOP_DELAY = 500;

void setup() {
    Serial.begin(115200);
    LcdHelper::init();
    LcdHelper::printFromStart(NAME + " " + VER);
    pinMode(13, OUTPUT);//led on board
    BMP180::init();
}

void loop() {
    digitalWrite(13, HIGH);//one loop

    LcdHelper::printFromStart("Temp: " + String(BMP180::getBmp().readTemperature()) + " *C");
    LcdHelper::printSecondLine("Pres: " + String(BMP180::getBmp().readPressure()) + " Pa");

    delay(LOOP_DELAY / 2);
    digitalWrite(13, LOW);
    delay(LOOP_DELAY / 2);
}
