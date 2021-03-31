#pragma once

#if __AVR_ATtiny13A__
#include "avr/interrupt/mcu/attiny13a.hpp"
#elif __AVR_ATtiny25__ || __AVR_ATtiny45__ || __AVR_ATtiny85__
#include "avr/interrupt/mcu/attiny85.hpp"
#elif __AVR_ATmega328P__ || __AVR_ATmega328__
#include "avr/interrupt/mcu/atmega328p.hpp"
#endif
