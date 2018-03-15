/*
 * DA2P5C.c
 *
 * Created: 3/13/2018 6:46:21 PM
 * Author : JSharpHalpin
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vectJ)		//INT0 interrupt function
{
	PORTB = 0xFF;	//set PORTB output to FF
	_delay_ms(250);	//delay for 250ms
	PORTB = 0x00;	//set PORTB output to 0
}


int main(void)
{
    DDRB = 0xFF;	//set PORTB to output
	EICRA = 0x03;	//set external interrupt to rising edge
	EIMSK = (1 << INT0);	//clear INT0 flag
	EIFR = (1 << INTF0);	//clear external interrupt flag
	sei();			//set interrupts
	
    while (1) 
    {
    }
}

