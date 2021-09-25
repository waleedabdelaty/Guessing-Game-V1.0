/*
 * button.c
 *
 *  Created on: Sep 25, 2021
 *      Author: TOSHIBA PC
 */

#include "button.h"

static uint8_t counter=0;
static ST_BUTTON_channels_t channels;

void BUTTON_init(ST_BUTTON_config_t* config)
{
	EN_port port = config->port;
	uint8_t pin = config->pin;
	//ST_DIO_config_t button_config = {port,pin,INPUT};
	//DIO_init(&button_config);
	DIO_init(port,pin,INPUT);
	channels.button[counter].port = port;
	channels.button[counter].pin = pin;
	counter++;
}
uint8_t BUTTON_read(uint8_t button_number)
{
	button_number -= 1;
	EN_port port = channels.button[button_number].port;
	uint8_t pin = channels.button[button_number].pin;
	return DIO_read(port,pin);
}
