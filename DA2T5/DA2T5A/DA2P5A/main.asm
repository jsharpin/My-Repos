;
; DA2P5A.asm
;
; Created: 3/13/2018 6:01:31 PM
; Author : JSharpHalpin
;


.ORG 0x00
	JMP MAIN
.ORG 0x06		;INT0 interrupt call
	JMP EX0_ISR

MAIN:
	LDI R20, HIGH(RAMEND)
	OUT SPH, R20			;set stack pointer high address
	LDI R20, LOW(RAMEND)
	OUT SPL, R20			;set stack pointer low address
	SBI DDRB, 5				;set PORTB 5 to output
	LDI R17, 0
	LDI R20, (1 << INT0)
	OUT EIMSK, R20			;clear interrupt flag
	SEI
HERE:
	JMP HERE				;jump to HERE

EX0_ISR:					;INT0 interrupt function
	LDI R20, (1 << INTF0)	;clear interrupt flag
	LDI R16, 32	
	EOR R17, R16			;xor 32 with 0
	OUT PORTB, R17			;set PORTB output
	LDI R18, 0xF3			;set loop to F3
LOOP:
	SUBI R18, 1
	CPI R18, 0x00			;check when R18 equals 0
	BRNE LOOP
	LDI R20, 0x00
	STS TCNT0, R20			;reset counter value to 0
	RETI