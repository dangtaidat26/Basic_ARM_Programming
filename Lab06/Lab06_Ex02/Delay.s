			THUMB
; Delay.s
; Delay function
; generate 100 ms delay from System clock = 48 MHz (47.972.352 Hz)
; Input: R0 contain iteration number
; Time for each instruction:
; Refer at: http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.ddi0484b/CHDCICDF.html
; LDR takes about 2 clock cycles
; SUBS takes about 1 clock cycle
; CMP takes about 1 clock cycle
; B<cc> <label> (conditional branch) takes 2 cycle if taken, 1 cycle if not
; B     <label> (unconditional branch) takes 1 cycle
; => number of clock cycle = 2 + 4 * numOfLoop. 100ms =>  47972350 cycles => numOfLoop should be 1.199.309

			AREA DelayA, CODE, READONLY ; declare code area
			ENTRY
			EXPORT Delay ; make delay function visible to main()
Delay
			LDR r0, =1199309
LOOP
			SUBS r0,r0,#1
			CMP r0, #0
			BEQ LOOPEND
			B LOOP
LOOPEND
			END
