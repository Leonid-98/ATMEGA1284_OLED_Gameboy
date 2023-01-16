/*
 * button.c
 *
 *  Author: Leonid T?igrinski
 */

#include "button.h"

void priv_updateGivenButton(button_st *button);

button_st button_1 = {
	.pin = BUTTON_1_PIN,
	.curr_pin_state = Not_Active,
	.prev_pin_state = Not_Active,
	.state = Button_Falling};

button_st button_2 = {
	.pin = BUTTON_2_PIN,
	.curr_pin_state = Not_Active,
	.prev_pin_state = Not_Active,
	.state = Button_Falling};

button_st button_3 = {
	.pin = BUTTON_3_PIN,
	.curr_pin_state = Not_Active,
	.prev_pin_state = Not_Active,
	.state = Button_Falling};

button_st button_4 = {
	.pin = BUTTON_4_PIN,
	.curr_pin_state = Not_Active,
	.prev_pin_state = Not_Active,
	.state = Button_Falling};

void button_init()
{
	BUTTON_DDR &= !(0 << BUTTON_1_PIN | 0 << BUTTON_2_PIN | 0 << BUTTON_3_PIN | 0 << BUTTON_4_PIN);
	BUTTON_PORT |= 1 << BUTTON_1_PIN | 1 << BUTTON_2_PIN | 1 << BUTTON_3_PIN | 1 << BUTTON_4_PIN;
}

void buttons_updateAll()
{
	priv_updateGivenButton(&button_1);
	priv_updateGivenButton(&button_2);
	priv_updateGivenButton(&button_3);
	priv_updateGivenButton(&button_4);
}

button_state_e button_getState1()
{
	return button_1.state;
}

button_state_e button_getState2()
{
	return button_2.state;
}

button_state_e button_getState3()
{
	return button_3.state;
}

button_state_e button_getState4()
{
	return button_4.state;
}

void priv_updateGivenButton(button_st *button)
{
	button->curr_pin_state = (BUTTON_PIN & (1 << button->pin)) >> button->pin;

	if ((button->curr_pin_state == Not_Active) && (button->prev_pin_state == Not_Active))
	{
		button->state = Button_Up;
	}
	else if ((button->curr_pin_state == Active) && (button->prev_pin_state == Not_Active))
	{
		button->state = Button_Falling;
	}
	else if ((button->curr_pin_state == Active) && (button->prev_pin_state == Active))
	{
		button->state = Button_Down;
	}
	else if ((button->curr_pin_state == Not_Active) && (button->prev_pin_state == Active))
	{
		button->state = Button_Rising;
	}

	button->prev_pin_state = button->curr_pin_state;
}
