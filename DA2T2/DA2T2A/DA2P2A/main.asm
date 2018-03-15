;
; DA2P2A.asm
;
; Created: 3/12/2018 8:07:59 PM
; Author : JSharpHalpin
;


.ORG 0x00
MAIN:
	LDI R16, 32
	SBI DDRB, 5			;set PORTB 5 to output
	LDI R17, 0
	LDI R18, 0
	OUT DDRD, R18			;set DDRD to input
	LDI R20, 13
	STS TCCR1B, R20			;set prescaler to 1024
	IN R20, PIND			;get input values
	ANDI R20, 0b00000010	;bitmask input value
	CPI R20, 0b00000010		;check if button was pressed
	BRNE MAIN
begin:
	RCALL delay				;call delay function
	EOR R17, R16			;xor 32 with 0
	OUT PORTB, R17			;output to PORTB 5
	RJMP begin
delay:
	LDS R29, TCNT1H			;get the upper half of counter
	LDS R28, TCNT1L			;get lower half of counter
	CPI R28, 0xF3			;check if TCNT1L is 0xF3
	BRSH body				;branch if same or higher
	RJMP delay				;jump to delay
body:
	CPI R29, 0x00			;check if TCNT1H is 0x00
	BRSH done				;branch if same or higher
	RJMP delay				;jump to delay
done:
	LDI R20, 0x00
	STS TCNT1H, R20			;reset TCNT1H to 0
	LDI R20, 0x00
	STS TCNT1L, R20			;reset TCNT1L to 0
	RET
