#include "MKL46Z4.h"


void InitLED(void)
{ 
	/* Init Green LED */
	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK; //This enables the clock to PORTD:	SIM->SCGC5 |= SIM_SCGC5_PORTD_MASK;
	PORTD->PCR[5] = PORT_PCR_MUX(1); //This sets the Mux control of PTD5 to "001": PORTD->PCR[5] = PORT_PCR_MUX(1)
	GPIOD->PDDR |= (1u << 5); //This sets PTD5 as an output. There are no masks defined for each pin so we have to do it by hand.
}

void Config_Clk_Freq(void)
{
      // set a safe value for divider
    SIM->CLKDIV1 |= SIM_CLKDIV1_OUTDIV4_MASK | SIM_CLKDIV1_OUTDIV1_MASK;
    MCG->C1 |= MCG_C1_IREFS_MASK; // Slow Internal clock : 32768 Hz - FLL
    MCG->C4 |= MCG_C4_DMX32_MASK | MCG_C4_DRST_DRS(1);// 32768 * 1464 = 47.972.352 Hz ~ 48MHz
    MCG->C1 &= ~MCG_C1_CLKS_MASK; // Output of FLL is selected for MCGOUTCLK
    while((MCG->S & MCG_S_IREFST_MASK) == 0); // wait for Internal clock is selected
    while((MCG->S & MCG_S_CLKST_MASK) != 0); // wait for FLL is selected
    SIM->CLKDIV1 = SIM_CLKDIV1_OUTDIV1(1 - 1) |  // core/system clock = MCGOUTCLK / 1 = 48 / 1 = 48MHz
                   SIM_CLKDIV1_OUTDIV4(2 - 1);   // flash/bus clock = core/system / 2 = 24MHz
}
