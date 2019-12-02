#include "MKL46Z4.h"

//#define SysTick_CTRL_CLKSOURCE_Msk (1 << 2)
//#define SysTick_CTRL_TICKINT_Msk (1 << 1)
//#define SysTick_CTRL_ENABLE_Msk (1 << 0)
// SystemCoreClock = 8.000.000

uint32_t volatile msTicks = 0; // Interval counter in ms
void init_SysTick_interrupt()
{
	SysTick->LOAD = SystemCoreClock / 1000; //configured the SysTick to count in 1ms
	/* Select Core Clock & Enable SysTick & Enable Interrupt */
	SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk |SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void InitLED(void)
{ 
	/* Init Green LED */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //This enables the clock to PORTD:	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[5] = PORT_PCR_MUX(1); //This sets the Mux control of PTD5 to "001": PORTD->PCR[5] = PORT_PCR_MUX(1)
	GPIOD->PDDR |= (1 << 5); //This sets PTD5 as an output. There are no masks defined for each pin so we have to do it by hand.
}



void SysTick_Handler (void)
{ 
	// SysTick interrupt Handler
	msTicks++; // Increment counter
}


void Delay (uint32_t TICK)
{
	while (msTicks < TICK); // Wait 500ms
	msTicks = 0; // Reset counter
}


void blink(void)
{
	PTD->PDOR |= (1 << 5);
	Delay(500);
	PTD->PDOR &= (0 << 5);
	Delay(500);
}
