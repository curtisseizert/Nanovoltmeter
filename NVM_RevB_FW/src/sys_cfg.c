/**

	CLOCK Setup for STM32F446ZE
	Author: Curtis Seizert
	Updated: 24 Aug 2023
	
	*/
	
	
#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "sys_cfg.h"

void sysConfig(void)
{
	
	FLASH->OPTR |= FLASH_OPTR_IO_VDD_HSLV;
	
				/* Enable core peripheral clocks */
	RCC->AHB3ENR |= RCC_AHB3ENR_PWREN;
	RCC->APB3ENR |= RCC_APB3ENR_SYSCFGEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_FLASHEN;
	
			/* See procedure on ref manual p. 407 */
			/* 1.a. Configure PLL1MBoost */
	RCC->PLL1CFGR |= (1U << RCC_PLL1CFGR_PLL1MBOOST_Pos);
	
			/* 1.b. Turn HSE ON and set bypass */
	RCC->CR |= RCC_CR_HSEEXT | RCC_CR_HSEON | RCC_CR_HSEBYP;	
	
			/* Wait for HSE to become ready */
	while(!(RCC->CR & RCC_CR_HSERDY));	
	
			/* 1.c. Select PLL1 clock source */
	RCC->PLL1CFGR |= (3U << RCC_PLL1CFGR_PLL1SRC_Pos); // HSE source for PLL1
	
			/* 2. Set Power Scaling */
	PWR->VOSR |= (3u << PWR_VOSR_VOS_Pos); // Range 1
	
			/* 3. Wait for VOSRDY flag */
	while(!(PWR->VOSR & PWR_VOSR_VOSRDY));
	
			/* 4. If target SYSCLK > 55 MHz set BOOSTEN and wait for BOOSTRDY flag */
	if(SYS_FREQ > 55000000){
		PWR->VOSR |= PWR_VOSR_BOOSTEN;
		while(!(PWR->VOSR & PWR_VOSR_BOOSTRDY));
	}
	
			/* 5. Adjust number of wait states in FLASH_ACR and WSC bits in RAMCFG_MxCR */
	FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_1WS;
	
			/* 6. Configure PLL */
	RCC->PLL1CFGR &= ~(RCC_PLL1CFGR_PLL1FRACEN);
	RCC->PLL1CFGR |= (1U << RCC_PLL1CFGR_PLL1MBOOST_Pos)
									| (PLL1_M << RCC_PLL1CFGR_PLL1M_Pos) 
									| RCC_PLL1CFGR_PLL1REN 
									| (3U << RCC_PLL1CFGR_PLL1RGE_Pos);	// Input clock 8-16 MHz

	RCC->PLL1DIVR = (PLL1_N << RCC_PLL1DIVR_PLL1N_Pos) |
									(PLL1_R << RCC_PLL1DIVR_PLL1R_Pos) |
									(0U << RCC_PLL1DIVR_PLL1P_Pos);
	
			/* Enable the PLL */
	RCC->CR |= RCC_CR_PLL1ON;
	while(!(RCC->CR & RCC_CR_PLL1RDY));
	
			/* Set the clock source */
	RCC->CFGR1 |= (3u << RCC_CFGR1_SW_Pos); // PLL1R selected as system clock
	while(((RCC->CFGR1 & RCC_CFGR1_SWS_Msk) >> RCC_CFGR1_SWS_Pos) != 3u);
	
		/* Configure prescalers */
	RCC->CFGR2 |= (0u << RCC_CFGR2_HPRE_Pos) |	// AHB PR
								(0u << RCC_CFGR2_PPRE1_Pos) |	// APB1 PR
								(0u << RCC_CFGR2_PPRE2_Pos);	// APB2 PR
	
			/* Allow write access to RCC_BDCR */
	PWR->DBPR |= PWR_DBPR_DBP;
	
			/* Turn LSE ON */
	RCC->BDCR |= RCC_BDCR_LSEBYP
						| RCC_BDCR_LSEON;
	
		/* Wait for LSE to become ready */
	while(!(RCC->BDCR & RCC_BDCR_LSERDY));
	
			/* Enable use of LSE outside backup domain */
	RCC->BDCR |= RCC_BDCR_LSESYSEN;
	
			/* Wait for LSESYS to become ready */
	while(!(RCC->BDCR & RCC_BDCR_LSESYSRDY));
	
			/* Select LSE for RTC and TAMP */
	RCC->BDCR |= (1U << RCC_BDCR_RTCSEL_Pos);
		
		/* Configure peripheral clock muxes */
	RCC->CCIPR3 |= (3u << RCC_CCIPR3_LPTIM1SEL_Pos); // LSE for LPTIM1
	
		/* Enable peripheral clocks */
	enablePeripheralClocks();
}

void enablePeripheralClocks(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPDMA1EN;
	
	RCC->AHB2ENR1 |= RCC_AHB2ENR1_ADC12EN |
						RCC_AHB2ENR1_GPIOHEN |
						RCC_AHB2ENR1_GPIODEN |
						RCC_AHB2ENR1_GPIOCEN |
						RCC_AHB2ENR1_GPIOBEN |
						RCC_AHB2ENR1_GPIOAEN;
	
	RCC->AHB3ENR |= RCC_AHB3ENR_DAC1EN
								|	RCC_AHB3ENR_PWREN;
	
	RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN |
					RCC_APB1ENR1_UART4EN |
					RCC_APB1ENR1_SPI2EN |
					RCC_APB1ENR1_TIM7EN |
					RCC_APB1ENR1_TIM6EN |
					RCC_APB1ENR1_TIM5EN |
					RCC_APB1ENR1_TIM4EN |
					RCC_APB1ENR1_TIM3EN |
					RCC_APB1ENR1_TIM2EN; 
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN | RCC_APB2ENR_SPI1EN |
					RCC_APB2ENR_TIM1EN | RCC_APB2ENR_TIM15EN; 
	
	RCC->APB3ENR |= RCC_APB3ENR_RTCAPBEN |
					RCC_APB3ENR_VREFEN |
					RCC_APB3ENR_LPTIM1EN |
					RCC_APB3ENR_SYSCFGEN; 
	
}
