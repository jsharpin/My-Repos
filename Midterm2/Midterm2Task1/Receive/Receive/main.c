/*
 * Receive.c
 *
 * Created: 4/29/2018 12:12:24 PM
 * Author : JSharpHalpin
 */ 

#define F_CPU 16000000UL			//set clock rate

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdbool.h>
#include <string.h>
#include <util/delay.h>
#include <stdio.h>
#include "nrf24l01.h"
nRF24L01 *setup_rf(void);
void process_message(char *message);

inline void prepare_led_pin(void);	//set led pin
inline void set_led_high(void);		//turn on led
inline void set_led_low(void);		//turn off led
volatile bool rf_interrupt = false;

int main(void) {
	uint8_t address[5] = { 0x22, 0x55, 0x33, 0x88, 0x46 };	//set addres to look for
	prepare_led_pin();
	sei();				//allow interrupts
	
	nRF24L01 *rf = setup_rf();			//set rf pointer
	nRF24L01_listen(rf, 0, address);	//check for communication from given address
	uint8_t addr[5];
	nRF24L01_read_register(rf, 0x00, addr, 1);
	while (true) {
		if (rf_interrupt) {				//check rf interrupt variable
			rf_interrupt = false;
			while (nRF24L01_data_received(rf)) {		//if data is received continue into loop
				nRF24L01Message msg;
				nRF24L01_read_received_data(rf, &msg);	//get message from rf
				process_message((char *)msg.data);		//convert data
			}
			nRF24L01_listen(rf, 0, address);
		}
	}
	return 0;
}

nRF24L01 *setup_rf(void) {				//initialize the rf communication
	nRF24L01 *rf = nRF24L01_init();
	rf->ss.port = &PORTB;
	rf->ss.pin = PB2;
	rf->ce.port = &PORTB;
	rf->ce.pin = PB1;
	rf->sck.port = &PORTB;
	rf->sck.pin = PB5;
	rf->mosi.port = &PORTB;
	rf->mosi.pin = PB3;
	rf->miso.port = &PORTB;
	rf->miso.pin = PB4;
	// interrupt on falling edge of INT0 (PD2)
	EICRA |= _BV(ISC01);
	EIMSK |= _BV(INT0);
	nRF24L01_begin(rf);
	return rf;
}
void process_message(char *message) {
	if (strcmp(message, "ON") == 0)
	set_led_high();
	else if (strcmp(message, "OFF") == 0)
	set_led_low();
}
inline void prepare_led_pin(void) {
	DDRB |= _BV(PB0);
	PORTB &= ~_BV(PB0);
}
inline void set_led_high(void) {
	PORTB |= _BV(PB0);
}
inline void set_led_low(void) {
	PORTB &= ~_BV(PB0);
}
// nRF24L01 interrupt
ISR(INT0_vect) {
	rf_interrupt = true;
}