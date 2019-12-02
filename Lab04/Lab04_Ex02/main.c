#include "MKL46Z4.h"
#include "LED.h"
int main(void)
{
/* Configure RED LED pin as GPIO output*/
	InitLED();
	while (1)
	{
		BlinkTwoLED();
	/* Delay */
	/* Toggle LED */
	}
	
}