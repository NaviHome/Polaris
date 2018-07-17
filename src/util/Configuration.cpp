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


#include <EEPROM.h>
#include "Configuration.h"
#include "../config.h"

#define SSID_LEN 32
#define PASS_LEN 32

char* Configuration::WIFI_PASS;
char* Configuration::WIFI_SSID;

void Configuration::init()
{
    int ssidAddr = 0;
    int passAddr = ssidAddr + SSID_LEN;

    // malloc for parameters
    WIFI_SSID = (char *)malloc(SSID_LEN);
    WIFI_PASS = (char *)malloc(PASS_LEN);

    // try to read out the credential information, if failed, the length should be 0.
    EEPROMRead(ssidAddr, WIFI_SSID);
    EEPROMRead(passAddr, WIFI_PASS);
}

void Configuration::setSsid(char* ssid){
    EEPROMWrite(0, ssid, strlen(ssid));//ssidAddr = 0
    WIFI_SSID = ssid;
}

void Configuration::setPass(char* pass){
    EEPROMWrite(SSID_LEN, pass, strlen(pass));//passAddr = ssidAddr + SSID_LEN
    WIFI_PASS = pass;
}

#define EEPROM_END 0
#define EEPROM_START 1
void Configuration::EEPROMWrite(int addr, char *data, int size)
{
    // write the start marker
    EEPROM.write(addr, EEPROM_START);
    addr++;
    for (int i = 0; i < size; i++)
    {
        EEPROM.write(addr, data[i]);
        addr++;
    }
    EEPROM.write(addr, EEPROM_END);
}

// read bytes from addr util '\0'
// return the length of read out.
int Configuration::EEPROMRead(int addr, char *buf)
{
    int count = -1;
    char c = EEPROM.read(addr);
    addr++;
    if (c != EEPROM_START)
    {
        return 0;
    }
    while (c != EEPROM_END)
    {
        c = (char)EEPROM.read(addr);
        count++;
        addr++;
        buf[count] = c;
    }
    return count;
}
