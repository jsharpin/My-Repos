;
; DA2P3A.asm
;
; Created: 3/13/2018 4:43:53 PM
; Author : JSharpHalpin
;


.org 0
	LDI R16, 32	
	SBI DDRB, 5			;set PORTB 5 to output
	LDI R17, 0
	OUT PORTB, R17		;set PORTB output to 0
	LDI R20, 5
	STS TCCR0B, R20		;set prescaler to 1024
	LDI R20, 0xF3
	STS OCR0A, R20		;set OCR0A to F3
begin:
	RCALL delay			;call delay function
	EOR R17, R16		;xor 32 with 0
	OUT PORTB, R17		;output to PORTB
	RJMP begin			;jump to begin
delay:
	LDS R19, TCNT0		;get TCNT0 value
	CPI R19, 0xF3		;check if counter equals 0xF3
	BRSH done			;branch if same or higher
	RJMP delay			;jump to delay
done: 
	LDI R20, 0x00
	STS TCNT0, R20		;reset counter to 0
	RET