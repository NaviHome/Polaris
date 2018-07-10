#include <Arduino.h>

/*
Standalone Sketch to use with a Arduino UNO and a
Sharp Optical Dust Sensor GP2Y1010AU0F
/**user define**/
//Connect Vo of dust sensor Vo to Arduino A0 pin int ledPin = 2;
//Connect LED(3pin) of dust sensor to Arduino D2 pin

/**system define**/

int voutPin = A0;
int ledPin = 2;

int samplingTime = 280;
int deltaTime = 40;
int sleepTime = 9680;
int voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;

void setup()
{

    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
}

void loop()
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

    Serial.print("Raw Signal Value (0-1023): ");
    Serial.print(voMeasured);

    Serial.print(" - Voltage: ");
    Serial.print(calcVoltage);
    Serial.print("V");

    Serial.print(" - Dust Density: ");

    if (calcVoltage > 3.5)
    {
        Serial.print(">"); // unit: mg/m3
    }

    Serial.print(dustDensity);
    Serial.println(" mg/m3");

    delay(1000);
}
