

#include "snake.h"
#include "game.h"
#include "ssd1306.h"
#include "joystcik.h"
#include "timer_tick.h"
#include "random.h"

static void priv_drawSnake(struct snake *snake);
static void priv_drawFood(struct snake_food *food);
static void snake_movePixels(struct snake *snake);
static void priv_displayScore(uint16_t score);

void priv_drawSnake(struct snake *snake)
{
    for (uint8_t i = 0; i < snake->size; i++)
    {
        ssd1306_DrawRectangle(snake->x[i], snake->y[i], snake->x[i] + SNAKE_SIZE, snake->y[i] + SNAKE_SIZE, White);
    }
}

void priv_drawFood(struct snake_food *food)
{
    ssd1306_FillRectangle(food->x, food->y, food->x + SNAKE_SIZE, food->y + SNAKE_SIZE, White);
}

void snake_movePixels(struct snake *snake)
{
    for (uint8_t node_idx = 0; node_idx < snake->size - 1; node_idx++)
    {
        snake->x[node_idx] = snake->x[node_idx + 1];
        snake->y[node_idx] = snake->y[node_idx + 1];
    }

    switch (snake->dir)
    {
    case Snake_Right:
        snake->x[snake->size - 1] += SNAKE_SIZE;
        break;

    case Snake_Left:
        snake->x[snake->size - 1] -= SNAKE_SIZE;
        break;

    case Snake_Up:
        snake->y[snake->size - 1] += SNAKE_SIZE;
        break;

    case Snake_Down:
        snake->y[snake->size - 1] -= SNAKE_SIZE;
        break;
    }
}

static void priv_displayScore(uint16_t score)
{
    static char buff[20];

    snprintf(buff, 20, "Score: %d   ", score);
    ssd1306_SetCursor(SNAKE_SCORE_X, 0);
    ssd1306_WriteString(buff, Font_6x8, White);
}

void snake_gameloop()
{
    while (true)
    {
        struct snake snake = {{SNAKE_SPAWN_X}, {30}, 1, Snake_Right};
        struct snake_food food = {64, 32};

        uint16_t score = 0;
        TimerTick = 0;
        while (true)
        {
            score = TimerTick;
            ssd1306_Fill(Black);
            priv_displayScore(score);

            // Move snake
            if (joystcik_getX() < JOYSTICK_CENTER - JOYSTICK_CENTER_OFFSET && snake.dir != Snake_Right)
            {
                snake.dir = Snake_Left;
                snake_movePixels(&snake);
            }
            else if (joystcik_getX() > JOYSTICK_CENTER + JOYSTICK_CENTER_OFFSET && snake.dir != Snake_Left)
            {
                snake.dir = Snake_Right;
                snake_movePixels(&snake);
            }

            if (joystcik_getY() > JOYSTICK_CENTER + JOYSTICK_CENTER_OFFSET && snake.dir != Snake_Up)
            {
                snake.dir = Snake_Down;
                snake_movePixels(&snake);
            }
            else if (joystcik_getY() < JOYSTICK_CENTER - JOYSTICK_CENTER_OFFSET && snake.dir != Snake_Down)
            {
                snake.dir = Snake_Up;
                snake_movePixels(&snake);
            }

            // Eat food
            if ((snake.x[snake.size - 1] <= food.x + SNAKE_SIZE && snake.x[snake.size - 1] + SNAKE_SIZE >= food.x) &&
                (snake.y[snake.size - 1] <= food.y + SNAKE_SIZE && snake.y[snake.size - 1] + SNAKE_SIZE >= food.y))
            {

                switch (snake.dir)
                {
                case Snake_Right:
                    snake.x[snake.size] = snake.x[snake.size - 1] + SNAKE_SIZE;
                    snake.y[snake.size] = snake.y[snake.size - 1];
                    break;

                case Snake_Left:
                    snake.x[snake.size] = snake.x[snake.size - 1] - SNAKE_SIZE;
                    snake.y[snake.size] = snake.y[snake.size - 1];
                    break;

                case Snake_Up:
                    snake.x[snake.size] = snake.x[snake.size - 1];
                    snake.y[snake.size] = snake.y[snake.size - 1] + SNAKE_SIZE;
                    break;

                case Snake_Down:
                    snake.x[snake.size] = snake.x[snake.size - 1];
                    snake.y[snake.size] = snake.y[snake.size - 1] - SNAKE_SIZE;
                    break;
                }
                snake.size++;

                food.x = random_randint(0, SSD1306_WIDTH - SNAKE_SIZE);
                food.y = random_randint(0, SSD1306_HEIGHT - SNAKE_SIZE);
            }

            // Check if boundaries hit
            if (snake.x[snake.size - 1] <= 0 || snake.x[snake.size - 1] + SNAKE_SIZE >= SSD1306_WIDTH ||
                snake.y[snake.size - 1] <= 0 || snake.y[snake.size - 1] + SNAKE_SIZE >= SSD1306_HEIGHT)
            {
                break;
            }

            priv_drawSnake(&snake);
            priv_drawFood(&food);
            ssd1306_UpdateScreen();
        }
        if (game_over(score, Game_Snake))
        {
            break;
        }
    }
}