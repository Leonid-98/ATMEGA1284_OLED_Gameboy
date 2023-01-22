/*
 * dino.h
 *
 * Created: 20.01.2023 03:40:58
 *  Author: kotse
 */ 


#ifndef DINO_H_
#define DINO_H_

#include <stdint.h>

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

#define TREE2_WIDTH 15
#define TREE2_HEIGHT 23

#define TREE_Y 35

#define JUMP_PIXEL 22 // Number of pixel dino will jump

void dino_moveDino(int16_t y);
void dino_moveTree(int16_t x, uint8_t type);
void dino_gameOver(uint16_t score);
void dino_renderScene(int16_t i);
void dino_displayScore(uint16_t score);
void dino_gameloop();

#endif /* DINO_H_ */