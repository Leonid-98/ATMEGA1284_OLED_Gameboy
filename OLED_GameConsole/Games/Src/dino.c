/*
 * dino.c
 *
 * Created: 20.01.2023 03:41:12
 *  Author: Leonid Tsigrinski
 */
#include <stdio.h>

#include "game.h"
#include "dino.h"
#include "timer_tick.h"
#include "button.h"
#include "ssd1306.h"
#include "random.h"

static void priv_moveObject(struct dino_object_st *obj);
static void priv_displayScore(uint16_t score);

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

static void priv_moveObject(struct dino_object_st *obj)
{
	ssd1306_DrawBitmap(obj->x, obj->y, obj->bitmap, obj->width, obj->height, White);
}

static void priv_displayScore(uint16_t score)
{
	static char buff[20];

	snprintf(buff, 20, "Score: %d    ", score);
	ssd1306_SetCursor(50, 10);
	ssd1306_WriteString(buff, Font_6x8, White);
}

void dino_gameloop()
{
	while (true)
	{
		struct dino_object_st dino;
		dino.bitmap = dino_bmp;
		dino.width = DINO_WIDTH;
		dino.height = DINO_HEIGHT;
		dino.x = DINO_SPAWN_X;
		dino.y = DINO_SPAWN_Y;

		struct dino_object_st tree1;
		tree1.bitmap = tree1_bmp;
		tree1.width = TREE1_WIDTH;
		tree1.height = TREE1_HEIGHT;
		tree1.x = TREE1_SPAWN_X;
		tree1.y = TREE_Y;
		tree1.type = random_randint(0, 1);

		struct dino_object_st tree2;
		tree2.bitmap = tree2_bmp;
		tree2.width = TREE2_WIDTH;
		tree2.height = TREE2_HEIGHT;
		tree2.x = TREE2_SPAWN_X;
		tree2.y = TREE_Y;
		tree2.type = random_randint(0, 1);

		uint8_t dino_state = Dino_Running;

		uint16_t score = 0;
		TimerTick = 0;
		while (true)
		{
			buttons_updateAll();
			ssd1306_Fill(Black);
			score = TimerTick;

			if (BUTTON_UP_IS_PRESSED && dino_state == Dino_Running)
			{
				dino_state = Dino_Jumping;
			}

			if (dino_state == Dino_Jumping)
			{
				// 0 is top of the OLED
				dino.y--;
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

			if (tree1.x <= (DINO_SPAWN_X + DINO_WIDTH) && tree1.x >= (DINO_SPAWN_X + (DINO_WIDTH / 2)))
			{
				if (dino.y >= (DINO_SPAWN_Y - 3))
				{
					break;
				}
			}

			if (tree2.x <= (DINO_SPAWN_X + DINO_WIDTH) && tree2.x >= (DINO_SPAWN_X + (DINO_WIDTH / 2)))
			{
				if (dino.y >= (DINO_SPAWN_Y - 3))
				{
					break;
				}
			}

			priv_displayScore(score);
			priv_moveObject(&tree1);
			priv_moveObject(&tree2);
			priv_moveObject(&dino);

			tree1.x--;
			tree2.x--;
			if (tree1.x == 0)
			{
				tree1.x = TREE1_SPAWN_X;
				tree1.type = random_randint(0, 1);
			}

			if (tree2.x == 0)
			{
				tree2.x = TREE2_SPAWN_X;
				tree2.type = random_randint(0, 1);
			}
			ssd1306_UpdateScreen();
		}

		if (game_over(score, Game_Dino))
		{
			break;
		}
	}
}
