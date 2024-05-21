

#include "tim.h"
#include "gpio.h"


void enable_timer(TIM_TypeDef * tim)
{
	tim->CR1 |= TIM_CR1_CEN;
}

void disable_timer(TIM_TypeDef * tim)
{
	tim->CR1 &= ~TIM_CR1_CEN;
}

void reset_timer(TIM_TypeDef * tim)
{
	tim->EGR |= TIM_EGR_UG;
}

inline uint32_t get_timer_count(TIM_TypeDef * tim)
{
	return tim->CNT;
}

void enable_lp_timer(LPTIM_TypeDef * lptim)
{
	lptim->CR |= LPTIM_CR_ENABLE;
}

void start_lp_timer(LPTIM_TypeDef * lptim)
{
	lptim->CR |= LPTIM_CR_CNTSTRT;
}

void stop_lp_timer(LPTIM_TypeDef * lptim)
{
	lptim->CR &= ~LPTIM_CR_ENABLE;
	while(!(lptim->CR & LPTIM_CR_COUNTRST));

	lptim->CR |= LPTIM_CR_COUNTRST;
	while(!(lptim->CR & LPTIM_CR_COUNTRST));
	lptim->CR |= LPTIM_CR_ENABLE;
}


void tim8_init(void)
{

	TIM8->CR1 |= TIM_CR1_ARPE | TIM_CR1_OPM;	// One-pulse mode
	
	TIM8->PSC = 0;
		
	TIM8->SMCR |=  (1U << 20) // ITR4 trigger source (TIM5)
								| (1U << 16); // Resest & Trigger mode (SMS bit 16)
	
	TIM8->CCMR1 |= (7U << TIM_CCMR1_OC1M_Pos) 	// CH1: PWM Mode 2
								| TIM_CCMR1_OC1PE;							// Output 2 Preload Enable

	TIM8->BDTR |= TIM_BDTR_MOE | TIM_BDTR_OSSR;
}

void tim15_init(void)
{
	TIM15->PSC = 0;
	
	TIM15->CR2 |= (1U << TIM_CR2_MMS_Pos); // EN used as external trigger (DMA CH0)
	TIM15->DIER |= TIM_DIER_UIE;
		
	TIM15->SMCR |= (2U << 4) // ITR2 trigger source (TIM3)
				| (7U << 0); // External clock mode 1
}

void tim16_init(void)
{
	TIM16->PSC = 63999;
	
	TIM16->ARR = 999;
		
	TIM16->DIER |= TIM_DIER_UIE;
}

void lptim1_init(void)
{
	/* Note: input tick is from LSE */
	
	LPTIM1->CFGR |= (5U << LPTIM_CFGR_PRESC_Pos); // Prescaler of 32 (1 ms tick)
	LPTIM1->ARR = 999U;
	LPTIM1->CCR1 = 1U;
	
	LPTIM1->DIER |= LPTIM_DIER_UEIE;
}

void tim15_config(uint16_t blocks_per_avg)
{
	TIM15->ARR = blocks_per_avg - 1;
}

void tim2_enable(void)
{
	TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E;	// Enable Capture Compare 1, 3 & 4
	TIM2->CR1 |= TIM_CR1_CEN;			// Enable counter
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
