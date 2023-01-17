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
#include "button.h"
#include "ssd1306.h"
#include "joystcik.h"

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


typedef int16_t int16_pos;

volatile int16_pos TimerTick;
ISR(TIMER0_OVF_vect)
{
	TimerTick++;
	// Tick always should be positive, but less than 32768, it's snprintf limit
	if (TimerTick > INT16_MAX / 2) 
	{
		TimerTick = 0; 
	}
}

static const uint8_t dino1[] = {
	// 'dino', 25x26px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x0e, 0xff, 0x00,
	0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xc0, 0x00,
	0x00, 0x0f, 0xfc, 0x00, 0x40, 0x0f, 0xc0, 0x00, 0x40, 0x1f, 0x80, 0x00, 0x40, 0x7f, 0x80, 0x00,
	0x60, 0xff, 0xe0, 0x00, 0x71, 0xff, 0xa0, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xff, 0x80, 0x00,
	0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00,
	0x03, 0xfc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00,
	0x01, 0x0c, 0x00, 0x00, 0x01, 0x8e, 0x00, 0x00};

static const uint8_t tree1[] = {
	// 'tree1', 11x23px
	0x1e, 0x00, 0x1f, 0x00, 0x1f, 0x40, 0x1f, 0xe0, 0x1f, 0xe0, 0xdf, 0xe0, 0xff, 0xe0, 0xff, 0xe0,
	0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xe0, 0xff, 0xc0, 0xff, 0x00, 0xff, 0x00, 0x7f, 0x00,
	0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00, 0x1f, 0x00};

static const uint8_t tree2[] = {
	// 'tree2', 22x23px
	0x1e, 0x01, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x4f, 0xe8, 0x1f, 0xff, 0xfc, 0x1f, 0xff, 0xfc, 0xdf,
	0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff, 0xfc, 0xff, 0xff,
	0xfc, 0xff, 0xef, 0xfc, 0xff, 0x83, 0xfc, 0xff, 0x03, 0xfc, 0xff, 0x03, 0xf8, 0x7f, 0x03, 0xe0,
	0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f, 0x03, 0xe0, 0x1f,
	0x03, 0xe0, 0x1f, 0x03, 0xe0};

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

// #########################
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
// ##########################

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

// Move dino function
void moveDino(int16_t y)
{
	ssd1306_DrawBitmap(DINO_INIT_X, y, dino1, DINO_WIDTH, DINO_HEIGHT, White);
}

// Move tree funciton
void moveTree(int16_t x, uint8_t type)
{
	if (type == 0)
	{
		ssd1306_DrawBitmap(x, TREE_Y, tree1, TREE1_WIDTH, TREE1_HEIGHT, White);
	}
	else if (type == 1)
	{
		ssd1306_DrawBitmap(x, TREE_Y, tree2, TREE2_WIDTH, TREE2_HEIGHT, White);
	}
}

// Game over display with score
void gameOver(int16_t score)
{
	while (!(
	button_getState1() == Button_Falling ||
	button_getState2() == Button_Falling ||
	button_getState3() == Button_Falling ||
	button_getState4() == Button_Falling
	)) {
		buttons_updateAll();
		};
	// display.clearDisplay();

	// display.setTextSize(2); // Draw 2X-scale text
	// display.setTextColor(SSD1306_WHITE);
	// display.setCursor(10, 5);
	// display.println("Game Over");

	// display.setTextSize(1);

	// display.setCursor(10, 30);
	// display.print("Score: ");
	// display.print(score);

	// display.setCursor(1, 45);
	// display.println("Enter 1 To Play Again");

	// display.display();
}

// Display score while running the game
void displayScore(int16_pos score)
{
	static char buff[20];

	snprintf(buff, 20, "Score: %d    ", score); // TODO score
	ssd1306_SetCursor(50, 10);
	ssd1306_WriteString(buff, Font_6x8, White);
}

// Main play function
void play()
{

	int16_t tree_x = 127;
	int16_t tree1_x = 195;
	uint8_t tree_type = get_random_val(1);
	uint8_t tree_type1 = get_random_val(1);

	int16_t dino_y = DINO_INIT_Y;
	uint8_t input_command;
	uint8_t jump = 0;

	int16_pos score = 0;

	for (;;)
	{
		buttons_updateAll();
		ssd1306_Fill(Black);
		score = TimerTick;

		if (button_getState4() == Button_Falling && jump == 0)
		{
				jump = 1;
		}

		if (jump == 1)
		{
			dino_y--;
			if (dino_y == (DINO_INIT_Y - JUMP_PIXEL))
			{
				jump = 2;
			}
		}
		else if (jump == 2)
		{
			dino_y++;
			if (dino_y == DINO_INIT_Y)
			{
				jump = 0;
			}
		}
		
		if (tree_x <= (DINO_INIT_X + DINO_WIDTH) && tree_x >= (DINO_INIT_X + (DINO_WIDTH / 2)))
		{
			if (dino_y >= (DINO_INIT_Y - 3))
			{
				// Collision Happened
				break;
			}
		}

		if (tree1_x <= (DINO_INIT_X + DINO_WIDTH) && tree1_x >= (DINO_INIT_X + (DINO_WIDTH / 2)))
		{
			if (dino_y >= (DINO_INIT_Y - 3))
			{
				// Collision Happened
				break;
			}
		}

		displayScore(score);
		moveTree(tree_x, tree_type);
		moveTree(tree1_x, tree_type1);
		moveDino(dino_y);
		// display.drawLine(0, 54, 127, 54, SSD1306_WHITE); TODO CHECK WHAT IS THIS
		//ssd1306_DrawRectangle(0, 54, 128, 54, White);

		tree_x--;
		tree1_x--;
		if (tree_x == 0)
		{
			tree_x = 127;
			tree_type = get_random_val(1);
		}

		if (tree1_x == 0)
		{
			tree1_x = 195;
			tree_type1 = get_random_val(1);
		}
		ssd1306_UpdateScreen();
	}
	gameOver(score);
}

void renderScene(int16_t i)
{

	ssd1306_DrawBitmap(10, 29, dino1, 25, 26, White);
	ssd1306_DrawBitmap(50, TREE_Y, tree1, 11, 23, White);
	ssd1306_DrawBitmap(100, TREE_Y, tree2, 22, 23, White);
	// display.drawLine(0, 54, 127, 54, White); TODO test this as well
	// display.drawPixel(i, 60, White);
}

int main(void)
{
	ENABLE_DEBUG_LED;
	joystick_init();
	button_init();
	ssd1306_Init();
	buttons_updateAll();
	
	// fast timer to show 7SEG numbers
	TCCR0A = 0;
	TCCR0B = (1 << CS02) | (0 << CS01) | (1 << CS00);
	TIMSK0 = (1 << TOIE0); // overflow interrupt en
	
	sei();
	
	// ssd1306_DrawBitmap(10, 10, dino1, 25, 26, White);
	// ssd1306_DrawBitmap(50, 10, tree1, 11, 23, White);
	// ssd1306_DrawBitmap(100, 10, tree2, 22, 23, White);
	// game_showMainMenu();
	// sei();
	// ssd1306_Fill(Black);
	play();
	while (1)
	{
	}

	return 0;
}

void run_debug_screen(void)
{
	static char buff0[50];
	static char buff1[50];
	static char buff3[50];

	buttons_updateAll();

	snprintf(buff0, 50, "Joy x: %d   ", joystcik_getX());
	ssd1306_SetCursor(0, 2);
	ssd1306_WriteString(buff0, Font_6x8, White);

	snprintf(buff1, 50, "Joy y: %d   ", joystcik_getY());
	ssd1306_SetCursor(0, 12);
	ssd1306_WriteString(buff1, Font_6x8, White);

	snprintf(buff3, 50, "Random: %d   ", get_random_val(10));
	ssd1306_SetCursor(64, 2);
	ssd1306_WriteString(buff3, Font_6x8, White);

	ssd1306_FillCircle(56, 35, 5, White);
	ssd1306_FillCircle(71, 35, 5, White);
	ssd1306_FillCircle(71, 50, 5, White);
	ssd1306_FillCircle(56, 50, 5, White);

	if (button_getState4() == Button_Down)
	{
		ssd1306_FillCircle(56, 35, 4, White);
	}
	else
	{
		ssd1306_FillCircle(56, 35, 4, Black);
	}

	if (button_getState3() == Button_Down)
	{
		ssd1306_FillCircle(71, 35, 4, White);
	}
	else
	{
		ssd1306_FillCircle(71, 35, 4, Black);
	}

	if (button_getState2() == Button_Down)
	{
		ssd1306_FillCircle(56, 50, 4, White);
	}
	else
	{
		ssd1306_FillCircle(56, 50, 4, Black);
	}

	if (button_getState1() == Button_Down)
	{
		ssd1306_FillCircle(71, 50, 4, White);
	}
	else
	{
		ssd1306_FillCircle(71, 50, 4, Black);
	}

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