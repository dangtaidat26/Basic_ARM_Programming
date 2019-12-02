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
	
	/* Init Sw2 */
	PORTC->PCR[12] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // This sets mux control of PTC12 to "001" and Enable pull-up register
	PTC->PDDR &= (0 << 12); // This set PTC12 (Sw2) as an input.
}
void swPressed(void)
{
	/* Pressed SW1 */
	if ((PTC->PDIR & (1 << 3)) == 0) 
	{
		PTD->PDOR |= (1 << 5); // This sets PTD5 to be 1 so the GREEN LED will be turned off.
	}
	/* unPressed SW1 */
	else
	{
		PTD->PDOR &= (0 << 5);  // This sets PTD5 to be 0 so the GREEN LED will be kept lighting up.
	}
	
	/* Pressed SW2 */
	if ((PTC -> PDIR & (1 << 12)) == 0)
	{
		PTE->PDOR |= (1 << 29); // This sets PTE29 to be 1 so the RED LED will be turned off.
	}
	/* unPressed SW2 */
	else
	{
		PTE->PDOR &= (0 << 29); // This sets PTD5 to be 0 so the RED LED will be kept lighting up.
	}
}
