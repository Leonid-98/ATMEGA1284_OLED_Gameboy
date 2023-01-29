/*
 * main.c
 *
 *  Author: Leonid T?igrinski
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "timer_tick.h"
#include "random.h"
#include "button.h"
#include "ssd1306.h"
#include "joystcik.h"

#include "game.h"
#include "dino.h"
#include "pong.h"
#include "snake.h"

void debug_mainloop(void);

// ! TIMER
/*
#include "notes.h"
#include "song_lose.h"

volatile uint16_t i = 0;
const uint16_t lenMelody1 = sizeof(melody) / sizeof(melody[0]);
uint16_t scaleDelay(uint16_t delayMs)
{
	return (delayMs - delayMs / 32 + delayMs / 128);
}

uint16_t freqToDelay(uint16_t freq)
{
	return F_CPU / freq / 2;
}

int16_t myAbs(int16_t v)
{
	return v * ((v > 0) - (v < 0));
}

ISR(TIMER1_COMPA_vect)
{
	// fast timer, freq generator
	// PINB = 1 << PORTB6;
	PIND = 1 << PIND5;
}

ISR(TIMER3_COMPA_vect)
{
	// slow timer, tone changer
	TCNT3 = 0;
	i += 2;
	if (i > lenMelody1)
	{
		i = 0;
	}
}
*/
// ! TIMER

int main(void)
{
	// ENABLE_DEBUG_LED;
	timer0_init();
	joystick_init();
	random_init();
	button_init();
	ssd1306_Init();
	buttons_updateAll();
	sei();

	// ! TIMER
	/*
	// TIMER1, sound generator, fast timer
	TCCR1A = (1 << WGM10) | (1 << WGM11);
	TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10);
	TIMSK1 = 1 << OCIE1A; // interrupt en

	// TIMER3, tone changer, slow timer
	TCCR3A = (0 << WGM30) | (0 << WGM31);
	TCCR3B = (0 << WGM32) | (0 << WGM33) | (1 << CS32) | (0 << CS31) | (1 << CS30);
	TIMSK3 = 1 << OCIE3A; // interrupt en

	// buzzer init
	DDRD = 0xFF;
	PORTD |= 1 << PORTD5;

	while (true)
	{
		// freq selector
		if (melody[i])
		{
			TIMSK1 |= 1 << OCIE1A;
			OCR1A = freqToDelay(melody[i]);
		}
		else
		{
			TIMSK1 |= 0 << OCIE1A;
		}

		// note selector
		int16_t lenNote = (240000 / tempo) / myAbs(melody[i + 1]) * 2;
		if (melody[i + 1] < 0)
			lenNote *= 1.5;
		OCR3A = scaleDelay(lenNote);
	}
	*/
	// ! TIMER

	game_selected_e selected_game;
	while (true)
	{
		selected_game = game_mainMenuLoop();
		switch (selected_game)
		{
		case Game_Dino:
			dino_gameloop();
			break;
		case Game_Snake:
			snake_gameloop();
			break;
		case Game_Pong:
			pong_gameloop();
			break;
		case Game_Debug:
			debug_mainloop();
			break;
		default:
			break;
		}
	}

	return 0;
}

void debug_mainloop(void)
{
	static char buff0[20];
	static char buff1[20];
	static char buff2[20];
	static char buff3[20];

	ssd1306_Fill(Black);
	while (true)
	{
		buttons_updateAll();

		snprintf(buff0, 20, "Joy x: %d   ", joystcik_getX());
		ssd1306_SetCursor(0, 2);
		ssd1306_WriteString(buff0, Font_6x8, White);

		snprintf(buff1, 20, "Joy y: %d   ", joystcik_getY());
		ssd1306_SetCursor(0, 12);
		ssd1306_WriteString(buff1, Font_6x8, White);

		snprintf(buff2, 20, "Random: %d   ", random_randint(0, 128));
		ssd1306_SetCursor(64, 2);
		ssd1306_WriteString(buff2, Font_6x8, White);

		snprintf(buff3, 20, "Tick: %d   ", TimerTick);
		ssd1306_SetCursor(64, 12);
		ssd1306_WriteString(buff3, Font_6x8, White);

		ssd1306_SetCursor(64, 50);
		ssd1306_WriteString("UP + DOWN", Font_6x8, White);

		ssd1306_SetCursor(64, 30);
		ssd1306_WriteString("clr score:", Font_6x8, White);
		ssd1306_SetCursor(64, 40);
		ssd1306_WriteString("exit: A+B", Font_6x8, White);

		ssd1306_FillCircle(10, 35, 5, White);
		ssd1306_FillCircle(25, 35, 5, White);
		ssd1306_FillCircle(25, 50, 5, White);
		ssd1306_FillCircle(10, 50, 5, White);

		(button_getState1() == Button_Down) ? ssd1306_FillCircle(10, 35, 4, White) : ssd1306_FillCircle(10, 35, 4, Black);
		(button_getState2() == Button_Down) ? ssd1306_FillCircle(25, 35, 4, White) : ssd1306_FillCircle(25, 35, 4, Black);
		(button_getState3() == Button_Down) ? ssd1306_FillCircle(10, 50, 4, White) : ssd1306_FillCircle(10, 50, 4, Black);
		(button_getState4() == Button_Down) ? ssd1306_FillCircle(25, 50, 4, White) : ssd1306_FillCircle(25, 50, 4, Black);

		if (button_getState1() == Button_Down && button_getState3() == Button_Down)
		{
			game_clearAllScores();
		}

		if (button_getState2() == Button_Down && button_getState4() == Button_Down)
		{
			break;
		}

		ssd1306_UpdateScreen();
	}
}
