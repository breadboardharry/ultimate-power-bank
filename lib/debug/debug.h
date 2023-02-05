#ifndef DEBUG_H
#define DEBUG_H

#include <Arduino.h>

#if DEBUG

#define debug_begin(br) Serial.print(br)
#define debug_print(v) Serial.print(v)
#define debug_println(v) Serial.println(v)

#else

#define debug_begin(br)
#define debug_print(v)
#define debug_println(v)

#endif

#endif