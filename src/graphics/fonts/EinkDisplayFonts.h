#ifndef EINKDISPLAYFONTS_h
#define EINKDISPLAYFONTS_h

#ifdef USE_EINK

#ifdef ARDUINO
#include <Arduino.h>
#elif __MBED__
#define PROGMEM
#endif

#ifdef HAS_XIP_QSPI
#define PROGMEM __attribute__((section(".progmem")))
#endif

/**
 * Monospaced Plain 30
 */
extern const uint8_t Monospaced_plain_30[] PROGMEM;

#endif // USE_EINK

#endif
