/*
 * main.c
 *
 *  Author: Leonid T?igrinski
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "timer.h"
#include "button.h"
#include "ssd1306.h"
#include "joystcik.h"

#include "game.h"
#include "dino.h"

void debug_mainloop(void);
void init_random_seed(void);
uint8_t get_random_val(uint8_t n);

#define MENU_LINE_X 5
#define MENU_LINE0_Y 3
#define MENU_LINE1_Y 24
#define MENU_LINE2_Y 38
#define MENU_LINE3_Y 51

#define SELECTOR_X_START 3
#define SELECTOR_X_END 125

#define SELECTOR_LINE1_Y_START 22
#define SELECTOR_LINE1_Y_END 34
#define SELECTOR_LINE2_Y_START 35
#define SELECTOR_LINE2_Y_END 48
#define SELECTOR_LINE3_Y_START 49
#define SELECTOR_LINE3_Y_END 62

int main(void)
{
	// ENABLE_DEBUG_LED;
	timer_init();
	joystick_init();
	init_random_seed();
	button_init();
	ssd1306_Init();
	buttons_updateAll();
	sei();
	
	//// TODO debug remove
	//char buff[20];
	//uint16_t i = 0;
	//while (1)
	//{
		//snprintf(buff, 20, "i: %d   ", i++);
		//ssd1306_SetCursor(0, 32);
		//ssd1306_WriteString(buff, Font_16x26, White);
		//ssd1306_UpdateScreen();
//
	//}

	game_selected_e selected_game;
	while (1)
	{
		selected_game = game_mainMenuLoop();
		switch (selected_game)
		{
		case Game_Dino:
			dino_gameloop();
			break;
		case Game_Snake:
			ssd1306_FillCircle(4, 34, 2, White);
			break;
		case Game_Pong:
			ssd1306_FillCircle(4, 44, 2, White);
			break;
		case Game_Debug:
			debug_mainloop();
			break;
		default:
			break;
		}
	}

	return 0;
}

void debug_mainloop(void)
{
	static char buff0[20];
	static char buff1[20];
	static char buff2[20];
	static char buff3[20];

	ssd1306_Fill(Black);
	while (1)
	{
		buttons_updateAll();

		snprintf(buff0, 20, "Joy x: %d   ", joystcik_getX());
		ssd1306_SetCursor(0, 2);
		ssd1306_WriteString(buff0, Font_6x8, White);

		snprintf(buff1, 20, "Joy y: %d   ", joystcik_getY());
		ssd1306_SetCursor(0, 12);
		ssd1306_WriteString(buff1, Font_6x8, White);

		snprintf(buff2, 20, "Random: %d   ", get_random_val(10));
		ssd1306_SetCursor(64, 2);
		ssd1306_WriteString(buff2, Font_6x8, White);

		snprintf(buff3, 20, "Tick: %d   ", TimerTick);
		ssd1306_SetCursor(64, 12);
		ssd1306_WriteString(buff3, Font_6x8, White);

		ssd1306_SetCursor(64, 50);
		ssd1306_WriteString("exit: A+B", Font_6x8, White);
		
		ssd1306_SetCursor(64, 30);
		ssd1306_WriteString("clr score:", Font_6x8, White);
		ssd1306_SetCursor(64, 40);
		ssd1306_WriteString("^ + v", Font_6x8, White);

		ssd1306_FillCircle(10, 35, 5, White);
		ssd1306_FillCircle(25, 35, 5, White);
		ssd1306_FillCircle(25, 50, 5, White);
		ssd1306_FillCircle(10, 50, 5, White);

		(button_getState1() == Button_Down) ? ssd1306_FillCircle(10, 35, 4, White) : ssd1306_FillCircle(10, 35, 4, Black);
		(button_getState2() == Button_Down) ? ssd1306_FillCircle(25, 35, 4, White) : ssd1306_FillCircle(25, 35, 4, Black);
		(button_getState3() == Button_Down) ? ssd1306_FillCircle(10, 50, 4, White) : ssd1306_FillCircle(10, 50, 4, Black);
		(button_getState4() == Button_Down) ? ssd1306_FillCircle(25, 50, 4, White) : ssd1306_FillCircle(25, 50, 4, Black);
		
		if (button_getState1() == Button_Down && button_getState3() == Button_Down)
		{
			game_clearAllScores();
		}
		
		
		if (button_getState2() == Button_Down && button_getState4() == Button_Down)
		{
			break;
		}

		ssd1306_UpdateScreen();
	}
}

void init_random_seed(void)
{
	srand(joystcik_getY());
}

uint8_t get_random_val(uint8_t n)
{
	return rand() % (n + 1);
}