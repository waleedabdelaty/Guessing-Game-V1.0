/*
 * timer.c
 *
 *  Created on: Sep 25, 2021
 *      Author: TOSHIBA PC
 */


#include "timer.h"
/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/
/* Global variables to hold the configuration structure data */
uint8 g_clock;
uint8 g_initial_value;

/* Global variable to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void)=NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER0_OVF_vect)
{
	TCNT0 = g_initial_value ;
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}

ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		(*g_callBackPtr)();
	}
}
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the Timer driver
 * 	1. Set the required clock.
 * 	2. Set the initial value.
 * 	3. Set the compare value.
 * 	4. Enable Interrupt depending on the mode
 */

void Timer0_init(const Timer_ConfigType * Config_Ptr)
{
	SREG |= 1<<7;
	g_clock = (Config_Ptr->clk);
	g_initial_value=( Config_Ptr->initial_value ) ;
	TCCR0 = ( 1<<FOC0 ) |  ( Config_Ptr->mode << WGM01 );
	OCR0 = ( Config_Ptr->compare_value ) ;

	if(Config_Ptr->mode)  //Compare Mode
	{
		TIMSK |= 1<<OCIE0 ; // Timer Overflow Interrupt Enable
	}
	else  // Normal Mode
	{
		TIMSK |= 1<<TOIE0 ;  //Compare Match Interrupt Enable
	}
}

/*
 * Description : set call back function of the Timer driver
 */

void Timer0_setCallBack(void(*a_ptr)(void))
{
	g_callBackPtr=a_ptr;
}

/*
 * Description : Activating the timer by putting the clock value
 */
void Timer0_start(void)
{
	TCNT0 = g_initial_value ;
	TCCR0 |= (g_clock & 0x07);
}

/*
 * Description : Deactivating the timer by resetting of the clock value
 */
void Timer0_stop(void)
{
	TCCR0 &= ~(0x07); /* Disable The Clock*/
}

