#include "MKL46Z4.h" // Device header

void InitLED(void)
{ 
	/*This function enables RED LED and GREEN LED on the FRDM-KL46Z development board */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //This enables the clock to PORTD:	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; //This enables the clock to PORTE:	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTD->PCR[5] = PORT_PCR_MUX(1); //This sets the Mux control of PTD5 to 001, or GPIO:	PORTD->PCR[5] = PORT_PCR_MUX(1);
	PORTE->PCR[29] = PORT_PCR_MUX(1); //This sets the Mux control of PTE29 to 001, or GPIO:	PORTE->PCR[29] = PORT_PCR_MUX(1);
	GPIOD->PDDR |=(1u << 5); //This sets PTD5 as an output. There are no masks defined for each pin so we have to do it by hand.
	GPIOE->PDDR |= (1u << 29); //This sets PTE29 as an output. There are no masks defined for each pin so we have to do it by hand.
}

void BlinkTwoLED(void)
{
	/* This method turns Each LED off, then back on oppositely. */
	uint32_t i = 0; //Create a loop variable
	PTD->PDOR |= (1u << 5);	//Set PTD5 = 1, turns GREEN LED OFF
	PTE->PDOR &= (0u << 29); // Set PTE29 = 0, turns RED LED ON
  	for(i = 0; i < 5000000; i++){};  //Burn some time
	PTD->PDOR &= (0u << 5); //Set PTD5 = 0, turns GREEN LED ON
	PTE->PDOR |= (1u << 29); //Set PTD5 = 1, turns RED LED OFF
	for(i = 0; i < 5000000; i++){};  //Burn some time
}

