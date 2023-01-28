#include "pong.h"
#include "button.h"
#include "joystcik.h"
#include "timer_tick.h"

struct paddle player1 = {0, 20, 4, 16};
struct paddle player2 = {123, 25, 4, 16};
struct ball ball = {64, 32, 1, 1, 1};



// Function to move the ball
void pong_moveBall(struct ball *ball)
{
    ball->x += ball->xVelocity;
    ball->y += ball->yVelocity;

    if (ball->y + ball->size >= PONG_FIELD_Y1 || ball->y <= PONG_FIELD_Y0)
    {
        ball->yVelocity = -ball->yVelocity;
    }

    if (ball->x + ball->size >= PONG_FIELD_X1 || ball->x <= PONG_FIELD_X0)
    {
        ball->xVelocity = -ball->xVelocity;
    }
}

void pong_movePaddle(struct paddle *paddle, uint8_t direction)
{
    if (direction == Paddle_Down && (paddle->y + paddle->height) < PONG_FIELD_Y1)
    {
        paddle->y++;
    }

    if (direction == Paddle_Up && (paddle->y) > PONG_FIELD_Y0)
    {
        paddle->y--;
    }
}

void pong_checkForCollision(void)
{
    if (ball.x == PONG_FIELD_X0 && (ball.y < player1.y || ball.y > (player1.y + player1.height)))
    {
        player1.isLost = true;
    }
    if (ball.x == (PONG_FIELD_X1 - 1) && (ball.y < player2.y || ball.y > (player2.y + player2.height)))
    {
        player2.isLost = true;
    }
}

void pong_gameloop(void)
{
    ssd1306_Fill(Black);
    
    char buff0[20];
    snprintf(buff0, 20, "Score: %d   ", TimerTick);
    ssd1306_SetCursor(42, 0);
    ssd1306_WriteString(buff0, Font_6x8, White);

    // ssd1306_DrawRectangle(PONG_FIELD_X0, PONG_FIELD_Y0, PONG_FIELD_X1, PONG_FIELD_Y1, White);
    ssd1306_FillRectangle(player1.x, player1.y, player1.x + player1.width, player1.y + player1.height, White);
    ssd1306_FillRectangle(player2.x, player2.y, player2.x + player2.width, player2.y + player2.height, White);
    ssd1306_FillRectangle(ball.x, ball.y, ball.x + ball.size, ball.y + ball.size, Black);
    ssd1306_UpdateScreen();
    while (1)
    {
        ssd1306_FillRectangle(ball.x, ball.y, ball.x + ball.size, ball.y + ball.size, Black);
        pong_moveBall(&ball);
        ssd1306_FillRectangle(ball.x, ball.y, ball.x + ball.size, ball.y + ball.size, White);
        ssd1306_UpdateScreen();
        pong_checkForCollision();

        if (BUTTON_DOWN_IS_HOLD)
        {
            ssd1306_FillRectangle(player2.x, player2.y, player2.x + player2.width, player2.y + player2.height, Black);
            pong_movePaddle(&player2, Paddle_Down);
            ssd1306_FillRectangle(player2.x, player2.y, player2.x + player2.width, player2.y + player2.height, White);
        }
        else if (BUTTON_UP_IS_HOLD)
        {
            ssd1306_FillRectangle(player2.x, player2.y, player2.x + player2.width, player2.y + player2.height, Black);
            pong_movePaddle(&player2, Paddle_Up);
            ssd1306_FillRectangle(player2.x, player2.y, player2.x + player2.width, player2.y + player2.height, White);
        }

        if (joystcik_getY() < JOYSTICK_CENTER - JOYSTICK_CENTER_OFFSET)
        {
            ssd1306_FillRectangle(player1.x, player1.y, player1.x + player1.width, player1.y + player1.height, Black);
            pong_movePaddle(&player1, Paddle_Up);
            ssd1306_FillRectangle(player1.x, player1.y, player1.x + player1.width, player1.y + player1.height, White);
        }
        else if (joystcik_getY() > JOYSTICK_CENTER + JOYSTICK_CENTER_OFFSET)
        {
            ssd1306_FillRectangle(player1.x, player1.y, player1.x + player1.width, player1.y + player1.height, Black);
            pong_movePaddle(&player1, Paddle_Down);
            ssd1306_FillRectangle(player1.x, player1.y, player1.x + player1.width, player1.y + player1.height, White);
        }

        if (player1.isLost)
        {
            // ssd1306_SetCursor(10, 15);
            // ssd1306_WriteString("Player 1 lost", Font_6x8, White);
            // ssd1306_UpdateScreen();
            // while (1)
            //     ;
            break;
        }
        if (player2.isLost)
        {
            // ssd1306_SetCursor(10, 15);
            // ssd1306_WriteString("Player 2 lost", Font_6x8, White);
            // ssd1306_UpdateScreen();
            // while (1)
            //     ;
            break;
        }

        // _delay_ms(5);
    }
}