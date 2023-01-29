#include "pong.h"
#include "game.h"
#include "button.h"
#include "joystcik.h"
#include "timer_tick.h"
#include "random.h"

static void priv_moveBall(struct ball *ball);
static void priv_movePaddle(struct paddle *paddle, uint8_t direction);
static void priv_displayScore(uint16_t score);
static priv_initGame(struct ball *ball, struct paddle *player1, struct paddle *player2);

static void priv_moveBall(struct ball *ball)
{
    ssd1306_FillRectangle(ball->x, ball->y, ball->x + ball->size, ball->y + ball->size, Black);

    ball->x += ball->x_velocity;
    ball->y += ball->y_velocity;

    if (ball->y + ball->size >= PONG_FIELD_Y1 || ball->y <= PONG_FIELD_Y0)
    {
        ball->y_velocity = -ball->y_velocity;
    }

    if (ball->x + ball->size >= PONG_FIELD_X1 || ball->x <= PONG_FIELD_X0)
    {
        ball->x_velocity = -ball->x_velocity;
    }

    ssd1306_FillRectangle(ball->x, ball->y, ball->x + ball->size, ball->y + ball->size, White);
}

static void priv_movePaddle(struct paddle *paddle, uint8_t direction)
{
    ssd1306_FillRectangle(paddle->x, paddle->y, paddle->x + paddle->width, paddle->y + paddle->height, Black);

    if (direction == Paddle_Down && (paddle->y + paddle->height) < PONG_FIELD_Y1)
    {
        paddle->y++;
    }

    if (direction == Paddle_Up && (paddle->y) > PONG_FIELD_Y0)
    {
        paddle->y--;
    }

    ssd1306_FillRectangle(paddle->x, paddle->y, paddle->x + paddle->width, paddle->y + paddle->height, White);
}

static void priv_displayScore(uint16_t score)
{
    static char buff[20];

    snprintf(buff, 20, "Score: %d   ", score);
    ssd1306_SetCursor(PONG_SCORE_X, 0);
    ssd1306_WriteString(buff, Font_6x8, White);
}

static priv_initGame(struct ball *ball, struct paddle *player1, struct paddle *player2)
{
    ssd1306_FillRectangle(player1->x, player1->y, player1->x + player1->width, player1->y + player1->height, White);
    ssd1306_FillRectangle(player2->x, player2->y, player2->x + player2->width, player2->y + player2->height, White);
    ssd1306_FillRectangle(ball->x, ball->y, ball->x + ball->size, ball->y + ball->size, Black);
}

void pong_gameloop(void)
{
    while (true)
    {

        struct paddle player1 = {0, 20, 4, 16};
        struct paddle player2 = {123, 25, 4, 16};
        struct ball ball = {0, 0, 1, 1, 1};
        ball.x = random_randint(PONG_BALL_X0, PONG_BALL_X1);
        ball.y = random_randint(PONG_BALL_Y0, PONG_BALL_Y1);

        ssd1306_Fill(Black);
        priv_initGame(&ball, &player1, &player2);
        ssd1306_UpdateScreen();

        uint16_t score = 0;
        TimerTick = 0;
        while (1)
        {
            score = TimerTick;
            priv_displayScore(score);
            priv_moveBall(&ball);

            if (ball.x == PONG_FIELD_X0 && (ball.y < player1.y || ball.y > (player1.y + player1.height)))
            {
                player1.isLost = true;
                break;
            }
            if (ball.x == (PONG_FIELD_X1 - 1) && (ball.y < player2.y || ball.y > (player2.y + player2.height)))
            {
                player2.isLost = true;
                break;
            }

            if (BUTTON_DOWN_IS_HOLD)
            {
                priv_movePaddle(&player2, Paddle_Down);
            }
            if (BUTTON_UP_IS_HOLD)
            {
                priv_movePaddle(&player2, Paddle_Up);
            }

            // Using X axis, because OLED is mirrored, Y became X
            if (joystcik_getX() < JOYSTICK_CENTER - JOYSTICK_CENTER_OFFSET)
            {
                priv_movePaddle(&player1, Paddle_Up);
            }
            if (joystcik_getX() > JOYSTICK_CENTER + JOYSTICK_CENTER_OFFSET)
            {
                priv_movePaddle(&player1, Paddle_Down);
            }

            ssd1306_UpdateScreen();
        }
        if (game_over(score, Game_Pong))
        {
            break;
        }
    }
}