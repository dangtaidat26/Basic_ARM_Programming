// Configure peripheral and interrupt

#include "MKL46Z4.h" // Device header

void Init(void)
{ 
	/* Init Green LED */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //This enables the clock to PORTD:	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[5] = PORT_PCR_MUX(1); //This sets the Mux control of PTD5 to "001": PORTD->PCR[5] = PORT_PCR_MUX(1)
	GPIOD->PDDR |= (1 << 5); //This sets PTD5 as an output. There are no masks defined for each pin so we have to do it by hand.
	
	/* Init Red LED */
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; //This enables the clock to PORTE:	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[29] = PORT_PCR_MUX(1); //This sets the Mux control of PTE29 to "001": PORTE->PCR[29] = PORT_PCR_MUX(1)
	GPIOE->PDDR |= (1 << 29); //This sets PTE29 as an output.
	
	/* Init Sw1 */
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; //This enables the clock to PORTC:	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // This sets mux control of PTC3 to "001" and Enable pull-up register 
	PTC->PDDR &= (0 << 3); // This set PTC3 (Sw1) as an input.
	PORTC->PCR[3] |= PORT_PCR_IRQC(0xA); /* Set value for IRQC bit field in PCR register to select falling edge (1010) interrupts for PORTC[3]. */
	
	/* Init Sw2 */
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK; //This enables the clock to PORTC:	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // This sets mux control of PTC12 to "001" and Enable pull-up register 
	PTC->PDDR &= (0 << 12); // This set PTC12 (Sw2) as an input.
	PORTC->PCR[12] |= PORT_PCR_IRQC(0xA); /* Set value for IRQC bit field in PCR register to select falling edge (1010) interrupts for PORTC[3]. */
	
	NVIC_EnableIRQ(31);									 /*Enable PORTC_PORTD_IRQHandler*/
}


// IRQ_Handler
void PORTC_PORTD_IRQHandler(void)
{
	uint32_t i, j; //Create loop variable
	
	/* When we push the SW1, RED LED will blink for 3 times before remain active */
	/* Similarly, SW2 makes GREEN LED blinks for 3 time before remain active */
	if((PTC->PDIR & (1u << 3)) == 0)
	{
		for(j = 0; j < 3; j++)
		{
			PTE->PDOR &= (0u << 29); // Set PTE29 = 0, turns RED LED ON
			for(i = 0; i < 5000000; i++){};  //Burn some time
			PTE->PDOR |= (1u << 29); //Set PTD5 = 1, turns RED LED OFF
			for(i = 0; i < 5000000; i++){};  //Burn some time
		}
	}
	
	if((PTC->PDIR & (1u << 12)) == 0)
	{
		for(j = 0; j < 3; j++)
		{
			PTD->PDOR |= (1u << 5);	//Set PTD5 = 1, turns GREEN LED OFF
			for(i = 0; i < 5000000; i++){};  //Burn some time
			PTD->PDOR &= (0u << 5); //Set PTD5 = 0, turns GREEN LED ON
			for(i = 0; i < 5000000; i++){};  //Burn some time
		}
	}
	
	/* Clear interrupt service flag in port control register otherwise int. remains active */
	PORTC->PCR[3] |= PORT_PCR_ISF_MASK;
	PORTC->PCR[12] |= PORT_PCR_ISF_MASK;
	
}


