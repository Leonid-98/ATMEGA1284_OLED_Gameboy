/*
 * game.h
 *
 * Created: 28.01.2023 23:52:01
 *  Author: Leonid Tsigrinski
 */

#ifndef PONG_H_
#define PONG_H_

#include "ssd1306.h"
#include "stdbool.h"


#define PONG_FIELD_X0 5
#define PONG_FIELD_Y0 10
#define PONG_FIELD_X1 SSD1306_WIDTH - 6
#define PONG_FIELD_Y1 SSD1306_HEIGHT - 1
// Player paddle structure
struct paddle
{
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    bool isLost;
};

// Ball structure
struct ball
{
    uint8_t x;
    uint8_t y;
    int8_t xVelocity;
    int8_t yVelocity;
    uint8_t size;
};

enum
{
    Paddle_Up,
    Paddle_Down
};

void pong_moveBall(struct ball *ball);
void pong_movePaddle(struct paddle *paddle, uint8_t direction);
void pong_checkForCollision(void);
void pong_gameloop(void);

#endif
