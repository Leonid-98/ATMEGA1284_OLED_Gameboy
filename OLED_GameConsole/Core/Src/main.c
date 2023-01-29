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
#include "timer_tick.h"
#include "random.h"
#include "button.h"
#include "ssd1306.h"
#include "joystcik.h"
#include "buzzer.h"

#include "game.h"
#include "dino.h"
#include "pong.h"
#include "snake.h"

void debug_mainloop(void);

int main(void)
{
	// ENABLE_DEBUG_LED;
	timer0_init();
	joystick_init();
	random_init();
	button_init();
	ssd1306_Init();
	buzzer_init();
	sei();
	buttons_updateAll();

	game_selected_e selected_game;
	while (true)
	{
		selected_game = game_mainMenuLoop();
		switch (selected_game)
		{
		case Game_Dino:
			dino_gameloop();
			break;
		case Game_Snake:
			snake_gameloop();
			break;
		case Game_Pong:
			pong_gameloop();
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
	while (true)
	{
		buttons_updateAll();

		snprintf(buff0, 20, "Joy x: %d   ", joystcik_getX());
		ssd1306_SetCursor(0, 2);
		ssd1306_WriteString(buff0, Font_6x8, White);

		snprintf(buff1, 20, "Joy y: %d   ", joystcik_getY());
		ssd1306_SetCursor(0, 12);
		ssd1306_WriteString(buff1, Font_6x8, White);

		snprintf(buff2, 20, "Random: %d   ", random_randint(0, 128));
		ssd1306_SetCursor(64, 2);
		ssd1306_WriteString(buff2, Font_6x8, White);

		snprintf(buff3, 20, "Tick: %d   ", TimerTick);
		ssd1306_SetCursor(64, 12);
		ssd1306_WriteString(buff3, Font_6x8, White);

		ssd1306_SetCursor(37, 45);
		ssd1306_WriteString("Score CLR: A+B", Font_6x8, White);
		ssd1306_SetCursor(37, 55);
		ssd1306_WriteString("Exit: UP + DOWN", Font_6x8, White);

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
