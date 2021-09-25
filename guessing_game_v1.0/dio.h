/*
 * dio.h
 *
 *  Created on: Sep 25, 2021
 *      Author: TOSHIBA PC
 */
#ifndef DIO_H_
#define DIO_H_

#include "common_macros.h"
#include <avr/io.h>
#include <stdint.h>


typedef enum
{ INPUT=0,
	OUTPUT=1
}EN_direction;

typedef enum
{
	A,B,C,D
}EN_port;

typedef enum
{
	UPPER,LOWER
}EN_part;

typedef struct
{
	EN_port port;
	uint8_t pin;
	EN_direction direction;

}ST_DIO_config_t;


//void DIO_init(ST_DIO_config_t* configurations);
void DIO_init(EN_port port,uint8_t pin,EN_direction direction);
void DIO_initPort(EN_port port,EN_direction direction);
void DIO_initHalfPort(EN_port port,EN_direction direction,EN_part part);
void DIO_write(EN_port port,uint8_t pin,uint8_t data);
void DIO_writePort(EN_port port,uint8_t data);
void DIO_writeHalfPort(EN_port port,uint8_t data,EN_part part);
uint8_t DIO_read(EN_port port,uint8_t pin);
void DIO_toggle(EN_port port,uint8_t pin);

#endif /* DIO_H_ */
