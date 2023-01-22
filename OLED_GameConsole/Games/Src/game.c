/*
 * game.c
 *
 * Created: 22.01.2023 3:22:14
 *  Author: msi
 */

#include <stdint.h>

#include <avr/eeprom.h>

#include "button.h"
#include "ssd1306.h"
#include "game.h"

void game_writeScore(uint16_t new_score, uint8_t game)
{
	switch (game)
	{
	case Game_Dino:
		eeprom_write_word(GAME_DINO_ADDR, new_score);
		break;
	case Game_Snake:
		eeprom_write_word(GAME_SNAKE_ADDR, new_score);
		break;
	case Game_Pong:
		eeprom_write_word(GAME_PONG_ADDR, new_score);
		break;
	default:
		break;
	}
}

uint16_t game_readScore(uint8_t game)
{
	switch (game)
	{
	case Game_Dino:
		return eeprom_read_word(GAME_DINO_ADDR);
	case Game_Snake:
		return eeprom_read_word(GAME_SNAKE_ADDR);
	case Game_Pong:
		return eeprom_read_word(GAME_PONG_ADDR);
	default:
		return 1;
	}
}

void game_clearAllScores(void)
{
	eeprom_write_word(GAME_DINO_ADDR, 0);
	eeprom_write_word(GAME_SNAKE_ADDR, 0);
	eeprom_write_word(GAME_PONG_ADDR, 0);
}

void game_drawMainMenu()
{
	ssd1306_SetCursor(0, 0);
	ssd1306_WriteString("Select game:", Font_11x18, White);

	ssd1306_SetCursor(10, 20);
	ssd1306_WriteString("Dino", Font_7x10, White);
	ssd1306_SetCursor(10, 30);
	ssd1306_WriteString("Snake", Font_7x10, White);
	ssd1306_SetCursor(10, 40);
	ssd1306_WriteString("Pong", Font_7x10, White);
	ssd1306_SetCursor(10, 50);
	ssd1306_WriteString("Debug", Font_7x10, White);
}

void game_drawSelector(game_selected_e selected_game)
{
	ssd1306_FillCircle(4, 24, 2, Black);
	ssd1306_FillCircle(4, 34, 2, Black);
	ssd1306_FillCircle(4, 44, 2, Black);
	ssd1306_FillCircle(4, 54, 2, Black);
	switch (selected_game)
	{
	case Game_Dino:
		ssd1306_FillCircle(4, 24, 2, White);
		break;
	case Game_Snake:
		ssd1306_FillCircle(4, 34, 2, White);
		break;
	case Game_Pong:
		ssd1306_FillCircle(4, 44, 2, White);
		break;
	case Game_Debug:
		ssd1306_FillCircle(4, 54, 2, White);
		break;
	default:
		break;
	}
}

game_selected_e game_mainMenuLoop()
{
	game_selected_e selected_game = Game_Dino;

	ssd1306_Fill(Black);
	game_drawMainMenu();
	while (1)
	{
		buttons_updateAll();

		if (button_getState3() == Button_Falling) // TODO define macro for button i.e. BUTTON_A
		{
			if (selected_game != Game_Debug) // Last game
			{
				selected_game++;
			}
		}

		if (button_getState1() == Button_Falling)
		{
			if (selected_game != Game_Dino) // First game
			{
				selected_game--;
			}
		}

		if (button_getState4() == Button_Falling)
		{
			return selected_game;
		}

		game_drawSelector(selected_game);
		ssd1306_UpdateScreen();
	}
}
