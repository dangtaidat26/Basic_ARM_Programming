#include "MKL46Z4.h"
#include "Init.h"


int main()
{
    Config_Clk_Freq();
    InitLED();
    while(1)
	{
        PTD->PDOR &= (0u << 5);
        Delay();
        PTD->PDOR |= (1u << 5);
        Delay();
	}
}
