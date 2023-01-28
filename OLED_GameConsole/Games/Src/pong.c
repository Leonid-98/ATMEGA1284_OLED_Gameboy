// #define UP_BUTTON 2
// #define DOWN_BUTTON 3

// // Color definitions
// #define BLACK 0x0000
// #define BLUE 0x001F
// #define RED 0xF800
// #define GREEN 0x07E0
// #define CYAN 0x07FF
// #define MAGENTA 0xF81F
// #define YELLOW 0xFFE0
// #define WHITE 0xFFFF

// const unsigned long PADDLE_RATE = 33;
// const unsigned long BALL_RATE = 20;
// const uint8_t PADDLE_HEIGHT = 24;

// int MAX_SCORE = 8;
// int CPU_SCORE = 0;
// int PLAYER_SCORE = 0;

// void drawCourt();

// uint8_t ball_x = 64, ball_y = 32;
// uint8_t ball_dir_x = 1, ball_dir_y = 1;

// boolean gameIsRunning = true;
// boolean resetBall = false;

// unsigned long ball_update;
// unsigned long paddle_update;

// const uint8_t CPU_X = 12;
// uint8_t cpu_y = 16;

// const uint8_t PLAYER_X = 85;
// uint8_t player_y = 16;

// void setup()
// {

//   pinMode(UP_BUTTON, INPUT_PULLUP);
//   pinMode(DOWN_BUTTON, INPUT_PULLUP);
//   display.begin();
//   display.fillScreen(BLACK);
//   display.drawBitmap(3, 0, pong, 89, 24, GREEN);
//   display.drawBitmap(10, 30, game, 75, 26, RED);
//   while (digitalRead(UP_BUTTON) == HIGH && digitalRead(DOWN_BUTTON) == HIGH)
//   {
//     delay(100);
//   }
//   unsigned long start = millis();

//   display.fillScreen(BLACK);
//   drawCourt();

//   while (millis() - start < 2000)
//     ;
//   ball_update = millis();
//   paddle_update = ball_update;
//   ball_x = random(25, 65);
//   ball_y = random(3, 63);
// }

// void loop()
// {

//   unsigned long time = millis();
//   static bool up_state = false;
//   static bool down_state = false;

//   up_state |= (digitalRead(UP_BUTTON) == LOW);
//   down_state |= (digitalRead(DOWN_BUTTON) == LOW);

//   if (resetBall)
//   {
//     ball_x = random(25, 70);
//     ball_y = random(3, 63);
//     do
//     {
//       ball_dir_x = random(-1, 2);
//     } while (ball_dir_x == 0);

//     do
//     {
//       ball_dir_y = random(-1, 2);
//     } while (ball_dir_y == 0);

//     resetBall = false;
//   }

//   if (time > ball_update && gameIsRunning)
//   {
//     uint8_t new_x = ball_x + ball_dir_x;
//     uint8_t new_y = ball_y + ball_dir_y;

//     // Check if we hit the vertical walls
//     if (new_x == 0) // Player Gets a Point
//     {
//       PLAYER_SCORE++;
//       if (PLAYER_SCORE == MAX_SCORE)
//       {
//         gameOver();
//       }
//       else
//       {
//         showScore();
//       }
//     }

//     // Check if we hit the vertical walls
//     if (new_x == 95) // CPU Gets a Point
//     {
//       CPU_SCORE++;
//       if (CPU_SCORE == MAX_SCORE)
//       {
//         gameOver();
//       }
//       else
//       {
//         showScore();
//       }
//     }

//     // Check if we hit the horizontal walls.
//     if (new_y == 0 || new_y == 63)
//     {
//       ball_dir_y = -ball_dir_y;
//       new_y += ball_dir_y + ball_dir_y;
//     }

//     // Check if we hit the CPU paddle
//     if (new_x == CPU_X && new_y >= cpu_y && new_y <= cpu_y + PADDLE_HEIGHT)
//     {
//       ball_dir_x = -ball_dir_x;
//       new_x += ball_dir_x + ball_dir_x;
//     }

//     // Check if we hit the player paddle
//     if (new_x == PLAYER_X && new_y >= player_y && new_y <= player_y + PADDLE_HEIGHT)
//     {
//       ball_dir_x = -ball_dir_x;
//       new_x += ball_dir_x + ball_dir_x;
//     }

//     display.drawPixel(ball_x, ball_y, BLACK);
//     display.drawPixel(new_x, new_y, WHITE);
//     ball_x = new_x;
//     ball_y = new_y;

//     ball_update += BALL_RATE;
//   }

//   if (time > paddle_update && gameIsRunning)
//   {
//     paddle_update += PADDLE_RATE;

//     // CPU paddle
//     display.drawFastVLine(CPU_X, cpu_y, PADDLE_HEIGHT, BLACK);
//     const uint8_t half_paddle = PADDLE_HEIGHT >> 1;
//     if (cpu_y + half_paddle > ball_y)
//     {
//       cpu_y -= 1;
//     }
//     if (cpu_y + half_paddle < ball_y)
//     {
//       cpu_y += 1;
//     }
//     if (cpu_y < 1)
//       cpu_y = 1;
//     if (cpu_y + PADDLE_HEIGHT > 63)
//       cpu_y = 63 - PADDLE_HEIGHT;
//     display.drawFastVLine(CPU_X, cpu_y, PADDLE_HEIGHT, RED);

//     // Player paddle
//     display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, BLACK);
//     if (up_state)
//     {
//       player_y -= 1;
//     }
//     if (down_state)
//     {
//       player_y += 1;
//     }
//     up_state = down_state = false;
//     if (player_y < 1)
//       player_y = 1;
//     if (player_y + PADDLE_HEIGHT > 63)
//       player_y = 63 - PADDLE_HEIGHT;
//     display.drawFastVLine(PLAYER_X, player_y, PADDLE_HEIGHT, GREEN);
//   }
// }

// void drawCourt()
// {
//   display.drawRect(0, 0, 96, 64, WHITE);
// }

// void gameOver()
// {
//   gameIsRunning = false;
//   display.fillScreen(BLACK);
//   drawCourt();
//   if (PLAYER_SCORE > CPU_SCORE)
//   {
//     display.setCursor(5, 4);
//     display.setTextColor(WHITE);
//     display.setTextSize(2);
//     display.print("You Won");
//   }
//   else
//   {
//     display.setCursor(5, 4);
//     display.setTextColor(WHITE);
//     display.setTextSize(2);
//     display.print("CPU WON");
//   }

//   display.setCursor(20, 30);
//   display.setTextColor(RED);
//   display.setTextSize(3);
//   display.print(String(CPU_SCORE));

//   display.setCursor(60, 30);
//   display.setTextColor(GREEN);
//   display.setTextSize(3);
//   display.print(String(PLAYER_SCORE));

//   delay(2000);

//   while (digitalRead(UP_BUTTON) == HIGH && digitalRead(DOWN_BUTTON) == HIGH)
//   {
//     delay(100);
//   }
//   gameIsRunning = true;

//   CPU_SCORE = PLAYER_SCORE = 0;

//   unsigned long start = millis();
//   display.fillScreen(BLACK);
//   drawCourt();
//   while (millis() - start < 2000)
//     ;
//   ball_update = millis();
//   paddle_update = ball_update;
//   gameIsRunning = true;
//   resetBall = true;
// }

// void showScore()
// {
//   gameIsRunning = false;
//   display.fillScreen(BLACK);
//   drawCourt();

//   display.setCursor(15, 4);
//   display.setTextColor(WHITE);
//   display.setTextSize(2);
//   display.print("Score");

//   display.setCursor(20, 30);
//   display.setTextColor(RED);
//   display.setTextSize(3);
//   display.print(String(CPU_SCORE));

//   display.setCursor(60, 30);
//   display.setTextColor(GREEN);
//   display.setTextSize(3);
//   display.print(String(PLAYER_SCORE));

//   delay(2000);
//   unsigned long start = millis();

//   display.fillScreen(BLACK);
//   drawCourt();
//   while (millis() - start < 2000)
//     ;
//   ball_update = millis();
//   paddle_update = ball_update;
//   gameIsRunning = true;
//   resetBall = true;
// }
