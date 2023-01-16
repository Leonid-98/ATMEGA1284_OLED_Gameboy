/*
 * adc.c
 *
 *  Author: Leonid T?igrinski
 */

#include "adc.h"

void adc_init()
{
	ADCSRA = (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

uint16_t adc_read(uint8_t MUXn)
{
	ADMUX = (1 << REFS0) | (1 << MUXn);
	while (!(ADCSRA & (1 << ADIF)));
	return ADC;
}