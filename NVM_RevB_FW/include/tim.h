


#ifndef TIM_H
#define TIM_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "sys_cfg.h"

	/* TIMERS DESCRIPTION 
	*
	* TIM1: Trigger clock using ETR2
	*
	*	TIM2: modulator clocks, combined PWM mode
	*				master mode to trigger TIM3, TIM4, and TIM5
	*
	*	TIM3: demodulator clocks, combined PWM mode
	*				sync to TIM2
	*
	*	TIM4: ADC CDS clocks, PWM mode
	*
	* TIM5: Trigger to start conversions
	*				ARR = TIM2->ARR / 2, OCR = settling time
	*				OC1REF -> TRG0 -> Triggers TIM8
	*	
	*	TIM6: GP timer to e.g. time relay pulses
	*				PSC set so 1 count = 1 us
	*				One-pulse mode
	*
	*	TIM7: GP timer to e.g. time relay pulses, nonblocking
	*				PSC set so 1 count = 1 us
	*				One-pulse mode
	*
	* TIM8: AD403x-24 CNV Pin, PWM mode; TIM8->RCR = total number of samples per phase
	*				One pulse mode
	*				Triggered by TIM5
	*
	*	TIM15: Synchronizes indexing of output data array
	*				Clocked by TIM4
	*				Generates interrupt at UE to reset index counter
	*				ISR processes data, triggers output via UART4
	*	 
	*/

	/* TIM PIN DEFINES */
#define TIM1_ETR_PORT					GPIO_PORT_A // EXT'L TRIG
#define TIM1_ETR_PIN					GPIO_PIN_12
#define TIM1_ETR_AF						AF1
	
#define TIM2_CH1_PORT					GPIO_PORT_A // MOD1
#define TIM2_CH1_PIN					GPIO_PIN_15
#define TIM2_CH1_AF						AF1
#define TIM2_CH3_PORT					GPIO_PORT_B // MOD2
#define TIM2_CH3_PIN					GPIO_PIN_10
#define TIM2_CH3_AF						AF1

#define TIM3_CH1_PORT					GPIO_PORT_C // DEMOD2
#define TIM3_CH1_PIN					GPIO_PIN_6
#define TIM3_CH1_AF						AF2
#define TIM3_CH3_PORT					GPIO_PORT_C // DEMOD1
#define TIM3_CH3_PIN					GPIO_PIN_8
#define TIM3_CH3_AF						AF2

#define TIM4_CH3_PORT					GPIO_PORT_B // ADC_IN_SW1
#define TIM4_CH3_PIN					GPIO_PIN_8
#define TIM4_CH3_AF						AF2
#define TIM4_CH4_PORT					GPIO_PORT_B // ADC_IN_SW2
#define TIM4_CH4_PIN					GPIO_PIN_9
#define TIM4_CH4_AF						AF2

#define TIM8_CH1N_PORT				GPIO_PORT_A // CNV
#define TIM8_CH1N_PIN					GPIO_PIN_5
#define TIM8_CH1N_AF					AF3

#define TIM_DISABLE(_CHNUM) void TIM##_CHNUM##Disable(void);
	
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



extern uint16_t mod_psc, cnv_cycles, log2SampAvg, blocks_per_cycle, modcyc_per_cds;
extern uint32_t mod_cnt, tim4_arr, tim5_arr, adc_samp_freq;
extern uint32_t mod_deadtime_cyc, demod_deadtime_cyc;
extern float mod_freq, mod_deadtime_us, demod_deadtime_us, settle_time_us;
extern uint32_t adc_samp_freq;

extern uint16_t gpio_mod;
extern uint16_t gpio_cds;


void TIM1Init(void);
void TIM1Enable(void);

void TIM2Init(void);
void TIM3Init(void);
void TIM4Init(void);
void TIM5Init(void);
void TIM6Init(void);
void TIM8Init(void);

void TIM15Init(void);

void LPTIM1Init(void);

void TIM15Config(uint16_t blocks_per_avg);

void TIM2Enable(void);
void TIM8Enable(void);
void TIM15Enable(void);
void LPTIM1Enable(void);

void LPTIM1Start(void);
void LPTIM1Stop(void);

uint16_t TIM15GetCNT(void);
int8_t TIM4GetPhase(void);

void TIM7Init(void); // For debugging

void delay_us(uint16_t us);
void delay_ms(uint16_t ms);


#endif
