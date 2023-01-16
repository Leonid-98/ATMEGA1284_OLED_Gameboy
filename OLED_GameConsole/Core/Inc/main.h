/*
 * main.h
 *
 *  Author: Leonid T?igrinski
 */

/**
PWM     = PD4   - OC1B
BUZZER  = PD5   - OC1A
UART0   = PD0/1
I2C     = PC0/1
BUTTON  = PA4-PA7
*/

#ifndef MAIN_H_

#define MAIN_H_



#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include <util/delay.h>

#define ENABLE_DEBUG_LED \
DDRD |= 1 << PORTD4; \
PORTD |= 1 << PORTD4;
#define DISABLE_DEBUG_LED   \
DDRD &= !(0 << PORTD4); \
PORTD &= !(0 << PORTD4);

#endif /* MAIN_H_ */