

#include "gpio.h"



void gpioInit(void)
{

	// Enable clocks
	RCC->AHB2ENR1 |= RCC_AHB2ENR1_GPIOAEN |
									RCC_AHB2ENR1_GPIOBEN |
									RCC_AHB2ENR1_GPIOCEN;
	
		// AD403x-24 Pins
	gpioInitPin(ADC_NCS_Port, ADC_NCS_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_FAST, GPIO_PULL_UP);
	gpioInitPin(ADC_NRESET_Port, ADC_NRESET_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_UP);
	gpioInitPin(BUSY_C_Port, BUSY_C_Pin, GPIO_INPUT, GPIO_PUSH_PULL, GPIO_SPEED_FAST, GPIO_NO_PUPD);
	gpioSetPin(ADC_NCS_Port, ADC_NCS_Pin);
	gpioSetPin(ADC_NRESET_Port, ADC_NRESET_Pin);
	
	
		// Relay Control Pins
	gpioInitPin(K1_S_L_Port, K1_S_L_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioInitPin(K2_S_L_Port, K2_S_L_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioInitPin(K3_S_L_Port, K3_S_L_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioInitPin(K1_R_L_Port, K1_R_L_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioInitPin(K2_R_L_Port, K2_R_L_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioInitPin(K3_R_L_Port, K3_R_L_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	GPIOA->BSRR |= (1U << (K1_S_L_Pin + 16)) | (1U << (K2_S_L_Pin + 16)) | (1U << (K3_S_L_Pin + 16));
	GPIOB->BSRR |= (1U << (K1_R_L_Pin + 16)) | (1U << (K2_R_L_Pin + 16)) | (1U << (K3_R_L_Pin + 16));
	
		// Gain SW Pins
	gpioInitPin(GAIN_40_DB_Port, GAIN_40_DB_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioInitPin(GAIN_60_DB_Port, GAIN_60_DB_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioSetPin(GAIN_40_DB_Port, GAIN_40_DB_Pin);
	gpioResetPin(GAIN_60_DB_Port, GAIN_60_DB_Pin);
	
		// AD5686 Pins
	gpioInitPin(DAC_NRESET_Port, DAC_NRESET_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_UP);
	gpioSetPin(DAC_NRESET_Port, DAC_NRESET_Pin);
	
		// VBATT ADC Pins
	gpioInitPin(VBATT_ADC_SW_Port, VBATT_ADC_SW_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioResetPin(VBATT_ADC_SW_Port, VBATT_ADC_SW_Pin);
		
		// Configure General IO Pins
	gpioInitPin(INPUT_OVR_LED_Port, INPUT_OVR_LED_Pin, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_PULL_DOWN);
	gpioResetPin(INPUT_OVR_LED_Port, INPUT_OVR_LED_Pin);
	gpioInitPin(PG_IN_Port, PG_IN_Pin, GPIO_INPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_NO_PUPD);
	gpioInitPin(NOVR_Port, NOVR_Pin, GPIO_INPUT, GPIO_PUSH_PULL, GPIO_SPEED_LO, GPIO_NO_PUPD);
	
		// Configure EXTI lines
	interruptConfigFalling(BUSY_C_Port, BUSY_C_Pin);

}



/**************************************************
	*
	*					GENERAL PURPOSE FUNCTIONS
	*
***************************************************/


void interruptConfigRising(uint8_t gpiox, uint8_t pin)
{
	uint8_t exticr_ind = pin / 4;
	uint8_t exticr_pos = 8 * (pin % 4);
	
	
		// Configure EXTI registers
	EXTI->EXTICR[exticr_ind] &= ~(15U << exticr_pos); // Clear appropriate EXTICR bits
	EXTI->EXTICR[exticr_ind] |= (uint16_t) (gpiox << exticr_pos); // Select EXTIx configuration
	
		// Unmask Interrupt request
	EXTI->IMR1 |= (1U << pin);
	
		// Trigger selection
	EXTI->RTSR1 |= (1U << pin);
}

void interruptConfigFalling(uint8_t gpiox, uint8_t pin)
{
	uint8_t exticr_ind = pin / 4;
	uint8_t exticr_pos = 8 * (pin % 4);
	
	
		// Configure EXTI registers
	EXTI->EXTICR[exticr_ind] &= ~(15U << exticr_pos); // Clear appropriate EXTICR bits
	EXTI->EXTICR[exticr_ind] |= (uint16_t) (gpiox << exticr_pos); // Select EXTIx configuration
	
	
		// Unmask Interrupt request
	EXTI->IMR1 |= (1U << pin);
	
		// Trigger selection
	EXTI->FTSR1 |= (1U << pin);
}

void gpioInitPin(gpioPort_TypeDef port, gpioPin_TypeDef pin, gpioMode_TypeDef mode, gpioOtype_TypeDef otype, gpioSpeed_TypeDef ospeed, gpioPupd_TypeDef pupd)
{
	
	switch(port){
	
		case GPIO_PORT_A:
			GPIOA->MODER &= (uint32_t) ~(3U << (pin * 2));
			GPIOA->MODER |= (uint32_t) (mode << (pin * 2));
			
			GPIOA->OTYPER &= (uint32_t) ~(1U << pin);
			GPIOA->OTYPER |= (uint32_t) (otype << pin);
			
			GPIOA->OSPEEDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOA->OSPEEDR |= (uint32_t) (ospeed << (pin * 2));
			
			GPIOA->PUPDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOA->PUPDR |= (uint32_t) (pupd << (pin * 2));
			break;

		case GPIO_PORT_B:	
			GPIOB->MODER &= (uint32_t) ~(3U << (pin * 2));
			GPIOB->MODER |= (uint32_t) (mode << (pin * 2));
			
			GPIOB->OTYPER &= (uint32_t) ~(1U << pin);
			GPIOB->OTYPER |= (uint32_t) (otype << pin);
			
			GPIOB->OSPEEDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOB->OSPEEDR |= (uint32_t) (ospeed << (pin * 2));
			
			GPIOB->PUPDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOB->PUPDR |= (uint32_t) (pupd << (pin * 2));
			break;

		case GPIO_PORT_C:	
			GPIOC->MODER &= (uint32_t) ~(3U << (pin * 2));
			GPIOC->MODER |= (uint32_t) (mode << (pin * 2));
			
			GPIOC->OTYPER &= (uint32_t) ~(1U << pin);
			GPIOC->OTYPER |= (uint32_t) (otype << pin);
			
			GPIOC->OSPEEDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOC->OSPEEDR |= (uint32_t) (ospeed << (pin * 2));
			
			GPIOC->PUPDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOC->PUPDR |= (uint32_t) (pupd << (pin * 2));
			break;

		case GPIO_PORT_D:	
			GPIOD->MODER &= (uint32_t) ~(3U << (pin * 2));
			GPIOD->MODER |= (uint32_t) (mode << (pin * 2));
			
			GPIOD->OTYPER &= (uint32_t) ~(1U << pin);
			GPIOD->OTYPER |= (uint32_t) (otype << pin);
			
			GPIOD->OSPEEDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOD->OSPEEDR |= (uint32_t) (ospeed << (pin * 2));
			
			GPIOD->PUPDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOD->PUPDR |= (uint32_t) (pupd << (pin * 2));
			break;

		case GPIO_PORT_E:	
			GPIOE->MODER &= (uint32_t) ~(3U << (pin * 2));
			GPIOE->MODER |= (uint32_t) (mode << (pin * 2));
			
			GPIOE->OTYPER &= (uint32_t) ~(1U << pin);
			GPIOE->OTYPER |= (uint32_t) (otype << pin);
			
			GPIOE->OSPEEDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOE->OSPEEDR |= (uint32_t) (ospeed << (pin * 2));
			
			GPIOE->PUPDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOE->PUPDR |= (uint32_t) (pupd << (pin * 2));
			break;

		case GPIO_PORT_F:	
			GPIOF->MODER &= (uint32_t) ~(3U << (pin * 2));
			GPIOF->MODER |= (uint32_t) (mode << (pin * 2));
			
			GPIOF->OTYPER &= (uint32_t) ~(1U << pin);
			GPIOF->OTYPER |= (uint32_t) (otype << pin);
			
			GPIOF->OSPEEDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOF->OSPEEDR |= (uint32_t) (ospeed << (pin * 2));
			
			GPIOF->PUPDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOF->PUPDR |= (uint32_t) (pupd << (pin * 2));
			break;

		case GPIO_PORT_G:	
			GPIOG->MODER &= (uint32_t) ~(3U << (pin * 2));
			GPIOG->MODER |= (uint32_t) (mode << (pin * 2));
			
			GPIOG->OTYPER &= (uint32_t) ~(1U << pin);
			GPIOG->OTYPER |= (uint32_t) (otype << pin);
			
			GPIOG->OSPEEDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOG->OSPEEDR |= (uint32_t) (ospeed << (pin * 2));
			
			GPIOG->PUPDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOG->PUPDR |= (uint32_t) (pupd << (pin * 2));
			break;
		
		case GPIO_PORT_H:	
			GPIOH->MODER &= (uint32_t) ~(3U << (pin * 2));
			GPIOH->MODER |= (uint32_t) (mode << (pin * 2));
			
			GPIOH->OTYPER &= (uint32_t) ~(1U << pin);
			GPIOH->OTYPER |= (uint32_t) (otype << pin);
			
			GPIOH->OSPEEDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOH->OSPEEDR |= (uint32_t) (ospeed << (pin * 2));
			
			GPIOH->PUPDR &= (uint32_t) ~(3U << (pin * 2));
			GPIOH->PUPDR |= (uint32_t) (pupd << (pin * 2));
			break;
	}
}

void gpioSetAF(gpioPort_TypeDef port, gpioPin_TypeDef pin, gpioAF_TypeDef AF)
{
	uint8_t afr = pin/8;
	uint8_t af_shift = 4 * (pin % 8);
	
		switch(port){
			case GPIO_PORT_A:
				GPIOA->AFR[afr] &= ~(15U << af_shift);
				GPIOA->AFR[afr] |= (uint32_t) (AF << af_shift);
				break;
			case GPIO_PORT_B:
				GPIOB->AFR[afr] &= ~(15U << af_shift);
				GPIOB->AFR[afr] |= (uint32_t) (AF << af_shift);
				break;
			case GPIO_PORT_C:
				GPIOC->AFR[afr] &= ~(15U << af_shift);
				GPIOC->AFR[afr] |= (uint32_t) (AF << af_shift);
				break;
			case GPIO_PORT_D:
				GPIOD->AFR[afr] &= ~(15U << af_shift);
				GPIOD->AFR[afr] |= (uint32_t) (AF << af_shift);
				break;
			case GPIO_PORT_E:
				GPIOE->AFR[afr] &= ~(15U << af_shift);
				GPIOE->AFR[afr] |= (uint32_t) (AF << af_shift);
				break;
			case GPIO_PORT_F:
				GPIOF->AFR[afr] &= ~(15U << af_shift);
				GPIOF->AFR[afr] |= (uint32_t) (AF << af_shift);
				break;
			case GPIO_PORT_G:
				GPIOG->AFR[afr] &= ~(15U << af_shift);
				GPIOG->AFR[afr] |= (uint32_t) (AF << af_shift);
				break;
			case GPIO_PORT_H:
				GPIOH->AFR[afr] &= ~(15U << af_shift);
				GPIOH->AFR[afr] |= (uint32_t) (AF << af_shift);
				break;
												
	}
}

void gpioSetPin(gpioPort_TypeDef port, gpioPin_TypeDef pin)
{
	
		switch(port){
			case GPIO_PORT_A:
				GPIOA->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_B:
				GPIOB->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_C:
				GPIOC->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_D:
				GPIOD->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_E:
				GPIOE->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_F:
				GPIOF->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_G:
				GPIOG->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_H:
				GPIOH->BSRR |= (1U << pin);
				break;
												
	}
}

void gpioResetPin(gpioPort_TypeDef port, gpioPin_TypeDef pin)
{
	pin += 16;
	
		switch(port){
			case GPIO_PORT_A:
				GPIOA->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_B:
				GPIOB->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_C:
				GPIOC->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_D:
				GPIOD->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_E:
				GPIOE->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_F:
				GPIOF->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_G:
				GPIOG->BSRR |= (1U << pin);
				break;
			case GPIO_PORT_H:
				GPIOH->BSRR |= (1U << pin);
				break;
												
	}
}
