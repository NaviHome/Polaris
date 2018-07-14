# Polaris

The firmware of the main controller of [NaviHome](https://github.com/NaviHome) by [iTX Technologies](https://github.com/iTXTech).

## Requirements

* Arduino compatible board * 1
* Bread Board * 1
* ILI9225 2.2' TFT * 1
* DHT11 Sensor * 1
* BMP180 Sensor * 1
* UART WiFi Module * 1 (Recommended ESP-01)
* Dupont Wires

---------------

* [PlatformIO IDE](https://platformio.org/) (Recommended [Visual Studio Code](https://code.visualstudio.com/))

## Compatible Boards

* [Arduino UNO](https://store.arduino.cc/arduino-uno-rev3) - *Tested*
* [Arduino Mega 2560](https://store.arduino.cc/arduino-mega-2560-rev3) - *Tested*
* [Arduino Nano](https://store.arduino.cc/arduino-nano) - *Tested*
  * Change `BOARD_NANO` to `true` in `config.h`

---------------

* Any board which supports SPI, ADC, I2C
  * [ESP8266 DevBoard](https://www.esp8266.com/wiki/doku.php?id=esp8266-module-family)
  * [ESP32-DevKitC V4](https://esp-idf.readthedocs.io/en/latest/get-started/get-started-devkitc.html)
  * [STM32 DevBoard](https://www.st.com/en/microcontrollers/stm32f103c8.html)

## Environmental Data

* BMP180
  * Temperature (0.1°C)
  * Pressure (1 Pa)
  * ~~Altitude~~ - *Not available, API included*
  * ~~Sea Level Pressure~~ - *Not available, API included*
* DHT11
  * Temperature (1°C)
  * Humidity (1%)
* GP2Y10(10/14)
  * Dust Density (1 ug/m3)

## Step to Build

* Open Project in PlatformIO IDE
* Change `DEBUG` to `false` in `config.h` when debuging WiFi Module
* Modify `PIN layout configuration` in `config.h` after you changed it
* Connect the board
* Execute `PlatformIO: Upload` to flash the firmware
* Enjoy :)

## Serial Command Line

* Format: JSON
* See `util/DataManager.cpp` for more details

```C++
    /*
    command types:
        0: WiFi Module Information
            {"c":0,"fn":"Chronos","fv":"0.1.0"}
            fn: Firmware Name
            fv: Firmware Version
        1: Re-init display
            {"c":1}
        2: Update Time
            {"c":2,"t":"2018-07-14 18:09:23"}
            t: Current Time String
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