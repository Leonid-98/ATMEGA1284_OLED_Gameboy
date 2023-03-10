/*
 * joystick.h
 *
 * Created: 16.01.2023 4:07:41
 *  Author: Leonid Tsigrinski
 */ 


#ifndef JOYSTCIK_H_
#define JOYSTCIK_H_

#include <stdint.h>

#define JOYSTICK_Y_MAX				990
#define JOYSTICK_CENTER				480
#define JOYSTICK_CENTER_OFFSET		250

void joystick_init(void);
uint16_t joystcik_getX(void);
uint16_t joystcik_getY(void);

#endif /* JOYSTCIK_H_ */