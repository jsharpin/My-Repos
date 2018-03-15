/*
 * DA2P1C.c
 *
 * Created: 3/12/2018 7:53:51 PM
 * Author : JSharpHalpin
 */ 


#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	DDRB = 32;		//set PORTB 5 to output
	TCCR1B = 13;	//set prescaler to 1024
	TCNT1 = 0;		//set counter to 0
	OCR1A = 0x00F3;	//set value to count to
	
	while(1)
	{
		if((TIFR1 & 0b00000001) == 0b000000001)	//check for overflow
		{
			PORTB = 0xFF;		//set output of PORTB to 1
			_delay_ms(250);		//stay on for 250ms
			TCNT1 = 0;			//reset counter to 0
		}
		else
			PORTB = 0x00;		//set output of PORTB to 0
	}
}