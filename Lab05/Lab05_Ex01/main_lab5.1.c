#include "MKL46Z4.h"
#include "Config_lab5.1.h"
int main(void)
{
	/* Configure 2 LED pins as GPIO output */
	/* Configure 2 Switch pins as GPIO input */
	Init();
	while (1)
	{
		/* Polling 2 Switches to control RED LED and GREEN LED */
		swPressed();
	}
	
}