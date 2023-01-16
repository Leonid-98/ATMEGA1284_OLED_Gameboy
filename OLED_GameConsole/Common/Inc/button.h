/*
 * button.h
 *
 *  Author: Leonid T?igrinski
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <avr/io.h>

#define BUTTON_DDR DDRA
#define BUTTON_PORT PORTA
#define BUTTON_PIN PINA

#define BUTTON_1_PIN 5
#define BUTTON_2_PIN 4
#define BUTTON_3_PIN 7
#define BUTTON_4_PIN 6

typedef enum
{
	Active = 0,
	Not_Active = 1,
} pin_state_e;

typedef enum
{
	Button_Up,
	Button_Rising,
	Button_Falling,
	Button_Down,
} button_state_e;

typedef struct
{
	uint16_t pin;
	pin_state_e curr_pin_state;
	pin_state_e prev_pin_state;
	button_state_e state;
} button_st;

void button_init();
void buttons_updateAll();
button_state_e button_getState1();
button_state_e button_getState2();
button_state_e button_getState3();
button_state_e button_getState4();

#endif /* BUTTON_H_ */