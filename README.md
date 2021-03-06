# Polaris

[![License](https://img.shields.io/github/license/NaviHome/Polaris.svg)](https://github.com/NaviHome/Polaris/blob/master/LICENSE)
[![Version](https://img.shields.io/badge/version-0.6.0--alpha-orange.svg)](https://github.com/NaviHome/Polaris/blob/master/src/config.h)
[![Build Status](https://travis-ci.org/NaviHome/Polaris.svg?branch=master)](https://travis-ci.org/NaviHome/Polaris)

The firmware of the main controller of [NaviHome](https://github.com/NaviHome) by [iTX Technologies](https://github.com/iTXTech).

## Requirements

* Arduino compatible board * 1
* Bread Board * 1
* ILI9225 2.2' TFT * 1
* DHT11 Sensor * 1
* BMP180 Sensor * 1
* GP2Y10(10/14) Sensor * 1
* BH1750FVI Sensor * 1
* MQ135 Sensor * 1
* UART WiFi Module * 1 (Recommended ESP-01)
* Dupont Wires

---------------

* [PlatformIO IDE](https://platformio.org/) (Recommended [Visual Studio Code](https://code.visualstudio.com/))

## Compatible Boards

* [Arduino Mega 2560](https://store.arduino.cc/arduino-mega-2560-rev3)
* [Arduino UNO R3/Nano](https://store.arduino.cc/arduino-uno-rev3) - *Check config.h, RAM may not enough*
* Any board which supports SPI, ADC, I2C
  * [ESP8266 DevBoard](https://www.esp8266.com/wiki/doku.php?id=esp8266-module-family)
  * [ESP32 DevBoard](https://esp-idf.readthedocs.io/en/latest/get-started/get-started-devkitc.html)
  * [STM32 DevBoard](https://www.st.com/en/microcontrollers/stm32f103c8.html)

## Modules

### Sensors

* BH1750FVI (I2C)
  * Light Level (1 lx)
* BMP180 (I2C)
  * Temperature (0.1°C)
  * Pressure (1 Pa)
  * ~~Altitude~~ - *Not available, API included*
  * ~~Sea Level Pressure~~ - *Not available, API included*
* DHT11 (Digital Signal)
  * Temperature (1°C)
  * Relative Humidity (1%)
* GP2Y10(10/14) (Analog Signal)
  * Dust Density (1 ug/m3)
* MQ135 (Analog Signal)
  * Gas concentration (1 ppm)

### Others

* ILI9225 2.2' TFT (SPI)
  * Screen Size: 176 * 220

## Step to Build

* Open Project in `PlatformIO IDE`
* Change `DEBUG` to `false` in `config.h` when debugging WiFi Module
* Connect the board
* Execute `PlatformIO: Upload` to flash the firmware
* Enjoy :)

---------------

* Remember to modify `PIN layout configurations` in `config.h` if you changed them

## Serial Command Line

* Format: JSON
* See `util/DataManager.cpp` for more details

```C++
    /*
    commands:
        0: WiFi Module Information
            {"c":0,"n":"Chronos","v":"0.1.0"}
            n: Firmware Name
            v: Firmware Version
        1: Re-init Display
            {"c":1}
        2: Update Time
            {"c":2,"t":"1531615194"}
            t: Current Unix Timestamp
        3: Get Information (Firmware info, WiFi info)
            {"c":3}
        4: Set WiFi Info
            {"c":4,"s":"SSIDofWiFi","p":"password"}
            s: SSID
            p: Password
    */
```

## License

    Copyright (C) 2018 iTX Technologies

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.