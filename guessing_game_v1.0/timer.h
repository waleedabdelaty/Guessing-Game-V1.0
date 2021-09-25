/*
 * timer.h
 *
 *  Created on: Sep 25, 2021
 *      Author: TOSHIBA PC
 */
#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/


typedef enum
{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024,EXT_FALLING,EXT_RISING
}Timer_Clock;

typedef enum{
	NORMAL,COMPARE
}Timer_Mode;


typedef struct {
	Timer_Mode mode;
	Timer_Clock clk;
	uint8 initial_value;
	uint8 compare_value;
}Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Description : Function to initialize the Timer driver
 * 	1. Set the required clock.
 * 	2. Set the initial value.
 * 	3. Set the compare value.
 * 	4. Enable Interrupt depending on the mode
 */

void Timer0_init(const Timer_ConfigType * Config_Ptr);
/*
 * Description : set call back function of the Timer driver
 */
void Timer0_setCallBack(void(*a_ptr)(void));
/*
 * Description : Activating the timer by putting the clock value
 */
void Timer0_start(void);

/*
 * Description : Deactivating the timer by resetting of the clock value
 */
void Timer0_stop(void);




#endif /* TIMER_H_ */
