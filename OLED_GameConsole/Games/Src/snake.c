

#include "snake.h"
#include "ssd1306.h"
#include "joystcik.h"

struct snake_st snake = {
    {SNAKE_SPAWN_X, SNAKE_SPAWN_X + SNAKE_SIZE, SNAKE_SPAWN_X + SNAKE_SIZE * 2},
    {30, 30, 30},
    3,
    Snake_Right};

struct snake_food_st food = {64, 32};

void snake_draw()
{
    for (uint8_t i = 0; i < snake.size; i++)
    {
        ssd1306_DrawRectangle(snake.x[i], snake.y[i], snake.x[i] + SNAKE_SIZE, snake.y[i] + SNAKE_SIZE, White);
    }
}

void snake_food_draw()
{
    ssd1306_FillRectangle(food.x, food.y, food.x + SNAKE_SIZE, food.y + SNAKE_SIZE, White);
}

void snake_movePixels(enum snake_dir dir)
{
    for (uint8_t node_idx = 0; node_idx < snake.size - 1; node_idx++)
    {
        snake.x[node_idx] = snake.x[node_idx + 1];
        snake.y[node_idx] = snake.y[node_idx + 1];
    }

    switch (dir)
    {
    case Snake_Right:
        snake.x[snake.size - 1] += SNAKE_SIZE;
        break;

    case Snake_Left:
        snake.x[snake.size - 1] -= SNAKE_SIZE;
        break;

    case Snake_Up:
        snake.y[snake.size - 1] += SNAKE_SIZE;
        break;

    case Snake_Down:
        snake.y[snake.size - 1] -= SNAKE_SIZE;
        break;
    }
}

void snake_moveByJoystick(void)
{
    if (joystcik_getX() < JOYSTICK_CENTER - JOYSTICK_CENTER_OFFSET && snake.dir != Snake_Right)
    {
        snake.dir = Snake_Left;
        snake_movePixels(snake.dir);
    }
    else if (joystcik_getX() > JOYSTICK_CENTER + JOYSTICK_CENTER_OFFSET && snake.dir != Snake_Left)
    {
        snake.dir = Snake_Right;
        snake_movePixels(snake.dir);
    }

    if (joystcik_getY() > JOYSTICK_CENTER + JOYSTICK_CENTER_OFFSET && snake.dir != Snake_Up)
    {
        snake.dir = Snake_Down;
        snake_movePixels(snake.dir);
    }
    else if (joystcik_getY() < JOYSTICK_CENTER - JOYSTICK_CENTER_OFFSET && snake.dir != Snake_Down)
    {
        snake.dir = Snake_Up;
        snake_movePixels(snake.dir);
    }
}

void snake_gameloop()
{
    while (1)
    {
        while (1)
        {
            buttons_updateAll();

            ssd1306_Fill(Black);
            snake_moveByJoystick();
            snake_draw();
            snake_food_draw();

            // Food eaten TODO fix
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
            }

            // todo generate new food location
            if (snake.x[snake.size - 1] <= 0 || snake.x[snake.size - 1] + SNAKE_SIZE >= SSD1306_WIDTH ||
                snake.y[snake.size - 1] <= 0 || snake.y[snake.size - 1] + SNAKE_SIZE >= SSD1306_HEIGHT)
            {
                break;
            }

            ssd1306_UpdateScreen();
        }
    }
}