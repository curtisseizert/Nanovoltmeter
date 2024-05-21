/**

	System Configuration for STM32U575RI
	Author: Curtis Seizert
	Updated: 25 Jan 2024
	
	*/
	

/**
  * @brief  System Clock Configuration
  *         The system Clock is configured as follows : 
	*						 Clock input										=	24 MHz crystal oscillator
  *            System Clock source            = PLL (HSE)
  *            SYSCLK(Hz)                     = 64000000
  *            HCLK(Hz)                       = 64000000
  *            AHB Prescaler                  = 1
  *            APB1 Prescaler                 = 1
  *            APB2 Prescaler                 = 1
  *            APB3 Prescaler                 = 1
  *            HSE Frequency(Hz)              = 24000000
  *            PLL_M                          = 2
  *            PLL_N                          = 16
	*						 PLL_R													= 4
  *            PLL_P                          = 2
  *            VDD(V)                         = 3.3
  *            Main regulator output voltage  = Scale1 mode
  *            Flash Latency(WS)              = 5
  * @param  None
  * @retval None
  */
	
#ifndef SYS_CONFIG_H_
#define SYS_CONFIG_H_

#include <stdint.h>

typedef enum{
  VOSR_RANGE_4 = 0U,
  VOSR_RANGE_3 = 1U,
  VOSR_RANGE_2 = 2U,
  VOSR_RANGE_1 = 3U
} VOSR_RANGE_TypeDef;

typedef struct{
  const uint32_t osc_freq;
  uint32_t sys_freq;
  VOSR_RANGE_TypeDef vosr;
  uint8_t pll1_m;
  uint8_t pll1_n;
  uint8_t pll1_r;
  uint8_t pll1_q;
  uint8_t pll2_m;
  uint8_t pll2_n;
  uint8_t pll2_r;
  uint8_t pll2_q;

} SysConfig_t;


void update_sysfreq(SysConfig_t * sys);

void clock_config(SysConfig_t * sys);
void enablePeripheralClocks(void);



#endif // SYS_CONFIG_H_
