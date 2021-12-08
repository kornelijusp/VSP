#include "stm32f3xx_hal.h"
#include "stm32f3xx_hal_gpio.h"

void Init_Tim_Gpio(void){
// ALternative Function selection
	GPIOE->MODER &= ~GPIO_MODER_MODER9_0; // AF
	GPIOE->MODER |= GPIO_MODER_MODER9_1; // AF
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_0; // Speed H
	GPIOE->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9_1; // Speed H
	GPIOE->AFR[1] |= 0b00100000; //(GPIO_AFRH_AFRH1 & 2); //0b00100000; // AF2

}

void Init_Tim(int dutty){
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Connect RCC clocks to TIM
	TIM1->PSC |= 0x0F; // Prescalller (reasonable value 0x0F, but could be any 0x00 - 0x1F)
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM1->CR1 |= TIM_CR1_ARPE;
//	We want PWM1, therefore set CCMR1 as 0110
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0; // 0
	TIM1->CCMR1 |=  TIM_CCMR1_OC1M_1; // 1
	TIM1->CCMR1 |=  TIM_CCMR1_OC1M_2; // 1
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_3; // 0
//	TIM1->CCER |= TIM_CCER_CC1NE | TIM_CCER_CC1E; //On - OC1N signal is output on the corresponding output pin depending on MOE, OSSI, OSSR, OIS1, OIS1N and CC1E bits
	TIM1->ARR = 100;
	TIM1->CCR1 = TIM1->ARR/dutty;
	// By default, after reset, preload for channel 1 is turned off */
	// To change it uncomment the below line */
	// TIMą->CCMR1 |= TIM_CCMR1_OC1PE;
	TIM1->BDTR |= TIM_BDTR_MOE; // Main to output
	TIM1->CCER |= TIM_CCER_CC1E; // Enable
	TIM1->CR1 |= TIM_CR1_CEN; // Enable
}

// void Init_Tim_PWM(int dutty){
// 	/* Reset the OC1M bits in the CCMR1 register */
// 	TIM1->CCR1 = 100/TIM1->ARR * dutty;

// 	Init_Tim(100);
// 	/* Reset the OC1M bits in the CCMR1 register */
// }


int i=0;


int main(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOEEN;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &= ~GPIO_MODER_MODER0_0;
	GPIOA->MODER &= ~GPIO_MODER_MODER0_1;
	GPIOE->MODER |= GPIO_MODER_MODER15_0;
	GPIOE->MODER &= ~GPIO_MODER_MODER15_1;



	GPIOE->BSRR |=1<<15;
	for(i = 0; i < 200000; i++);
	GPIOE->BSRR |=1<<31;


	Init_Tim_Gpio();
	Init_Tim(100);



// 21 -> desimtaine
//0b0000... -> dvejetaine
//0x.... -> sesioliktaine
// 0x15       (31-16)(15-0)  0...9 A,B,C,D,E,F

	int i = 0;
	int count = 0, brt = 0;

while(1)
{
	GPIOE->BSRR |=1<<15;

	if((GPIOA->IDR & 0x01) == 1){
		GPIOE->BSRR |=1<<31;
		count++;
		for(i = 0; i < 200000; i++);

	}
if (count > 3){
	count = 0;
}


switch(count){
case 0:
	brt = 0;
	break;
case 1:
	brt = 15;
	break;
case 2:
	brt = 8;
	break;
case 3:
	brt = 1;
	break;
}

Init_Tim(brt);



}


}
