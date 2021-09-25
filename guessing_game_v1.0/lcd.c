
#include "lcd.h"
#include <stdlib.h>

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/


void LCD_init(void)
{
	/* Control Port as an Output */
	DIO_init(LCD_CTRL_PORT,E,OUTPUT);
	DIO_init(LCD_CTRL_PORT,RS,OUTPUT);
	DIO_init(LCD_CTRL_PORT,RW,OUTPUT);

#if (DATA_BITS_MODE == 8)
	DIO_initPort(LCD_DATA_PORT,OUTPUT); /* Data Port as an Output */
	LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /*Configure LCD For 8 Bit Data Mode + 2 Line LCD */
#elif (DATA_BITS_MODE == 4)
	LCD_sendCommand(FOUR_BITS_DATA_MODE);
	LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
	#ifdef UPPER_PORT_PINS
	DIO_initHalfPort(LCD_DATA_PORT,OUTPUT,UPPER);
	#else
	DIO_initHalfPort(LCD_DATA_PORT,OUTPUT,LOWER);
	#endif
#endif

	LCD_sendCommand(CURSOR_OFF); /* Cursor Off */
	LCD_sendCommand(CLEAR_COMMAND); /* Clearing The LCD*/

}
void LCD_sendCommand(uint8_t command)
{
	DIO_write(LCD_CTRL_PORT,RS,LOW);
	DIO_write(LCD_CTRL_PORT,RW,LOW);
	_delay_ms(1);
	DIO_write(LCD_CTRL_PORT,E,HIGH);
	_delay_ms(1);
	#if (DATA_BITS_MODE == 8)
	DIO_writePort(LCD_DATA_PORT,command);
	_delay_ms(1);
	DIO_write(LCD_CTRL_PORT,E,LOW);
	_delay_ms(1);

	#elif (DATA_BITS_MODE == 4)
	/* SEND FIRST 4 BITS OF Command */
	#ifdef UPPER_PORT_PINS
	DIO_writeHalfPort(LCD_DATA_PORT,command,UPPER);
	#else
	DIO_writeHalfPort(LCD_DATA_PORT,command,LOWER);
	#endif
	_delay_ms(1);
	DIO_write(LCD_CTRL_PORT,E,LOW);
	_delay_ms(1);
	/* SEND SECOND 4 BITS OF Command */
	DIO_write(LCD_CTRL_PORT,E,HIGH);
	_delay_ms(1);
	#ifdef UPPER_PORT_PINS
	DIO_writeHalfPort(LCD_DATA_PORT,command>>4,UPPER);
	#else
	DIO_writeHalfPort(LCD_DATA_PORT,command>>4,LOWER);
	#endif
	_delay_ms(1);
	DIO_write(LCD_CTRL_PORT,E,LOW);
	_delay_ms(1);
#endif



}
void LCD_displayCharacter(uint8_t data)
{
		DIO_write(LCD_CTRL_PORT,RS,HIGH);
		DIO_write(LCD_CTRL_PORT,RW,LOW);
		_delay_ms(1);
		DIO_write(LCD_CTRL_PORT,E,HIGH);
		_delay_ms(1);
		#if (DATA_BITS_MODE == 8)
		DIO_writePort(LCD_DATA_PORT,data);
		_delay_ms(1);
		DIO_write(LCD_CTRL_PORT,E,LOW);
		_delay_ms(1);

		#elif (DATA_BITS_MODE == 4)
		/* SEND FIRST 4 BITS OF Command */
		#ifdef UPPER_PORT_PINS
		DIO_writeHalfPort(LCD_DATA_PORT,data,UPPER);
		#else
		DIO_writeHalfPort(LCD_DATA_PORT,data,LOWER);
		#endif
		_delay_ms(1);
		DIO_write(LCD_CTRL_PORT,E,LOW);
		_delay_ms(1);
		/* SEND SECOND 4 BITS OF Command */
		DIO_write(LCD_CTRL_PORT,E,HIGH);
		_delay_ms(1);
		#ifdef UPPER_PORT_PINS
		DIO_writeHalfPort(LCD_DATA_PORT,data>>4,UPPER);
		#else
		DIO_writeHalfPort(LCD_DATA_PORT,data>>4,LOWER);
		#endif
		_delay_ms(1);
		DIO_write(LCD_CTRL_PORT,E,LOW);
		_delay_ms(1);
	#endif

}

void LCD_displayString(const uint8_t *Str)
{
	uint8_t i=0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
}
void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); /* Clearing The LCD*/
}
void LCD_goToRowColumn(uint8_t row,uint8_t col)
{
	uint8_t address;
	switch(row)
	{
	case 0:
		address=col;
		break;
	case 1:
		address= (0x40) + col;
		break;
	case 2:
		address= (0x10) + col;
		break;
	case 3:
		address= (0x50) + col;
	}
	LCD_sendCommand(SET_CURSOR_LOCATION | address);
}
void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const uint8_t *Str)
{
	LCD_goToRowColumn(row,col);
	LCD_displayString(Str);
}

/*Helper Functions For ITOA*/
void swap(uint8_t *x, uint8_t *y) {
	uint8_t t = *x; *x = *y; *y = t;
}

// Function to reverse `buffer[i…j]`
uint8_t* reverse(uint8_t *buffer, uint32_t i, uint32_t j)
{
    while (i < j) {
        swap(&buffer[i++], &buffer[j--]);
    }

    return buffer;
}

// Iterative function to implement `itoa()` function in C
uint8_t* ITOA(uint32_t value, uint8_t* buffer, uint32_t base)
{
    // invalid input
    if (base < 2 || base > 32) {
        return buffer;
    }

    // consider the absolute value of the number
    uint32_t n = abs(value);

    uint32_t i = 0;
    while (n)
    {
        int r = n % base;

        if (r >= 10) {
            buffer[i++] = 65 + (r - 10);
        }
        else {
            buffer[i++] = 48 + r;
        }

        n = n / base;
    }

    // if the number is 0
    if (i == 0) {
        buffer[i++] = '0';
    }

    // If the base is 10 and the value is negative, the resulting string
    // is preceded with a minus sign (-)
    // With any other base, value is always considered unsigned
    if (value < 0 && base == 10) {
        buffer[i++] = '-';
    }

    buffer[i] = '\0'; // null terminate string

    // reverse the string and return it
    return reverse(buffer, 0, i - 1);
}
void LCD_integerToString(uint32_t data)
{
	uint8_t buffer[32];
	ITOA(data,buffer,10);
	LCD_displayString(buffer);
}
