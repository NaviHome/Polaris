#pragma once

#include <Arduino.h>

//Change this to false when release
#define DEBUG true

//Change this to true when using Arduino Nano
#define BOARD_NANO false

//WiFi Module UART config
#define WIFI_MODULE_RX 5
#define WIFI_MODULE_TX 6
#define WIFI_MODULE_BAUDRATE 115200

//DHT11 PIN config
#define DHT11_PIN 4

//GP2Y10 PIN config
#define LED_PIN 2
#define VOUT_PIN A0

//ILI9225 TFT PIN config
#define TFT_RST 8
#define TFT_RS 9
#define TFT_CS 10  // SS
#define TFT_SDI 11 // MOSI
#define TFT_CLK 13 // SCK
#define TFT_LED 3  // 0 if wired to +5V directly

const String NAME = "Polaris";
const String VER = "0.4.3";
const String COPYRIGHT = "(C) 2018 iTX Technologies";
