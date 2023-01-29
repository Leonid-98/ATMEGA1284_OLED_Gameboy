/*
 * snake.h
 *
 * Created: 28.01.2023 23:52:01
 *  Author: Leonid Tsigrinski
 */

#ifndef SNAKE_H_
#define SNAKE_H_

#include <stdint.h>

#define SNAKE_SIZE 4

#define SNAKE_SPAWN_X 10
#define SNAKE_SPAWN_SIZE 3

enum snake_dir
{
    Snake_Left,
    Snake_Right,
    Snake_Up,
    Snake_Down
};

struct snake_st
{
    int16_t x[200];
    int16_t y[200];
    uint8_t size;
    enum snake_dir dir;
};

struct snake_food_st
{
    uint8_t x;
    uint8_t y;
};

void snake_gameloop(void);

#endif