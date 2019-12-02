#include "stdint.h"
void InitLED(void);
void init_SysTick_interrupt();
uint32_t SysTick_Configuration(uint32_t ticks);
void SysTick_Handler(void);
void Delay (uint32_t TICK);
void blink(void);