/*
 * DA2P2C.c
 *
 * Created: 3/13/2018 4:35:16 PM
 * Author : JSharpHalpin
 */ 

#include <avr/io.h>
#include <avr/delay.h>

int main(void)
{
	DDRD = 0x00;	//set DDRD to read input
	DDRB = 0xFF;	//set DDRB to output
	
	while(1)
	{
		if((PIND & 0b00000001) == 0b00000001)	//check if the button was pressed
		{
			PORTB |= 0b00000010;	//set PORTB 1 to output
			_delay_ms(250);			//delay 250ms
		}
		else
			PORTB &= 0b11111101;	//toggle PORTB output
	}	
}