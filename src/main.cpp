#include <Arduino.h>
#include "module/DHT11.h"
#include "module/LcdHelper.h"
#include "module/BMP180.h"
#include "module/GP2Y10.h"
#include "util/Util.h"
#include "util/DataManager.h"
#include "config.h"

int loopDelay = 500;

void setup()
{
    Serial.begin(115200);
    DataManager::init();
    LcdHelper::init();
    BMP180::init();
    GP2Y10::init();
}

void loop()
{
    long startTime = millis();

    LcdHelper::setDefalutValue();

    TFT_22_ILI9225 display = LcdHelper::getDisplay();
    display.drawText(10, 40, "Temperature: " + String(BMP180::getSensor().readTemperature()) + " *C");
    display.drawText(10, 50, "Pressure: " + String(BMP180::getSensor().readPressure()) + " Pa");

    DHT11::readSensor();
    display.drawText(10, 70, "DigitalTemp: " + String(DHT11::getTemperature()) + " *C");
    display.drawText(10, 80, "Humidity: " + String(DHT11::getHumidity()) + "%");

    display.drawText(10, 100, "DustDensity: " + String(GP2Y10::getDustDensity()) + " ug/m3   ");

    display.drawText(10, 120, "LoopTime: " + String(millis() - startTime) + " ms   ");
    display.drawText(10, 130, "Uptime: " + Util::getUptime() + "  ");

    DataManager::update();

    delay(loopDelay);
}
