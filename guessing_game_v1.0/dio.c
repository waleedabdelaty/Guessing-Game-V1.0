/*
 * dio.c
 *
 *  Created on: Sep 25, 2021
 *      Author: TOSHIBA PC
 */


#include "dio.h"

void DIO_init(EN_port port,uint8_t pin,EN_direction direction)
{
	if(port == A )
	{
		if (direction == INPUT)
		{
			CLEAR_BIT(DDRA,pin);
		}
		else
		{
			SET_BIT(DDRA,pin);
			CLEAR_BIT(PORTA,pin);
		}
	}
	else if(port == B)
	{
		if (direction == INPUT)
		{
			CLEAR_BIT(DDRB,pin);
		}
		else
		{
			SET_BIT(DDRB,pin);
			CLEAR_BIT(PORTB,pin);
		}
	}
	else if(port == C)
	{
		if (direction == INPUT)
		{
			CLEAR_BIT(DDRC,pin);
		}
		else
		{
			SET_BIT(DDRC,pin);
			CLEAR_BIT(PORTC,pin);
		}


	}
	else
	{
		if (direction == INPUT)
		{
			CLEAR_BIT(DDRD,pin);
		}
		else
		{
			SET_BIT(DDRD,pin);
			CLEAR_BIT(PORTD,pin);

		}


	}

}

/*

void DIO_init(ST_DIO_config_t* configurations)
{
	EN_port port = configurations->port;
	uint8_t pin = configurations->pin;
	EN_direction direction = configurations->direction;

	if(port == A )
	{
		if (direction == INPUT)
		{
			CLEAR_BIT(DDRA,pin);
		}
		else
		{
			SET_BIT(DDRA,pin);
			CLEAR_BIT(PORTA,pin);
		}
	}
	else if(port == B)
	{
		if (direction == INPUT)
		{
			CLEAR_BIT(DDRB,pin);
		}
		else
		{
			SET_BIT(DDRB,pin);
			CLEAR_BIT(PORTB,pin);
		}
	}
	else if(port == C)
	{
		if (direction == INPUT)
		{
			CLEAR_BIT(DDRC,pin);
		}
		else
		{
			SET_BIT(DDRC,pin);
			CLEAR_BIT(PORTC,pin);
		}


	}
	else
	{
		if (direction == INPUT)
		{
			CLEAR_BIT(DDRD,pin);
		}
		else
		{
			SET_BIT(DDRD,pin);
			CLEAR_BIT(PORTD,pin);

		}


	}

}
*/
void DIO_initPort(EN_port port,EN_direction direction)
{
	if(port == A )
	{
		if (direction == INPUT)
		{
			DDRA &= ~(0xFF);
		}
		else
		{
			DDRA |= 0xFF;
			PORTA &= ~(0xFF);
		}
	}
	else if(port == B)
	{
		if (direction == INPUT)
		{
			DDRB &= ~(0xFF);
		}
		else
		{
			DDRB |= 0xFF;
			PORTB &= ~(0xFF);
		}

	}
	else if(port == C)
	{
		if (direction == INPUT)
		{
			DDRC &= ~(0xFF);
		}
		else
		{
			DDRC |= 0xFF;
			PORTC &= ~(0xFF);
		}



	}
	else
	{
		if (direction == INPUT)
		{
			DDRD &= ~(0xFF);
		}
		else
		{
			DDRD |= 0xFF;
			PORTD &= ~(0xFF);
		}



	}
}
void DIO_initHalfPort(EN_port port,EN_direction direction,EN_part part)
{
	if(port == A )
	{
		if (direction == INPUT)
		{
			if (part == UPPER)
			{
				DDRA &= ~(0xF0);
			}
			else
			{
				DDRA &= ~(0x0F);
			}

		}
		else /* Output */
		{
			if (part == UPPER)
			{
				DDRA |= 0xF0;
				PORTA &= ~(0xF0);
			}
			else
			{
				DDRA |= 0x0F;
				PORTA &= ~(0x0F);
			}
		}
	}
	else if(port == B)
	{
		if (direction == INPUT)
		{
			if (part == UPPER)
			{
				DDRB &= ~(0xF0);
			}
			else
			{
				DDRB &= ~(0x0F);
			}

		}
		else /* Output */
		{
			if (part == UPPER)
			{
				DDRB |= 0xF0;
				PORTB &= ~(0xF0);
			}
			else
			{
				DDRB |= 0x0F;
				PORTB &= ~(0x0F);
			}
		}
	}
	else if(port == C)
	{
		if (direction == INPUT)
		{
			if (part == UPPER)
			{
				DDRC &= ~(0xF0);
			}
			else
			{
				DDRC &= ~(0x0F);
			}

		}
		else /* Output */
		{
			if (part == UPPER)
			{
				DDRC |= 0xF0;
				PORTC &= ~(0xF0);
			}
			else
			{
				DDRC |= 0x0F;
				PORTC &= ~(0x0F);
			}
		}
	}
	else /* PORT D */
	{
		if (direction == INPUT)
		{
			if (part == UPPER)
			{
				DDRD &= ~(0xF0);
			}
			else
			{
				DDRD &= ~(0x0F);
			}

		}
		else /* Output */
		{
			if (part == UPPER)
			{
				DDRD |= 0xF0;
				PORTD &= ~(0xF0);
			}
			else
			{
				DDRD |= 0x0F;
				PORTD &= ~(0x0F);
			}
		}

	}


}
void DIO_write(EN_port port,uint8_t pin,uint8_t data)
{
	if (port ==A)
	{
		PORTA = ( PORTA & ~(1<<pin) ) | data<<pin;
	}
	else if (port ==B)
	{
		PORTB = ( PORTB & ~(1<<pin) ) | data<<pin;
	}
	else if(port ==C)
	{
		PORTC = ( PORTC & ~(1<<pin) ) | data<<pin;
	}
	else
	{
		PORTD = ( PORTD & ~(1<<pin) ) | data<<pin;
	}

}
void DIO_writePort(EN_port port,uint8_t data)
{
	if (port ==A)
	{
		PORTA = data;
	}
	else if (port ==B)
	{
		PORTB = data;
	}
	else if(port ==C)
	{
		PORTC = data;
	}
	else
	{
		PORTD = data;
	}
}
void DIO_writeHalfPort(EN_port port,uint8_t data,EN_part part)
{
	if (port ==A)
	{
		if(part==UPPER)
		{
			PORTA = (PORTA & 0x0F) | data<<4;
		}
		else
		{
			PORTA = (PORTA & 0xF0) | (data & 0x0F) ;
		}

	}
	else if (port ==B)
	{
		if(part==UPPER)
		{
			PORTB = (PORTB & 0x0F) | data<<4;
		}
		else
		{
			PORTB = (PORTB & 0xF0) | (data & 0x0F) ;
		}
	}
	else if(port ==C)
	{
		if(part==UPPER)
		{
			PORTC = (PORTC & 0x0F) | data<<4;
		}
		else
		{
			PORTC = (PORTC & 0xF0) | (data & 0x0F) ;
		}
	}
	else
	{
		if(part==UPPER)
		{
			PORTD = (PORTD & 0x0F) | data<<4;
		}
		else
		{
			PORTD = (PORTD & 0xF0) | (data & 0x0F) ;
		}
	}
}
uint8_t DIO_read(EN_port port,uint8_t pin)
{
	uint8_t data;
	if (port ==A)
	{
		data = BIT_IS_SET(PINA,pin);
	}
	else if (port ==B)
	{
		data = BIT_IS_SET(PINB,pin);
	}
	else if(port ==C)
	{
		data = BIT_IS_SET(PINC,pin);
	}
	else
	{
		data = BIT_IS_SET(PIND,pin);
	}
	return data;
}

void DIO_toggle(EN_port port,uint8_t pin)
{
	if (port ==A)
	{
		TOGGLE_BIT(PORTA,pin);
	}
	else if (port ==B)
	{
		TOGGLE_BIT(PORTB,pin);
	}
	else if(port ==C)
	{
		TOGGLE_BIT(PORTC,pin);
	}
	else
	{
		TOGGLE_BIT(PORTD,pin);
	}
}
