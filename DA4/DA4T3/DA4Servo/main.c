/*
 * DA4Servo.c
 *
 * Created: 4/10/2018 7:13:25 PM
 * Author : JSharpHalpin
 */ 

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    int i;
	DDRD = 0xFF;
	TCCR0B = 3;
	TCCR0A = 0x83;
	
    while (1) 
    {
		for(i=0; i<10; i++)
		{
			OCR0A = 15;
			_delay_ms(1000);
			OCR0A = 30;
			_delay_ms(1000);
		}
    }
}

