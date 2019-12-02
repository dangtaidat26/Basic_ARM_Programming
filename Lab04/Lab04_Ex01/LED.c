#include "MKL46Z4.h" // Device header

void InitLED(void)
{ 
	/* This function enables the red LED on the FRDM-KL46Z development board */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //This enables the clock to PORTD	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTD->PCR[5] = PORT_PCR_MUX(1); //This sets the Mux control of PTD5 to 001, or GPIO	PORTD->PCR[5] = PORT_PCR_MUX(1);
	GPIOD->PDDR |=(1u << 5); //This sets PTD5 as an output. There are no masks defined for each pin so we have to do it by hand.
}
void BlinkLED1(void)
{
	/* This method turns the LED off, then back on using two separate commands */
	uint32_t i = 0; //Create a loop variable
	PTD->PDOR |= (1u << 5);	//Set PTD5 = 1, turns LED OFF (Cathode connected to PTD5)
  	for(i = 0; i < 5000000; i++){};  //Burn some time
	PTD->PDOR &= ~((uint32_t)(1u << 5)); //Clear PTD5 = 0, turns LED ON
	for(i=0; i < 5000000; i++){}; //Burn some time
}

void BlinkLED2(void)
{
	/* This method turns the LED off, then back on using two separate commands. */
	uint32_t i = 0; //Create a loop variable
	PTD->PSOR |= (1u << 5); //Set output register = 1, turns LED OFF (Cathode connected to PTD5)
  	for(i = 0; i < 5000000; i++){};  //Burn some time
	PTD->PCOR |= (1u << 5); //Clear current output, output register will be 0, turns LED ON
	for(i = 0; i < 5000000; i++){};  //Burn some time
}


void BlinkLED3(void)
{
	/* This method turns the LED off, then back on using two separate commands. */
	uint32_t i = 0; //Create a loop variable
	PTD->PTOR |= (1u << 5);	// Toggle current output register. Output <- 1. The LED will be turned off 
  	for(i = 0; i < 5000000; i++){};  //Burn some time
	PTD->PTOR |= (1u << 5); // Toggle current output register. Output <- 0. The LED will be turned on
	for(i = 0; i < 5000000; i++){};  //Burn some time
}

