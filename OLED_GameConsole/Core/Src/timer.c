/*
 * timer.c
 *
 *  Author: Leonid Tsigrinski
 */


#include <stdint.h>
#include <avr/interrupt.h>
#include "timer.h"

volatile uint16_t TimerTick = 0;

ISR(TIMER0_OVF_vect)
{
    TimerTick++;
    // Tick always should be positive, but less than 32768, snprintf limit
    if (TimerTick > INT16_MAX / 2)
    {
        TimerTick = 0;
    }
}

void timer_init(void)
{
	TCCR0A = 0;
	TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00);
	TIMSK0 = (1 << TOIE0); // overflow interrupt en
}
