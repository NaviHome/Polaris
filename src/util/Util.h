#ifndef UTIL_H
#define UTIL_H

#include <Arduino.h>

class Util{
public:
    static void encodeAndSendJsonData(String name, String ver);
};

#endif