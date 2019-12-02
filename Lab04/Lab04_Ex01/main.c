#include "MKL46Z4.h"
#include "LED.h"
int main(void)
{
	/* Configure GREEN LED pin as GPIO output */
	InitLED();
	while (1)
	{
		BlinkLED1();
	/* Delay */
	/* Toggle LED */
	}

}
