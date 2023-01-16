/*
 * adc.h
 *
 *  Author: Leonid T?igrinski
 */

#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adc_init();
uint16_t adc_read(uint8_t MUXn);

#endif /* ADC_H_ */