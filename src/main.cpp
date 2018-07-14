#include <Arduino.h>
#include <time.h>
#include "module/DHT11.h"
#include "module/LcdHelper.h"
#include "module/BMP180.h"
#include "module/GP2Y10.h"
#include "util/Util.h"
#include "util/DataManager.h"

int loopDelay = 200;

void setup()
{
    DataManager::init();
}

void loop()
{
    long startTime = millis();

    LcdHelper::setDefalutValue();
    DataManager::update();

    TFT_22_ILI9225 display = LcdHelper::getDisplay();
    display.drawText(10, 50, "Temperature: " + String(BMP180::getTemperature()) + " *C");
    display.drawText(10, 60, "Pressure: " + String(BMP180::getPressure()) + " Pa");

    display.drawText(10, 80, "DigitalTemp: " + String(DHT11::getTemperature()) + " *C");
    display.drawText(10, 90, "Humidity: " + String(DHT11::getHumidity()) + "%");

    display.drawText(10, 110, "DustDensity: " + String(GP2Y10::getDustDensity()) + " ug/m3   ");

    display.drawText(10, 130, "LoopTime: " + String(millis() - startTime) + " ms   ");
    display.drawText(10, 140, "Uptime: " + Util::getUptime() + "  ");
    display.drawText(10, 150, "Time: " + String(DataManager::timeNow));

    delay(loopDelay);
}
