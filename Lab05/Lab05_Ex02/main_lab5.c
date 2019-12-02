#include "MKL46Z4.h"
#include "startup.h"

int main(void)
{
	Init();
	while(1)
	{
		uint32_t i;
		PTD->PDOR &= (0u << 5); //Set PTD5 = 0, turns GREEN LED ON
		PTE->PDOR &= (0u << 29); // Set PTE29 = 0, turns RED LED ON
		for(i = 0; i < 5000000; i++){};  //Burn some time
		PTD->PDOR |= (1u << 5);	//Set PTD5 = 1, turns GREEN LED OFF
		PTE->PDOR |= (1u << 29); //Set PTD5 = 1, turns RED LED OFF
		for(i = 0; i < 5000000; i++){};  //Burn some time
	}		

}
