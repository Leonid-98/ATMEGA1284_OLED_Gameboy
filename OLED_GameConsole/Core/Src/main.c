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

#include "dino.h"

void run_debug_screen(void);
void init_random_seed(void);
uint8_t get_random_val(uint8_t n);

#define DINO_WIDTH 25
#define DINO_HEIGHT 26
#define DINO_INIT_X 10 // Dino initial spawn location
#define DINO_INIT_Y 29 // Dino initial spawn location

#define BASE_LINE_X 0
#define BASE_LINE_Y 54
#define BASE_LINE_X1 127
#define BASE_LINE_Y1 54

#define TREE1_WIDTH 11
#define TREE1_HEIGHT 23
#define TREE2_WIDTH 22
#define TREE2_HEIGHT 23
#define TREE_Y 35
#define JUMP_PIXEL 22 // Number of pixel dino will jump

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

void game_showMainMenu()
{
	ssd1306_SetCursor(MENU_LINE_X, MENU_LINE0_Y);
	ssd1306_WriteString("Dino Game", Font_11x18, White);

	ssd1306_SetCursor(MENU_LINE_X, MENU_LINE1_Y);
	ssd1306_WriteString("Play", Font_7x10, White);
	ssd1306_SetCursor(MENU_LINE_X, MENU_LINE2_Y);
	ssd1306_WriteString("Difficulty: 1/3", Font_7x10, White);
	ssd1306_SetCursor(MENU_LINE_X, MENU_LINE3_Y);
	ssd1306_WriteString("Debug", Font_7x10, White);
}

void introMessage()
{
	ssd1306_SetCursor(MENU_LINE_X, MENU_LINE0_Y);
	ssd1306_WriteString("Dino Game", Font_11x18, White);

	ssd1306_SetCursor(MENU_LINE_X, MENU_LINE1_Y);
	ssd1306_WriteString("Play", Font_7x10, White);
	ssd1306_SetCursor(MENU_LINE_X, MENU_LINE2_Y);
	ssd1306_WriteString("Difficulty: 1/3", Font_7x10, White);
	ssd1306_SetCursor(MENU_LINE_X, MENU_LINE3_Y);
	ssd1306_WriteString("Debug", Font_7x10, White);
}

int main(void)
{
	ENABLE_DEBUG_LED;
	timer_init();
	joystick_init();
	init_random_seed();
	button_init();
	ssd1306_Init();
	buttons_updateAll();

	sei();

	// ssd1306_DrawBitmap(10, 10, dino1, 25, 26, White);
	// ssd1306_DrawBitmap(50, 10, tree1, 11, 23, White);
	// ssd1306_DrawBitmap(100, 10, tree2, 22, 23, White);
	// game_showMainMenu();
	// sei();
	// ssd1306_Fill(Black);

	dino_gameloop(TimerTick);

	while (1)
	{
		//run_debug_screen();
	}

	return 0;
}

void run_debug_screen(void)
{
	static char buff0[20];
	static char buff1[20];
	static char buff2[20];
	static char buff3[20];

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

	ssd1306_FillCircle(10, 35, 5, White);
	ssd1306_FillCircle(25, 35, 5, White);
	ssd1306_FillCircle(25, 50, 5, White);
	ssd1306_FillCircle(10, 50, 5, White);

	(button_getState4() == Button_Down) ? ssd1306_FillCircle(10, 35, 4, White) : ssd1306_FillCircle(10, 35, 4, Black);
	(button_getState3() == Button_Down) ? ssd1306_FillCircle(25, 35, 4, White) : ssd1306_FillCircle(25, 35, 4, Black);
	(button_getState2() == Button_Down) ? ssd1306_FillCircle(10, 50, 4, White) : ssd1306_FillCircle(10, 50, 4, Black);
	(button_getState1() == Button_Down) ? ssd1306_FillCircle(25, 50, 4, White) : ssd1306_FillCircle(25, 50, 4, Black);

	ssd1306_UpdateScreen();
}

void init_random_seed(void)
{
	srand(joystcik_getY());
}

uint8_t get_random_val(uint8_t n)
{
	return rand() % (n + 1);
}