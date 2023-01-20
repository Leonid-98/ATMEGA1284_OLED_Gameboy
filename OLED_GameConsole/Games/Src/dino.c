/*
 * dino.c
 *
 * Created: 20.01.2023 03:41:12
 *  Author: kotse
 */ 

#include "dino.h"
#include "button.h"
#include "ssd1306.h"

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
void gameOver(uint16_t score)
{
	ssd1306_Fill(Black);
	static char buff[20];
	snprintf(buff, 20, "Score: %d    ", score); // TODO score
	ssd1306_SetCursor(50, 10);
	ssd1306_WriteString(buff, Font_6x8, White);
	ssd1306_UpdateScreen();
	while (!(
	button_getState1() == Button_Falling ||
	button_getState2() == Button_Falling ||
	button_getState3() == Button_Falling ||
	button_getState4() == Button_Falling))
	{
		buttons_updateAll();
	};
	

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


void renderScene(int16_t i)
{

	ssd1306_DrawBitmap(10, 29, dino1, 25, 26, White);
	ssd1306_DrawBitmap(50, TREE_Y, tree1, 11, 23, White);
	ssd1306_DrawBitmap(100, TREE_Y, tree2, 22, 23, White);
	// display.drawLine(0, 54, 127, 54, White); TODO test this as well
	// display.drawPixel(i, 60, White);
}


void displayScore(uint16_t score)
{
	static char buff[20];

	snprintf(buff, 20, "Score: %d    ", score); // TODO score
	ssd1306_SetCursor(50, 10);
	ssd1306_WriteString(buff, Font_6x8, White);
}

void dino_gameloop(uint16_t timer_tick)
{
	while (1)
	{
	int16_t tree_x = 127;
	int16_t tree1_x = 195;
	uint8_t tree_type = get_random_val(1);
	uint8_t tree_type1 = get_random_val(1);

	int16_t dino_y = DINO_INIT_Y;
	uint8_t input_command;
	uint8_t jump = 0;

	uint16_t score = 0;

	
		while (1)
		{
			buttons_updateAll();
			ssd1306_Fill(Black);
			score = timer_tick;

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
			// ssd1306_DrawRectangle(0, 54, 128, 54, White);

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
}

