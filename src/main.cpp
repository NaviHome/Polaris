#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

//Polaris v0.1

LiquidCrystal_I2C lcd(0x3F, 16, 4);

void setup() {
    Serial.begin(115200);
    lcd.begin();
    lcd.backlight();
    pinMode(13, OUTPUT);
}

void loop() {
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    delay(1000);
}
