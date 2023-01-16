/*
 * main.c
 *
 *  Author: Leonid T?igrinski
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "main.h"
#include "button.h"
#include "ssd1306.h"
#include "joystcik.h"

#define ENABLE_DEBUG_LED \
	DDRD |= 1 << PORTD4; \
	PORTD |= 1 << PORTD4;
#define DISABLE_DEBUG_LED   \
	DDRD &= !(0 << PORTD4); \
	PORTD &= !(0 << PORTD4);

int main(void)
{
	ENABLE_DEBUG_LED;
	joystick_init();
	button_init();
	ssd1306_Init();
	ssd1306_Fill(Black);
	
	/*
	ssd1306_DrawRectangle(10, 10, 20, 20, White);
	ssd1306_FillRectangle(30, 10, 40, 20, White);
	ssd1306_DrawCircle(50, 15, 5, White);
	ssd1306_FillCircle(70, 15, 5, White);
	
	ssd1306_SetCursor(10, 25);
	ssd1306_WriteString("Leonid", Font_6x8, White);
	ssd1306_SetCursor(10, 33);
	ssd1306_WriteString("Leonid", Font_7x10, White);
	ssd1306_SetCursor(10, 43);
	ssd1306_WriteString("Leonid", Font_11x18, White);
	//ssd1306_WriteString("Leonid", Font_16x26, White);
	
	ssd1306_DrawArc(115, 50, 10, 0, 180, White);
	ssd1306_DrawArcWithRadiusLine(115, 20, 10, 0, 180, White);
	
	ssd1306_SetContrast(0xFF);
	
	*/
	ssd1306_UpdateScreen();
	
	sei();
	
	char buff0[50];
	char buff1[50];
	
	volatile uint8_t a;
	
	while (1)
	{
		buttons_updateAll();
		
		uint16_t adc0 = joystcik_getX();
		
		snprintf(buff0, 50, "Joy x: %d   ", adc0);
		ssd1306_SetCursor(2, 2);
		ssd1306_WriteString(buff0, Font_6x8, White);
		
		uint16_t adc1 = joystcik_getY();
		
		snprintf(buff1, 50, "Joy y: %d   ", adc1);
		ssd1306_SetCursor(2, 12);
		ssd1306_WriteString(buff1, Font_6x8, White);
		
		ssd1306_FillCircle(16, 45, 5, White);
		ssd1306_FillCircle(48, 45, 5, White);
		ssd1306_FillCircle(80, 45, 5, White);
		ssd1306_FillCircle(112, 45, 5, White);
		
		
		
		if (button_getState1() == Button_Down)
		{
			ssd1306_FillCircle(16, 45, 4, White);
		}
		else
		{
			ssd1306_FillCircle(16, 45, 4, Black);
		}
		
		if (button_getState2() == Button_Down)
		{
			ssd1306_FillCircle(48, 45, 4, White);
		}
		else
		{
			ssd1306_FillCircle(48, 45, 4, Black);
		}
		
		if (button_getState3() == Button_Down)
		{
			ssd1306_FillCircle(80, 45, 4, White);
		}
		else
		{
			ssd1306_FillCircle(80, 45, 4, Black);
		}
		
		if (button_getState4() == Button_Down)
		{
			ssd1306_FillCircle(112, 45, 4, White);
		}
		else
		{
			ssd1306_FillCircle(112, 45, 4, Black);
		}
		
		
		
		ssd1306_UpdateScreen();
	}
	

	return 0;
}

/*
int main(void)
{
	button_init();
	DDRD = 0xFF;

	adc_init();

	volatile pin_state_e x;
	volatile uint8_t y;
	volatile button_state_e w;
	// sei();
	while (1)
	{
		buttons_updateAll();
		w = button_getState1();
		if (w == Button_Falling)
		{
			PORTD ^= 0xFF;
		}
	}
}
*/