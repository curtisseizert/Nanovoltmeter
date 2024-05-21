
#ifndef TIM_H_
#define TIM_H_

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



void enable_timer(TIM_TypeDef * tim);
void disable_timer(TIM_TypeDef * tim);
void reset_timer(TIM_TypeDef * tim);
inline uint32_t get_timer_count(TIM_TypeDef * tim);
void enable_lp_timer(LPTIM_TypeDef * lptim);
void start_lp_timer(LPTIM_TypeDef * lptim);
void stop_lp_timer(LPTIM_TypeDef * lptim);

void tim1_init(void);


void tim8_init(void);

void tim15_init(void);
void tim15_config(uint16_t blocks_per_avg);

void lptim1_init(void);

void tim2_enable(void);

void tim7_init(void); // For debugging

void delay_us(uint16_t us);
void delay_ms(uint16_t ms);


#endif // TIM_H_
