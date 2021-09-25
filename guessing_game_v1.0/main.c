/*
 * main.c
 *
 *  Created on: Sep 25, 2021
 *      Author: TOSHIBA PC
 */


#include "lcd.h"
#include "button.h"
#include "timer.h"
#include <stdlib.h>

#define NON_RESPONDING_TICKS 10

uint16_t g_tick=0;
uint8_t flag=0;

void TIMER_callback(void)
{
	g_tick++;
	if(g_tick==NON_RESPONDING_TICKS)
	{
		flag = 1;
		g_tick=0;
	}
}

int main(void)
{
	ST_BUTTON_config_t button = {A,0};
	Timer_ConfigType timer_config = {COMPARE,F_CPU_1024,0,250};

	/* Timer Initialization */
	Timer0_init(&timer_config);
	Timer0_setCallBack(TIMER_callback); // Call Every 250ms Second
	Timer0_start();

	/* Button Initialization */
	BUTTON_init(&button);

	/* LCD Initialization */
	LCD_init();

	uint8_t number,count;
	while(1)
	{
		count = 0;
		flag=0;
		g_tick=0;
		number = ( rand() % 14 ) + 1;
		LCD_clearScreen();
		LCD_displayString("Guess: ");
		while(1)
		{
			if(BUTTON_read(1))
			{

				_delay_ms(30);
				if(BUTTON_read(1))
				{
					flag=0;
					g_tick=0;
					count++;
				}
				while(BUTTON_read(4)){}

			}
			if(flag==1) /*I didn't Press For 2seconds*/
			{
				if(count==0)
				{
					LCD_clearScreen();
					LCD_displayString("You Didn't Press!");
					_delay_ms(2000);

				}
				else
				{
					LCD_integerToString(count);
					_delay_ms(2000);
					LCD_clearScreen();
					if(count==number)
					{
						LCD_displayString("Right Guess!!");

					}
					else
					{
						LCD_displayString("Wrong Guess!!");
						LCD_goToRowColumn(1,0);
						LCD_displayString("Right Guess: ");
						LCD_integerToString(number);
					}
					_delay_ms(2000);
				}

				break;
			}

		}

	}
}
