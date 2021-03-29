#pragma once

#define AVRINT_RESET(...) AVRINT_ISR(__vector_0, __VA_ARGS__)
#define AVRINT_INT0(...) AVRINT_ISR(__vector_1, __VA_ARGS__)
#define AVRINT_INT1(...) AVRINT_ISR(__vector_2, __VA_ARGS__)
#define AVRINT_PCINT0(...) AVRINT_ISR(__vector_3, __VA_ARGS__)
#define AVRINT_PCINT1(...) AVRINT_ISR(__vector_4, __VA_ARGS__)
#define AVRINT_PCINT2(...) AVRINT_ISR(__vector_5, __VA_ARGS__)
#define AVRINT_WDT(...) AVRINT_ISR(__vector_6, __VA_ARGS__)
#define AVRINT_TIMER2_COMPA(...) AVRINT_ISR(__vector_7, __VA_ARGS__)
#define AVRINT_TIMER2_COMPARE_A(...) AVRINT_TIMER2_COMPA(__VA_ARGS__)
#define AVRINT_TIMER2_COMPB(...) AVRINT_ISR(__vector_8, __VA_ARGS__)
#define AVRINT_TIMER2_COMPARE_B(...) AVRINT_TIMER2_COMPB(__VA_ARGS__)
#define AVRINT_TIMER2_OVF(...) AVRINT_ISR(__vector_9, __VA_ARGS__)
#define AVRINT_TIMER2_OVERFLOW(...) AVRINT_TIMER2_OVF(__VA_ARGS__)
#define AVRINT_TIMER1_CAPT(...) AVRINT_ISR(__vector_10, __VA_ARGS__)
#define AVRINT_TIMER1_CAPTURE(...) AVRINT_TIMER1_CAPT(__VA_ARGS__)
#define AVRINT_TIMER1_COMPA(...) AVRINT_ISR(__vector_11, __VA_ARGS__)
#define AVRINT_TIMER1_COMPARE_A(...) AVRINT_TIMER1_COMPA(__VA_ARGS__)
#define AVRINT_TIMER1_COMPB(...) AVRINT_ISR(__vector_12, __VA_ARGS__)
#define AVRINT_TIMER1_COMPARE_B(...) AVRINT_TIMER1_COMPB(__VA_ARGS__)
#define AVRINT_TIMER1_OVF(...) AVRINT_ISR(__vector_13, __VA_ARGS__)
#define AVRINT_TIMER1_OVERFLOW(...) AVRINT_TIMER1_OVF(__VA_ARGS__)
#define AVRINT_TIMER0_COMPA(...) AVRINT_ISR(__vector_14, __VA_ARGS__)
#define AVRINT_TIMER0_COMPARE_A(...) AVRINT_TIMER0_COMPA(__VA_ARGS__)
#define AVRINT_TIMER0_COMPB(...) AVRINT_ISR(__vector_15, __VA_ARGS__)
#define AVRINT_TIMER0_COMPARE_B(...) AVRINT_TIMER0_COMPB(__VA_ARGS__)
#define AVRINT_TIMER0_OVF(...) AVRINT_ISR(__vector_16, __VA_ARGS__)
#define AVRINT_TIMER0_OVERFLOW(...) AVRINT_TIMER0_OVF(__VA_ARGS__)
#define AVRINT_SPI_STC(...) AVRINT_ISR(__vector_17, __VAR_ARGS__)
#define AVRINT_USART_RX(...) AVRINT_ISR(__vector_18, __VAR_ARGS__)
#define AVRINT_USART_UDRE(...) AVRINT_ISR(__vector_19, __VAR_ARGS__)
#define AVRINT_USART_TX(...) AVRINT_ISR(__vector_20, __VAR_ARGS__)
#define AVRINT_ADC(...) AVRINT_ISR(__vector_21, __VA_ARGS__)
#define AVRINT_EE_READY(...) AVRINT_ISR(__vector_22, __VA_ARGS__)
#define AVRINT_ANALOG_COMP(...) AVRINT_ISR(__vector_23, __VA_ARGS__)
#define AVRINT_ANALOG_COMPARATOR(...) AVRINT_ANALOG_COMP(__VA_ARGS__)
#define AVRINT_TWI(...) AVRINT_ISR(__vector_24, __VA_ARGS__)
#define AVRINT_SPM_READY(...) AVRINT_ISR(__vector_25, __VA_ARGS__)
