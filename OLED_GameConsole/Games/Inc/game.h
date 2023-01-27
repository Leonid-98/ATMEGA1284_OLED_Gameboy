/*
 * game.h
 *
 * Created: 22.01.2023 3:22:01
 *  Author: Leonid Tsigrinski
 */

#ifndef GAME_H_
#define GAME_H_

#include <stdint.h>
#include <stdbool.h>

// EEPROM addresses (stores dword)
#define GAME_DINO_ADDR      (uint16_t *)0x00
#define GAME_SNAKE_ADDR     (uint16_t *)0x02
#define GAME_PONG_ADDR      (uint16_t *)0x04

#define GAME_SCORE_X0		56
#define GAME_SCORE_X1		51
#define GAME_SCORE_X2		46
#define GAME_SCORE_X3		41
#define GAME_SCORE_X4		36
#define GAME_SCORE_Y		27

typedef enum
{
    Game_Dino,
    Game_Snake,
    Game_Pong,
    Game_Debug
} game_selected_e;

// EEPROM
void game_writeScore(uint16_t new_score, uint8_t game);
uint16_t game_readScore(uint8_t game);
void game_clearAllScores(void);

void game_drawMainMenu(game_selected_e selected_game);
// void game_drawSelector(game_selected_e selected_game);
game_selected_e game_mainMenuLoop();
bool game_over(uint16_t score, uint8_t game);

extern const uint8_t game_over_bmp[];

#endif /* GAME_H_ */