/**

	System Config for STM32U575RIT6 for Nanovoltmeter Rev B
	Author: Curtis Seizert
	Updated: 16 May 2024
	
*/
	
	
#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "sys_cfg.h"

/// @brief Updates the system frequency element using oscillator frequency and PLL settings
/// @param sys Container for system configuration parameters
void update_sysfreq(SysConfig_t * sys)
{
	sys->sys_freq = sys->osc_freq * (sys->pll1_n + 1)/((sys->pll1_m + 1) * (sys->pll1_r + 1));
}

/// @brief Configures the clocks and associated power settings
/// @param sys Container for system configuration parameters
void clock_config(SysConfig_t * sys)
{
	update_sysfreq(sys);

	FLASH->OPTR |= FLASH_OPTR_IO_VDD_HSLV;
	
			/* Enable core peripheral clocks */
	RCC->AHB3ENR |= RCC_AHB3ENR_PWREN;
	RCC->APB3ENR |= RCC_APB3ENR_SYSCFGEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_FLASHEN;
	
			/* See procedure on ref manual p. 407 */
			/* 1.a. Configure PLL1MBoost */
	if(sys->sys_freq >= 55000000) RCC->PLL1CFGR |= (1U << RCC_PLL1CFGR_PLL1MBOOST_Pos);
	
			/* 1.b. Turn HSE ON and set bypass */
	RCC->CR |= RCC_CR_HSEEXT | RCC_CR_HSEON | RCC_CR_HSEBYP;	
	
			/* Wait for HSE to become ready */
	while(!(RCC->CR & RCC_CR_HSERDY));	
	
			/* 1.c. Select PLL1 clock source */
	RCC->PLL1CFGR |= (3U << RCC_PLL1CFGR_PLL1SRC_Pos); // HSE source for PLL1
	
			/* 2. Set Power Scaling */
	PWR->VOSR |= ((uint32_t) sys->vosr << PWR_VOSR_VOS_Pos); 
	
			/* 3. Wait for VOSRDY flag */
	while(!(PWR->VOSR & PWR_VOSR_VOSRDY));
	
			/* 4. If target SYSCLK > 55 MHz set BOOSTEN and wait for BOOSTRDY flag */
	if(sys->sys_freq > 55000000){
		PWR->VOSR |= PWR_VOSR_BOOSTEN;
		while(!(PWR->VOSR & PWR_VOSR_BOOSTRDY));
	}
	
			/* 5. Adjust number of wait states in FLASH_ACR and WSC bits in RAMCFG_MxCR */
	FLASH->ACR |= FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_1WS;
	
			/* 6. Configure PLL */
	RCC->PLL1CFGR &= ~(RCC_PLL1CFGR_PLL1FRACEN);
	RCC->PLL1CFGR |= (1UL << RCC_PLL1CFGR_PLL1MBOOST_Pos)
									| (uint32_t) (sys->pll1_m << RCC_PLL1CFGR_PLL1M_Pos) 
									| RCC_PLL1CFGR_PLL1REN 
									| (3UL << RCC_PLL1CFGR_PLL1RGE_Pos);	// Input clock 8-16 MHz

	RCC->PLL1DIVR = (uint32_t)(sys->pll1_n << RCC_PLL1DIVR_PLL1N_Pos) |
									(uint32_t)(sys->pll1_r << RCC_PLL1DIVR_PLL1R_Pos) |
									(0UL << RCC_PLL1DIVR_PLL1P_Pos);
	
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
}


