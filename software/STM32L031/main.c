#include "stm32l0xx.h"
#include "stdint.h"

// user defined code
#include "xprintf.h"

// local functions used by the UI
static void sleep(uint32_t delay);


int main(void) {
	__disable_irq();
	uint8_t idx=0;

	// configure clock source MSI, 2.097MHz
	RCC->CR |= RCC_CR_MSION;
	RCC->ICSCR = (RCC->ICSCR&(~RCC_ICSCR_MSIRANGE_Msk))|RCC_ICSCR_MSIRANGE_5; // aprox. 2.097 MHz (reset value)
	while(0==(RCC->CR&RCC_CR_MSIRDY)) {
		asm volatile("nop");
	}

	// configure PA4, PA5, PA6 as output
	RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
	GPIOA->MODER &= ~(GPIO_MODER_MODE4_Msk|GPIO_MODER_MODE5_Msk|GPIO_MODER_MODE6_Msk);
	GPIOA->MODER |= GPIO_MODER_MODE4_0 | GPIO_MODER_MODE5_0 | GPIO_MODER_MODE6_0;

	// PA9 and PA12 as AF1
	GPIOA->MODER &= ~(GPIO_MODER_MODE9_Msk|GPIO_MODER_MODE10_Msk);
	GPIOA->MODER |= GPIO_MODER_MODE9_1 | GPIO_MODER_MODE10_1;
	GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9|GPIO_AFRH_AFSEL10);
	GPIOA->AFR[1] |= ((1<<GPIO_AFRH_AFSEL9_Pos)|(1<<GPIO_AFRH_AFSEL10_Pos));

	// I2C1 enabled
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	I2C1->CR1 = (2<<I2C_CR1_DNF_Pos);
	I2C1->CR2 = 0;
	I2C1->TIMINGR = (4<<I2C_TIMINGR_PRESC_Pos) | (3<<I2C_TIMINGR_SCLDEL_Pos) | (3<<I2C_TIMINGR_SDADEL_Pos)
			| (3<<I2C_TIMINGR_SCLH_Pos) | (3<<I2C_TIMINGR_SCLL_Pos);




	// blink
	while(1) {
		switch(idx) {
		case 0:
			GPIOA->BSRR = GPIO_BSRR_BS_4;
			break;
		case 1:
			GPIOA->BSRR = GPIO_BSRR_BS_5;
			break;
		case 2:
			GPIOA->BSRR = GPIO_BSRR_BS_6;
			break;
		}
		sleep(0x0FFF);

		switch(idx) {
		case 0:
			GPIOA->BSRR = GPIO_BSRR_BR_4;
			break;
		case 1:
			GPIOA->BSRR = GPIO_BSRR_BR_5;
			break;
		case 2:
			GPIOA->BSRR = GPIO_BSRR_BR_6;
			break;;
		}
		idx++;
		if(2<idx) {
			idx=0;
		}
		sleep(0xFFFF);
	}
   	return 0;
}

static void sleep(uint32_t delay) {
	volatile uint32_t cnt;
	for(cnt = 0; cnt < delay; cnt ++) {
		asm volatile("nop");
	}
}

