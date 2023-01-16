/*
 * main.c
 *
 *  Author: Leonid T?igrinski
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "main.h"
#include "button.h"
#include "ssd1306.h"
#include "joystcik.h"

void debug_testAll(void);

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

static const uint8_t dino1[]={
	// 'dino', 25x26px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x0e, 0xff, 0x00,
	0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xc0, 0x00,
	0x00, 0x0f, 0xfc, 0x00, 0x40, 0x0f, 0xc0, 0x00, 0x40, 0x1f, 0x80, 0x00, 0x40, 0x7f, 0x80, 0x00,
	0x60, 0xff, 0xe0, 0x00, 0x71, 0xff, 0xa0, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xff, 0x80, 0x00,
	0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00,
	0x03, 0xfc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00,
	0x01, 0x0c, 0x00, 0x00, 0x01, 0x8e, 0x00, 0x00
};

static const uint8_t tree1[]={
	// 'tree1', 11x23px
	0x1e, 0x00, 0x1f, 0x00, 0x1f, 0x40, 0x1f, 0xe0, 0x1f, 0xe0, 0xdf, 0xe0, 0xff, 0xe0, 0xff, 0xe0,
	0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xc0, 0xff, 0x00, 0xff, 0x00, 0x7f, 0x00,
	0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00
};

static const uint8_t tree2[]={
	// 'tree2', 22x23px
	0x1e, 0x01, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x4f, 0xe8, 0x1f, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0xdf,
	0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff,
	0xfc, 0xff, 0xef, 0xfc, 0xff, 0x83, 0xfc, 0xff, 0x03, 0xfc, 0xff, 0x03, 0xf8, 0x7f, 0x03, 0xe0,
	0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f,
	0x03, 0xe0, 0x1f, 0x03, 0xe0
};


#define MENU_LINE_X				5
#define MENU_LINE0_Y			3		
#define MENU_LINE1_Y			24	
#define MENU_LINE2_Y			38	
#define MENU_LINE3_Y			51	

#define SELECTOR_X_START		3
#define SELECTOR_X_END			125

#define SELECTOR_LINE1_Y_START	22
#define SELECTOR_LINE1_Y_END	34
#define SELECTOR_LINE2_Y_START	35
#define SELECTOR_LINE2_Y_END	48
#define SELECTOR_LINE3_Y_START	49
#define SELECTOR_LINE3_Y_END	62

	
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

void game_showSelector(uint8_t line, SSD1306_COLOR color)
{
	if (line == 1)
	{
		ssd1306_DrawRectangle(SELECTOR_X_START, SELECTOR_LINE1_Y_START, SELECTOR_X_END, SELECTOR_LINE1_Y_END, color);
		
	} 
	else if (line == 2)
	{
		ssd1306_DrawRectangle(SELECTOR_X_START, SELECTOR_LINE2_Y_START, SELECTOR_X_END, SELECTOR_LINE2_Y_END, color);
	}
	else if (line == 3)
	{
		ssd1306_DrawRectangle(SELECTOR_X_START, SELECTOR_LINE3_Y_START, SELECTOR_X_END, SELECTOR_LINE3_Y_END, color);
	}
}

int main(void)
{
	ENABLE_DEBUG_LED;
	joystick_init();
	button_init();
	ssd1306_Init();
	ssd1306_Fill(Black);
	
	//ssd1306_DrawBitmap(10, 10, dino1, 25, 26, White);
	//ssd1306_DrawBitmap(50, 10, tree1, 11, 23, White);
	//ssd1306_DrawBitmap(100, 10, tree2, 22, 23, White);
	
	
	
	game_showMainMenu();
	game_showSelector(3, White);
	
	//sei();
		
	while (1)
	{
		
		

		//debug_testAll();
		
		
		ssd1306_UpdateScreen();
	}
	

	return 0;
}

void debug_testAll(void)
{
	static char buff0[50];
	static char buff1[50];
	
	buttons_updateAll();
	
	uint16_t adc0 = joystcik_getX();
	
	snprintf(buff0, 50, "Joy x: %d   ", adc0);
	ssd1306_SetCursor(2, 2);
	ssd1306_WriteString(buff0, Font_6x8, White);
	
	uint16_t adc1 = joystcik_getY();
	
	snprintf(buff1, 50, "Joy y: %d   ", adc1);
	ssd1306_SetCursor(2, 12);
	ssd1306_WriteString(buff1, Font_6x8, White);

	ssd1306_FillCircle(16, 45, 5, White);
	ssd1306_FillCircle(48, 45, 5, White);
	ssd1306_FillCircle(80, 45, 5, White);
	ssd1306_FillCircle(112, 45, 5, White);
	
	
	
	if (button_getState1() == Button_Down)
	{
		ssd1306_FillCircle(16, 45, 4, White);
	}
	else
	{
		ssd1306_FillCircle(16, 45, 4, Black);
	}
	
	if (button_getState2() == Button_Down)
	{
		ssd1306_FillCircle(48, 45, 4, White);
	}
	else
	{
		ssd1306_FillCircle(48, 45, 4, Black);
	}
	
	if (button_getState3() == Button_Down)
	{
		ssd1306_FillCircle(80, 45, 4, White);
	}
	else
	{
		ssd1306_FillCircle(80, 45, 4, Black);
	}
	
	if (button_getState4() == Button_Down)
	{
		ssd1306_FillCircle(112, 45, 4, White);
	}
	else
	{
		ssd1306_FillCircle(112, 45, 4, Black);
	}
	
	ssd1306_UpdateScreen();
}