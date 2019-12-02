#include "MKL46Z4.h"
#include "Init.h"

int main(void)
{
	/* Configure LED pin as GPIO output*/
	InitLED();
	init_SysTick_interrupt();
	/* Configure SysTick to count down to zero in 5 ms */
	while (1)
	{
		blink();
		/* Call delay_using_SysTick function to wait 0.5 second */
		/* Toggle Red LED*/
	}
}
