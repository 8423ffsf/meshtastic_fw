#ifndef OLEDDISPLAYFONTSUA_h
#define OLEDDISPLAYFONTSUA_h

#ifdef ARDUINO
#include <Arduino.h>
#elif __MBED__
#define PROGMEM
#endif

#ifdef HAS_XIP_QSPI
#define PROGMEM __attribute__((section(".progmem")))
#endif

extern const uint8_t ArialMT_Plain_10_UA[] PROGMEM;
extern const uint8_t ArialMT_Plain_16_UA[] PROGMEM;
extern const uint8_t ArialMT_Plain_24_UA[] PROGMEM;
#endif