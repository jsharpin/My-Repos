;
; DA2P4A.asm
;
; Created: 3/13/2018 5:18:25 PM
; Author : JSharpHalpin
;


.ORG 0x00
	JMP MAIN
.ORG 0x20		//timer overflow interrupt
	JMP T0_OV_ISR

MAIN:
	LDI R20, HIGH(RAMEND)
	OUT SPH, R20			;set stack pointer high address
	LDI R20, LOW(RAMEND)
	OUT SPL, R20			;set stack pointer low address
	LDI R17, 0
	SBI DDRB, 5				;set PORTB 5 to output
	LDI R20, 13
	STS TCCR0B, R20			;set prescaler to 1024
	LDI R20, 71
	STS OCR0A, R20			;set max value
	LDI R20, (1 << TOIE0)
	OUT TIFR0, R20			;clear interrupt bit
	SEI						;set interrupt bit
begin:
	RJMP begin				;start poling

T0_OV_ISR:
	LDI R20, (1 << TOIE0)	;get flag bit
	OUT TIFR0, R20			;clear flag bit
	LDI R16, 32
	EOR R17, R16			;xor 32 with 0
	OUT PORTB, R17			;output PORTB
	LDI R18, 0xF3			;set loop value
LOOP:
	SUBI R18, 1
	CPI R18, 0				;check if R18 equals 0
	BRNE LOOP				;loop till R18 is 0
	LDI R20, 0x00
	STS TCNT0, R20			;reset counter value to 0
	RETI