/*
 * button.h
 *
 *  Created on: Sep 25, 2021
 *      Author: TOSHIBA PC
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include "dio.h"
#include <stdint.h>
#include "common_macros.h"
#define BUTTON_NUMBER 4

typedef struct
{
	EN_port port;
	uint8_t pin;

}ST_BUTTON_config_t;

typedef struct{
	ST_BUTTON_config_t button[BUTTON_NUMBER];
}ST_BUTTON_channels_t;

void BUTTON_init(ST_BUTTON_config_t* config);
uint8_t BUTTON_read(uint8_t button_number);


#endif /* BUTTON_H_ */
