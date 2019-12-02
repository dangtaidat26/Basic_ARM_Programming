;*****************************************************************************;
;Brief: This program is used to blink internal Green LED on FRDM-KL46Z board  
;Name:  Dang Tai Dat
;Date:  14/11/2019
;Class:  CMPE-250
;Section:  Midterm Project
;------------------------------------------------------------------------------
; Assembler Directives
			THUMB
;*****************************************************************************;
			AREA    Addr_const, DATA, READONLY

GPIO_PORTD_PTOR     	EQU 	0xF80FF0CC
GPIO_PORTD_PDDR     	EQU 	0xF80FF0D4 ;Fast GPIOD BASE: 0xF80FF0C0 PDDR's offset: 0x14, Slow GPIOD BASE is 400FF0C0
GPIO_PORTD_PCR      	EQU 	0x4004C000 ; PORTD_PCR_BASE
GPIO_PORTD_P5_SHIFT 	EQU		(0x01 << 5) 
GPIO_PORTD_PCR5			EQU 	0x4004C014 ;Pin 5 is Green LED
SIM_BASE_SCGC5      	EQU 	0x40048038
SIM_SCGC5_PORTD_MASK  	EQU 	0x1000   ; port D Clock Gating Control
PORT_PCR_MUX_MASK   	EQU 	0x700
PORT_PCR_MUX_SHIFT  	EQU 	0x08
DELAY 					EQU 	5000000

;*****************************************************************************;
;Replace some MASK to blink Red LED:										  ;
;	SIM_SCGC5_PORTD_MASK by SIM_SCGC5_PORTE_MASK: 0x2000					  ;
;	GPIO_PORTE_PCR29							: 0x4004D074				  ;
;	GPIO_PORTE_P29_SHIFT 						: (0x01 << 29) 				  ;
;*****************************************************************************;
			AREA MyCode, CODE, READONLY
			ENTRY
			;EXPORT main
main
;Enable clock for PORTD
;SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK
			LDR R1, =SIM_BASE_SCGC5 		;Assign R1 as address of SIM->SCGC5
			LDR R0, [R1]					;Use SIM->SCGC5's address value to implement logicial operation
			LDR R2, =SIM_SCGC5_PORTD_MASK	;Assign R2 PORTD_MASK
			ORRS R0, R2, R0					;This enable clock signal in logic 
			STR R0, [R1]					;This complete enabling clock signal
											;_value in SIM->SCGC5 is changed after logicial or bitwise operation

;Mux control
;PORTD->PCR[5] = PORT_PCR_MUX(1)	
;PORT_PCR_MUX(x) : (((uint32_t)(((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)
;GPIO_PORTD_PCR5 :  0x4004C014 This value is Equated in Addr_const field
			LDR R2, =0x01
			LSLS R3, R2, #PORT_PCR_MUX_SHIFT ;this make R3 stores the value (1 << 8) or GPIO
			LDR R2, =PORT_PCR_MUX_MASK
			ANDS R2, R3, R2					 ;This make R2 stores the value (((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)
			LDR R1, =GPIO_PORTD_PCR5
			LDR R0, [R1]
			LDR R4, =0xFFFFF8FF
			ANDS R0, R4, R0
			ORRS R0, R2, R0
			STR R0, [R1]					 ;This make R1 or PTD5 stores the value (((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)


;Set the direction for PORTD
;GPIOD->PDDR |= (1u << 5);
			LDR R1, =GPIO_PORTD_PDDR 		;Load address constant 
			LDR R0, [R1]					;Make R0 points to GPIOD->PDDR
			LDR R2, =GPIO_PORTD_P5_SHIFT	;The mask stands for (1 << 5)
			ORRS R0, R0, R2					;This set bit 5 of PORTD_DDR to 1
			STR R0, [R1]					;This completes above logicial bitwise operation 
			
			
;Infinite loop LED_BLINK
LED_BLINK
;Set the data for PORTD to turn LED off
;PTD->PTOR |= (1u << 5)
			LDR R1, =GPIO_PORTD_PTOR		
			LDR R0, [R1]
			LDR R2, =GPIO_PORTD_P5_SHIFT
			ORRS R0, R0, R2					;Toggle current output register. Output <- 1. The LED will be turned off 
			STR R0, [R1]


;Delay loop
			LDR R3, =DELAY
delay1
			SUBS R3, #1 					; decrease R3, this sets N,Z,V,C status bits
			BNE delay1  					; if zero hasn't been reached yet, keep on decreasing
			
;Set the data for PORTD to turn LED off
			LDR R1, =GPIO_PORTD_PTOR
			LDR R0, [R1]
			LDR R2, =GPIO_PORTD_P5_SHIFT
			ORRS R0, R0, R2					;Toggle current output register. Output <- 0. The LED will be turned on
			STR R0, [R1]

;Delay loop
			LDR R3, =DELAY
delay2
			SUBS R3, #1						; decrement R3, this sets N,Z,V,C status bits		 					
			BNE delay2						; if zero hasn't been reached yet, keep on decrementing
			B LED_BLINK
			ALIGN
			END