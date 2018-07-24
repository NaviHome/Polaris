/*
 * Copyright (C) 2018 iTX Technologies
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <avr/wdt.h>

#define NAME "Polaris"
#define VER "0.5.3"
#define COPYRIGHT "(C) 2018 iTX Technologies"

//Change to true when using ATmega328P
#define MINIMIZE false

//Use SoftwareSerial
#define SOFTWARE_SERIAL false
#define SOFTWARE_SERIAL_RX 2
#define SOFTWARE_SERIAL_TX 3

//Change this to false when release
#define DEBUG true

//Timezone for calcuting timestamp, default = GMT+8
//#define TIMEZONE -6
#define TIMEZONE 8

//WatchDog Timeout
#define WATCHDOG_TIMER_TIMEOUT WDTO_4S

//Serial config
#define SERIAL_BAUDRATE 115200
#define SERIAL_READ_TIMEOUT 100

//WiFi Module UART config
#define WIFI_MODULE_BAUDRATE 115200

#define MAIN_LOOP_DELAY 200

//DHT11 config
#define DHT11_PIN 44

//GP2Y10 config
#define LED_PIN 45
#define VOUT_PIN A0

//ILI9225 config
#define TFT_RST 48
#define TFT_RS 49
#define TFT_CS 53  // SS
#define TFT_SDI 51 // MOSI
#define TFT_CLK 52 // SCK
#define TFT_LED 3  // 0 if wired to +5V directly
#define UPDATE_DELAY 1000