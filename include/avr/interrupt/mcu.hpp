#pragma once

#if __AVR_ATtiny13A__
#include "avr/interrupt/mcu/attiny13a.h"
#elif __AVR_ATtiny25__ || __AVR_ATtiny45__ || __AVR_ATtiny85__
#include "avr/interrupt/mcu/attiny85.h"
#endif
