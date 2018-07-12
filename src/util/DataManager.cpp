#include <SoftwareSerial.h>
#include "DataManager.h"
#include "module/BMP180.h"
#include "module/DHT11.h"
#include "module/GP2Y10.h"
#include "config.h"
#include "BinaryStream.h"

#define ESP_RX 5
#define ESP_TX 6

#define ESP_BAUDRATE 9600

SoftwareSerial esp(ESP_RX, ESP_TX); //RX TX

void DataManager::init()
{
    esp.begin(ESP_BAUDRATE);
}

void DataManager::update()
{
    BinaryStream stream(128);

    BMP180::writeDataToStream(stream);
    DHT11::writeDataToStream(stream);
    GP2Y10::writeDataToStream(stream);

    Serial.println(stream.getAsCharArray());
}
