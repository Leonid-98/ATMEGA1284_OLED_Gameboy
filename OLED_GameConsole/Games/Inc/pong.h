/*
 * pong.h
 *
 * Created: 28.01.2023 23:52:01
 *  Author: Leonid Tsigrinski
 */

#ifndef PONG_H_
#define PONG_H_

#include "ssd1306.h"
#include "stdbool.h"

#define PONG_FIELD_X0       5
#define PONG_FIELD_Y0       10
#define PONG_FIELD_X1       SSD1306_WIDTH - 6
#define PONG_FIELD_Y1       SSD1306_HEIGHT - 1

#define PONG_SCORE_X        35
#define PONG_BALL_X0        44
#define PONG_BALL_X1        84
#define PONG_BALL_Y0        22
#define PONG_BALL_Y1        42

struct paddle
{
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    bool isLost;
};

struct ball
{
    uint8_t x;
    uint8_t y;
    int8_t x_velocity;
    int8_t y_velocity;
    uint8_t size;
};

typedef enum
{
    Paddle_Up,
    Paddle_Down
} paddle_dir_e;

void pong_gameloop(void);

#endif
