/*
 * DA2P3C.c
 *
 * Created: 3/13/2018 4:50:01 PM
 * Author : JSharpHalpin
 */ 

#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	DDRB = 32;		//set PORTB 5 to output
	TCCR0B = 13;	//set prescaler to 1024
	TCNT0 = 0;		//set TCNT to 0
	OCR0A = 0x00F3;	//set max value to F3
	
    while (1) 
    {
		if((TIFR0 & 0b00000001) == 0b00000001)	//check for overflow
		{
			PORTB = 0xFF;		//set PORTB to FF
			_delay_ms(250);		//delay for 250ms
			TCNT0 = 0;			//reset counter to 0
		}
		else
			PORTB = 0x00;		//set PORTB to 0
    }
}

