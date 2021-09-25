/*
 * registers.h
 *
 *  Created on: Sep 25, 2021
 *      Author: TOSHIBA PC
 */

#ifndef REGISTERS_H_
#define REGISTERS_H_
/*PORTS*/
#define DDRA            (*(volatile uint8_t*)(0x3A))
#define PORTA           (*(volatile uint8_t*)(0x3B))
#define PINA            (*(volatile uint8_t*)(0x39))

#define DDRB            (*(volatile uint8_t*)(0x37))
#define PORTB           (*(volatile uint8_t*)(0x38))
#define PINB            (*(volatile uint8_t*)(0x36))

#define DDRC            (*(volatile uint8_t*)(0x34))
#define PORTC           (*(volatile uint8_t*)(0x35))
#define PINC            (*(volatile uint8_t*)(0x33))

#define DDRD            (*(volatile uint8_t*)(0x31))
#define PORTD           (*(volatile uint8_t*)(0x32))
#define PIND            (*(volatile uint8_t*)(0x30))

//Timer 0 Stuff
#define TCCR0			(*(volatile uint8_t*)0x53)
#define TCNT0			(*(volatile uint8_t*)0x52)
#define OCR0			(*(volatile uint8_t*)0x5C)

//for interrupt
#define TIMSK			(*(volatile uint8_t*)0x59)
#define TIFR			(*(volatile uint8_t*)0x58)
//for GIE
#define SREG 			(*(volatile uint8_t*)(0x5F))


#endif /* REGISTERS_H_ */
