

#include "tim.h"
#include "gpio.h"


#define TIM_DISABLE(_CHNUM) void TIM##_CHNUM##Disable(void){ TIM##_CHNUM->CR1 &= ~TIM_CR1_CEN;}

TIM_DISABLE(1)
TIM_DISABLE(2)
TIM_DISABLE(3)
TIM_DISABLE(4)
TIM_DISABLE(5)
TIM_DISABLE(6)
TIM_DISABLE(7)
TIM_DISABLE(8)
TIM_DISABLE(15)

#undef TIM_DISABLE

void TIM2Init(void)
{
	
	/* Set GPIOs */
	gpioInitPin(TIM2_CH1_PORT, TIM2_CH1_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM2_CH3_PORT, TIM2_CH3_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioSetAF(TIM2_CH1_PORT, TIM2_CH1_PIN, TIM2_CH1_AF);
	gpioSetAF(TIM2_CH3_PORT, TIM2_CH3_PIN, TIM2_CH3_AF);
	

	
	TIM2->CR1 |= TIM_CR1_URS;
	TIM2->CR2 |= (1U << TIM_CR2_MMS_Pos); // CNT_EN used as tim_trgo
	
	TIM2->CCMR1 |= (6U << TIM_CCMR1_OC1M_Pos) 	// CH1:  PWM Mode 1
								| TIM_CCMR1_OC1PE							// Output 1 Preload Enable
								|	TIM_CCMR1_OC1FE;						// Output 1 Fast mode enable

	
	TIM2->CCMR2 |= (4U << TIM_CCMR2_OC3M_Pos) 	// CH3: Combined PWM Mode 1
								| (1U << 16)									// Noncontiguous MSB for OC3M
								| TIM_CCMR2_OC3PE							// Output 1 Preload Enable
								|	TIM_CCMR2_OC3FE 						// Output 1 Fast mode enable
								| (7U << TIM_CCMR2_OC4M_Pos) 	// CH4: PWM Mode 2
								| TIM_CCMR2_OC4PE						// Output 1 Preload Enable
								|	TIM_CCMR2_OC4FE;						// Output 1 Fast mode enable
								
	TIM2->CCER |= TIM_CCER_CC3P;	// Invert polarity of CH3
	TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E;	// Enable Capture Compare 1, 3 & 4

}

void TIM3Init(void)
{
	
	/* Set GPIOs */
	gpioInitPin(TIM3_CH1_PORT, TIM3_CH1_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM3_CH3_PORT, TIM3_CH3_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioSetAF(TIM3_CH1_PORT, TIM3_CH1_PIN, TIM3_CH1_AF);
	gpioSetAF(TIM3_CH3_PORT, TIM3_CH3_PIN, TIM3_CH3_AF);
	
	TIM3->CR1 |= TIM_CR1_URS;
	TIM3->CR2 |= (2U << TIM_CR2_MMS_Pos); // tim_trgo = UE
	
	TIM3->SMCR |= (1U << TIM_SMCR_TS_Pos) // Trigger = tim_itr1 (TIM2)
								| (6U << TIM_SMCR_SMS_Pos); // Trigger mode

	TIM3->DIER = TIM_DIER_UIE; // Update Event interrupt interrupt enable
	
	TIM3->CCMR1 |= (6U << TIM_CCMR1_OC1M_Pos) 	// CH1: PWM Mode 1
								| TIM_CCMR1_OC1PE							// Output 1 Preload Enable
								|	TIM_CCMR1_OC1FE;						// Output 1 Fast mode enable

	
	TIM3->CCMR2 |= (4U << TIM_CCMR2_OC3M_Pos) 	// CH3: Combined PWM Mode 1
								| (1U << 16)									// Noncontiguous MSB for OC3M
								| TIM_CCMR2_OC3PE							// Output 3 Preload Enable
								|	TIM_CCMR2_OC3FE 						// Output 3 Fast mode enable
								| (7U << TIM_CCMR2_OC4M_Pos) 	// CH4: PWM Mode 2
								| TIM_CCMR2_OC4PE							// Output 4 Preload Enable
								|	TIM_CCMR2_OC4FE;						// Output 4 Fast mode enable
		
	TIM3->CCER |= TIM_CCER_CC3P;	// Invert polarity of CH3
	TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E;	// Enable Capture Compare 1, 3 & 4

}

void TIM4Init(void)
{
	
	/* Set GPIOs */
	gpioInitPin(TIM4_CH4_PORT, TIM4_CH4_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM4_CH3_PORT, TIM4_CH3_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioSetAF(TIM4_CH4_PORT, TIM4_CH4_PIN, TIM4_CH4_AF);
	gpioSetAF(TIM4_CH3_PORT, TIM4_CH3_PIN, TIM4_CH3_AF);
	
	TIM4->SMCR |= (1U << TIM_SMCR_TS_Pos) // Trigger = tim_itr1 (TIM2)
							| (6U << TIM_SMCR_SMS_Pos); // Trigger mode
	
	
	TIM4->CCMR2 |= (6U << TIM_CCMR2_OC3M_Pos) 	// CH3: PWM Mode 1
								| TIM_CCMR2_OC3PE							// Output 3 Preload Enable
								|	TIM_CCMR2_OC3FE 						// Output 3 Fast mode enable
								| (7U << TIM_CCMR2_OC4M_Pos) 	// CH4: PWM Mode 2
								| TIM_CCMR2_OC4PE							// Output 4 Preload Enable
								|	TIM_CCMR2_OC4FE;						// Output 4 Fast mode enable

	TIM4->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;	// Enable Capture Compare 3 & 4

}

void TIM5Init(void)
{
	TIM5->CR1 |= TIM_CR1_URS;
	TIM5->CR2 |= (3U << TIM_CR2_MMS_Pos); // tim_trgo = Compare Pulse
	
	TIM5->SMCR |= (1U << TIM_SMCR_TS_Pos) // Trigger = tim_itr1 (TIM2)
							| (6U << TIM_SMCR_SMS_Pos); // Trigger mode

	TIM5->CCMR1 |= (7U << TIM_CCMR1_OC1M_Pos) // CH1: PWM Mode 2
								| TIM_CCMR1_OC1PE
								| TIM_CCMR1_OC1FE; 	
	TIM5->CCR1 = 480U;

}

void TIM6Init(void)
{
	/* Setup for blocking delays of 5ms by default */
	TIM6->CR1 |= TIM_CR1_OPM | TIM_CR1_URS;
	TIM6->EGR |= TIM_EGR_UG;
	TIM6->PSC = (SYS_FREQ / 1000000) - 1;
}

void TIM7Init(void)
{
	TIM7->CR1 |= TIM_CR1_OPM | TIM_CR1_URS; // One pulse mode, overflow triggers UE
	TIM7->EGR |= TIM_EGR_UG;
	TIM7->ARR = 9999; // Set ARR to 10 ms pulse
	
	TIM7->PSC = (SYS_FREQ / 1000000) - 1; // Set prescaler to 1 tick/us
	
	TIM7->DIER |= TIM_DIER_UIE;
}

void TIM8Init(void)
{
	
	/* Set GPIOs */
	gpioInitPin(TIM8_CH1N_PORT, TIM8_CH1N_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioSetAF(TIM8_CH1N_PORT, TIM8_CH1N_PIN, TIM8_CH1N_AF);
	
	//TIM8->CR1 &= ~TIM_CR1_DIR; // Upcounting mode
	TIM8->CR1 |= TIM_CR1_ARPE | TIM_CR1_OPM;	// One-pulse mode
	
	TIM8->PSC = 0;
	
	
	TIM8->SMCR |=  (1U << 20) // ITR4 trigger source (TIM5)
								| (1U << 16); // Resest & Trigger mode (SMS bit 16)
	
	TIM8->CCMR1 |= (7U << TIM_CCMR1_OC1M_Pos) 	// CH1: PWM Mode 2
								| TIM_CCMR1_OC1PE;							// Output 2 Preload Enable

	TIM8->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSR;

}



void TIM15Init(void)
{
	TIM15->PSC = 0;
	
	TIM15->CR2 |= (1U << TIM_CR2_MMS_Pos); // EN used as external trigger (DMA CH0)
		
	TIM15->SMCR |= (2U << 4) // ITR2 trigger source (TIM3)
								| (7U << 0); // External clock mode 1
}

void TIM16Init(void)
{
	TIM16->PSC = 63999;
	
	TIM16->ARR = 999;
		
	TIM16->DIER |= TIM_DIER_UIE;
}

void LPTIM1Init(void)
{
	/* Note: input tick is from LSE */
	
	LPTIM1->CFGR |= (5U << LPTIM_CFGR_PRESC_Pos); // Prescaler of 32 (1 ms tick)
	LPTIM1->ARR = 999U;
	LPTIM1->CCR1 = 1U;
	
	LPTIM1->DIER |= LPTIM_DIER_UEIE;
	
}

void TIM15Config(uint16_t blocks_per_avg)
{
	TIM15->ARR = blocks_per_avg - 1;
}


void TIM2Enable(void)
{
	TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E;	// Enable Capture Compare 1, 3 & 4
	TIM2->CR1 |= TIM_CR1_CEN;			// Enable counter

}

void TIM8Enable(void)
{
	TIM8->CR1 |= TIM_CR1_CEN;
}

void TIM15Enable(void)
{
	TIM15->CR1 |= TIM_CR1_CEN;
}

void LPTIM1Enable(void)
{
	LPTIM1->CR |= LPTIM_CR_ENABLE;
}

void LPTIM1Start(void)
{
	LPTIM1->CR |= LPTIM_CR_CNTSTRT;
}

void LPTIM1Stop(void)
{
	LPTIM1->CR &= ~LPTIM_CR_ENABLE;
	while(!(LPTIM1->CR & LPTIM_CR_COUNTRST));

	LPTIM1->CR |= LPTIM_CR_COUNTRST;
	while(!(LPTIM1->CR & LPTIM_CR_COUNTRST));
	LPTIM1->CR |= LPTIM_CR_ENABLE;
		
}



uint16_t TIM15GetCNT(void)
{
	return TIM15->CNT;
}

int8_t TIM4GetPhase(void)
{
	int8_t phase = (int8_t) (TIM4->CNT >= TIM4->CCR3);
	phase *= 2;
	phase--;
	return phase;
}

void delay_us(uint16_t us)
{
	TIM6->ARR = us;
	TIM6->CR1 |= TIM_CR1_CEN;
	while(!(TIM6->SR & 1U));
	TIM6->SR &= ~1U;
}
	
void delay_ms(uint16_t ms)
{
	for(uint16_t i=0; i<ms; i++)
	{
		delay_us(1000);
	}
}
