/*
 * dino.c
 *
 * Created: 20.01.2023 03:41:12
 *  Author: kotse
 */

#include "game.h"
#include "dino.h"
#include "timer.h"
#include "button.h"
#include "ssd1306.h"

static const uint8_t dino_bmp[] = {
	// 'dino', 25x26px
	0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfe, 0x00, 0x00, 0x06, 0xff, 0x00, 0x00, 0x0e, 0xff, 0x00,
	0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x00, 0x0f, 0xc0, 0x00,
	0x00, 0x0f, 0xfc, 0x00, 0x40, 0x0f, 0xc0, 0x00, 0x40, 0x1f, 0x80, 0x00, 0x40, 0x7f, 0x80, 0x00,
	0x60, 0xff, 0xe0, 0x00, 0x71, 0xff, 0xa0, 0x00, 0x7f, 0xff, 0x80, 0x00, 0x7f, 0xff, 0x80, 0x00,
	0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00,
	0x03, 0xfc, 0x00, 0x00, 0x01, 0xdc, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00, 0x01, 0x8c, 0x00, 0x00,
	0x01, 0x0c, 0x00, 0x00, 0x01, 0x8e, 0x00, 0x00};

static const uint8_t tree1_bmp[] = {
	// 'tree1', 11x23px
	0x04, 0x00, 0x0e, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00, 0x0f, 0x00,
	0x0f, 0x00, 0x4e, 0x00, 0xee, 0x00, 0xee, 0x60, 0xee, 0xe0, 0xee, 0xe0, 0xee, 0xe0, 0xfe, 0xe0,
	0x7f, 0xc0, 0x3f, 0x80, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00, 0x0e, 0x00};

static const uint8_t tree2_bmp[] = {
	// 'tree2', 15x23px
	0x03, 0x80, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc6, 0x67, 0xce, 0xf7, 0xce, 0xf7, 0xce, 0xf7, 0xce,
	0xf7, 0xce, 0xf7, 0xce, 0xf7, 0xce, 0xf7, 0xde, 0xf7, 0xfe, 0xff, 0xfc, 0x7f, 0xf8, 0x3f, 0xc0,
	0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x07, 0xc0, 0x0f, 0xc0};

void dino_moveDino(int16_t y)
{
	ssd1306_DrawBitmap(DINO_SPAWN_X, y, dino_bmp, DINO_WIDTH, DINO_HEIGHT, White);
}

void dino_moveTree(int16_t x, uint8_t type)
{
	if (type == 0)
	{
		ssd1306_DrawBitmap(x, TREE_Y, tree1_bmp, TREE1_WIDTH, TREE1_HEIGHT, White);
	}
	else if (type == 1)
	{
		ssd1306_DrawBitmap(x, TREE_Y, tree2_bmp, TREE2_WIDTH, TREE2_HEIGHT, White);
	}
}

void dino_displayScore(uint16_t score)
{
	static char buff[20];

	snprintf(buff, 20, "Score: %d    ", score); // TODO score
	ssd1306_SetCursor(50, 10);
	ssd1306_WriteString(buff, Font_6x8, White);
}

void dino_gameloop()
{

	dino_object_st dino;
	dino.bitmap = dino_bmp;
	dino.width = DINO_WIDTH;
	dino.height = DINO_HEIGHT;
	dino.x = DINO_SPAWN_X;
	dino.y = DINO_SPAWN_Y;

	dino_object_st tree1;
	dino.bitmap = tree1_bmp;
	dino.width = TREE1_WIDTH;
	dino.height = TREE1_HEIGHT;
	dino.x = TREE1_SPAWN_X;
	dino.y = TREE_Y;

	dino_object_st tree2;
	dino.bitmap = tree2_bmp;
	dino.width = TREE2_WIDTH;
	dino.height = TREE2_HEIGHT;
	dino.x = TREE2_SPAWN_X;
	dino.y = TREE_Y;

	int16_t tree1_x = TREE1_SPAWN_X; // TODO get rid of that variables
	int16_t tree2_x = TREE2_SPAWN_X;
	uint8_t tree1_type = get_random_val(1);
	uint8_t tree2_type = get_random_val(1);

	uint8_t dino_state = Dino_Running;

	uint16_t score = 0;
	TimerTick = 0;
	while (1)
	{
		buttons_updateAll();
		ssd1306_Fill(Black);
		score = TimerTick;

		if (button_getState4() == Button_Falling && dino_state == Dino_Running)
		{
			dino_state = Dino_Jumping;
		}

		if (dino_state == Dino_Jumping)
		{
			dino.y--; // 0 is top of the OLED
			if (dino.y == (DINO_SPAWN_Y - DINO_JUMP_HEIGHT))
			{
				dino_state = Dino_Falling;
			}
		}
		else if (dino_state == Dino_Falling)
		{
			dino.y++;
			if (dino.y == DINO_SPAWN_Y)
			{
				dino_state = 0;
			}
		}

		if (tree1_x <= (DINO_SPAWN_X + DINO_WIDTH) && tree1_x >= (DINO_SPAWN_X + (DINO_WIDTH / 2)))
		{
			if (dino.y >= (DINO_SPAWN_Y - 3))
			{
				// Collision Happened
				break;
			}
		}

		if (tree2_x <= (DINO_SPAWN_X + DINO_WIDTH) && tree2_x >= (DINO_SPAWN_X + (DINO_WIDTH / 2)))
		{
			if (dino.y >= (DINO_SPAWN_Y - 3))
			{
				// Collision Happened
				break;
			}
		}

		dino_displayScore(score);
		dino_moveTree(tree1_x, tree1_type);
		dino_moveTree(tree2_x, tree2_type);
		dino_moveDino(dino.y);

		// display.drawLine(0, 54, 127, 54, SSD1306_WHITE); TODO CHECK WHAT IS THIS
		// ssd1306_DrawRectangle(0, 54, 128, 54, White);

		tree1_x--;
		tree2_x--;
		if (tree1_x == 0)
		{
			tree1_x = TREE1_SPAWN_X;
			tree1_type = get_random_val(1);
		}

		if (tree2_x == 0)
		{
			tree2_x = TREE2_SPAWN_X;
			tree2_type = get_random_val(1);
		}
		ssd1306_UpdateScreen();
	}
	game_over(score, Game_Dino);
}
