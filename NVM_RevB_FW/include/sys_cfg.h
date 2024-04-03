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
	
#ifndef sys_config
#define sys_config

#include "stm32u5xx.h"
#include "stm32u575xx.h"

#define OSC_FREQ	24000000UL // HSE Oscillator Frequency
#define PLL1_M		1					// PLL1M = 2			
#define PLL1_N		23		// PLL1N = 16
#define	PLL1_R		3			// PLL1R = 4 
#define PLL1_Q		3			// PLL1Q = 3
#define PLL2_M		1			// PLL2M = 2			
#define PLL2_N		15		// PLL2N = 16
#define	PLL2_R		3			// PLL2R = 4 
#define PLL2_Q		3			// PLL2Q = 4
#define SYS_FREQ	OSC_FREQ * (PLL1_N + 1)/((PLL1_M + 1) * (PLL1_R + 1))

void sysConfig(void);
void enablePeripheralClocks(void);

#endif
