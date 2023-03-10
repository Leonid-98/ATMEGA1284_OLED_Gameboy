/*
 * joystick.c
 *
 * Created: 16.01.2023 4:08:09
 *  Author: msi
 */ 

#include "joystcik.h"
#include "adc.h"

void joystick_init(void)
{
	adc_init();
}

uint16_t joystcik_getX(void)
{
	return adc_read(MUX0);
}

uint16_t joystcik_getY(void)
{
	return JOYSTICK_Y_MAX - adc_read(MUX1);
}