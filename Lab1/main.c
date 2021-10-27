
#include "stm32f3xx_hal.h"

int i=0;

int main(void)
{

// Enable E register
RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
// Enable A register
RCC->AHBENR |= RCC_AHBENR_GPIOAEN;


GPIOE->MODER |= GPIO_MODER_MODER13_0; // 1 į MODER13 [x:1]
GPIOE->MODER &= ~GPIO_MODER_MODER13_1; // 0 į MODER13 [0:x] [01]

GPIOE->MODER |= GPIO_MODER_MODER12_0; // 1 į MODER13 [x:1]
GPIOE->MODER &= ~GPIO_MODER_MODER12_1; // 0 į MODER13 [0:x] [01]

GPIOE->MODER |= GPIO_MODER_MODER11_0; // 1 į MODER13 [x:1]
GPIOE->MODER &= ~GPIO_MODER_MODER11_1; // 0 į MODER13 [0:x] [01]

GPIOE->MODER |= GPIO_MODER_MODER10_0; // 1 į MODER13 [x:1]
GPIOE->MODER &= ~GPIO_MODER_MODER10_1; // 0 į MODER13 [0:x] [01]

// Button set

GPIOA->MODER &= ~GPIO_MODER_MODER0_0;


while(1)
{

	if((GPIOA->IDR & GPIO_IDR_0) == 1 )
	{
		GPIOE->BSRR |= 1<<13;

	}
	else{
		GPIOE->BSRR |= 1<<(13+16);

	}

//	GPIOE->BSRR |= 1<<12;
//	GPIOE->BSRR |= 1<<11;
//	GPIOE->BSRR |= 1<<10;
//	for(i = 0; i < 200000; i++);
//
//	GPIOE->BSRR |= 1<<(12+16);
//	GPIOE->BSRR |= 1<<(11+16);
//	GPIOE->BSRR |= 1<<(10+16);
//	for(i = 0; i < 200000; i++);
}


}
