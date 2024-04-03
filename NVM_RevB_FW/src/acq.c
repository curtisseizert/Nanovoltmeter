
#include "acq.h"
#include "gpio.h"
#include "tim.h"
#include "uart.h"
#include "ad403x.h"
#include "stdlib.h"
#include "spi.h"


void setAcquisitionDefaults(struct acq_param * acq)
{
	/*
	acq->mod_freq = 315;
	acq->mod_cycles_per_avg = 32;
	acq->mod_cycles_per_update = 1;
	acq->mod_cycles_per_cds = 4;
	acq->adc_samp_freq = 500000;
	acq->log2SampAvg = 8U;
	acq->settle_time_us = 2.0f;
	acq->Vos_dac_deadband_nV = 40.0f;
	
	acq->mod_deadtime_us = 0.08f;
	acq->demod_deadtime_us = 0.1f;
	*/

	acq->mod_freq = 1800;
	acq->mod_cycles_per_avg = 900;
	acq->mod_cycles_per_update = 18;
	acq->mod_cycles_per_cds = 18;
	acq->adc_samp_freq = 500000;
	acq->log2SampAvg = 7U;
	acq->settle_time_us = 15.0f;
	acq->Vos_dac_deadband_nV = 40.0f;
	
	acq->mod_deadtime_us = 0.00f;
	acq->demod_deadtime_us = 0.1f;


	
}



void setupAcquisition(struct acq_param * acq)
{
	initModTimers(acq);
	timerConfig(acq);
	allocateArrayMemory(acq);
	AD403X_Reset();
	AD403X_SetAcquisitionParam(acq);
	
	//SPI1DMAEnable();
	//DMA_CH0_Init();
	//DMA_CH0_Config((uint32_t) &SPI1->RXDR, (uint32_t) AD4032_data, acq->array_size*sizeof(uint32_t));
	//DMA_CH0_Enable();
	//SPI1Enable();
	
	acq->flags |= ACQ_FLAG_MODTIMRDY;
}

void startAcquisition(struct acq_param * acq)
{
	if(!(acq->flags & ACQ_FLAG_MODTIMRDY)) {
		if((acq->flags & ACQ_FLAG_GPIO_CDS) ^ (acq->flags & ACQ_FLAG_GPIOCDS_SET)) TIMcdsclocks(acq);
		if((acq->flags & ACQ_FLAG_GPIO_MOD) ^ (acq->flags & ACQ_FLAG_GPIOMOD_SET)) TIMmodclocks(acq);
		
		acq->flags |= ACQ_FLAG_MODTIMRDY;
	}
	
	TIM2Enable();
	TIM15Enable();
	//SPI1DMAEnable();
	//DMA_CH0_Config((uint32_t) &SPI1->RXDR, (uint32_t) AD4032_data, acq->array_size*sizeof(uint32_t));
	//DMA_CH0_Enable();
	
	acq->flags |= ACQ_FLAG_MOD_ON;
}

void pauseAcquisition(struct acq_param * acq)
{
	/* Disable timers, 
	*	 enable gpio modulator and cds
	*	 reset AD403X,
	*  reconfigure AD403X with current parameters*/
	
	disableModTimers();
	TIM8->CCER &= ~TIM_CCER_CC1NE;	// Disable TIM8 output (it is enabled in TIM3IRQ_Handler)
	ind = 0;
	offset_accum = 0;
	offset_counter = 0;
	
	GPIOmodclocks(acq);
	GPIOcdsclocks(acq);
	setmodphase(acq, 1);
	setcdsphase(acq, 0,0);
	
	//GPDMA1_Channel0->CCR |= DMA_CCR_SUSP;
	//SPI1DMADisable();
	
	
	AD403X_Reset();
	AD403X_SetAcquisitionParam(acq);
	
	//GPDMA1_Channel0->CCR |= DMA_CCR_RESET;
	
	
	
	acq->flags &= ~(ACQ_FLAG_MOD_ON | ACQ_FLAG_MODTIMRDY);
	
}

void pauseAcquisitionDiagnostic(struct acq_param * acq)
{
	/* Disable timers, 
	*	 enable gpio modulator and cds
	*	 reset AD403X,
	*  reconfigure AD403X with current parameters*/
	
	disableModTimers();
	TIM8->CCER &= ~TIM_CCER_CC1NE;	// Disable TIM8 output (it is enabled in TIM3IRQ_Handler)
	
	GPIOmodclocks(acq);
	GPIOcdsclocks(acq);
	setmodphase(acq, 0);
	setcdsphase(acq, 0,0);
	
}

void disableModTimers(void)
{
	TIM2Disable();
	TIM3Disable();
	TIM4Disable();
	TIM5Disable();
	TIM8Disable();
	TIM15Disable();

	TIM2->EGR |= TIM_EGR_UG;
	TIM3->EGR |= TIM_EGR_UG;
	TIM4->EGR |= TIM_EGR_UG;
	TIM5->EGR |= TIM_EGR_UG;
	TIM8->EGR |= TIM_EGR_UG;
	TIM15->EGR |= TIM_EGR_UG;
	
}

void AD403X_SetAcquisitionParam(struct acq_param * acq)
{
	while(1U & GPIOA->IDR);
	AD403X_EnterRegAccess();
	
	AD403X_WriteRegister(AD403X_REG_AVG, acq->log2SampAvg);
	AD403X_WriteRegister(AD403X_REG_MODES, AD403X_DEFAULT_MODE);
	
	AD403X_ExitRegAccess();
}

void allocateArrayMemory(struct acq_param * acq)
{
	acq->array_size = acq->blocks_per_cycle;
	
	AD4032_data = (int32_t *)realloc(AD4032_data, (acq->array_size)*sizeof(int32_t));
	
	for(uint16_t i = 0; i<acq->blocks_per_cycle; i++) AD4032_data[i] = 0;
	/*
	cds_phase = (uint8_t *)realloc(cds_phase, acq->mod_cycles_per_avg*sizeof(uint8_t));
	block_avg = (int32_t *)realloc(block_avg, acq->mod_cycles_per_avg*sizeof(int32_t));
	block_offset = (int32_t *)realloc(block_offset, acq->mod_cycles_per_avg*sizeof(int32_t));
	
	for(uint16_t i = 0; i<acq->mod_cycles_per_avg; i++){
		cds_phase[i] = 0;
		block_avg[i] = 0;
		block_offset[i] = 0;
	}
	*/
}




void timerConfig(struct acq_param * acq)
{
	/* NOTE: Assumes no prescaler for timers */
	/* Calculate autoreload register values */
	/* This function must be called before enabling TIM2 */
	
	uint16_t samples_per_block, blocks_per_phase;
	uint32_t ticks_per_phase, ticks_per_sample, ticks_per_block;
	float phase_time_us;
	
		
	samples_per_block = (uint16_t) (1U << acq->log2SampAvg); // Calculate number of samples per block
	
		/* All timers use integer multiples of ticks_per_phase or ticks_per_sample */
	ticks_per_phase = (uint32_t) (SYS_FREQ / (acq->mod_freq * 2));
	ticks_per_sample = (uint32_t) (SYS_FREQ / acq->adc_samp_freq);
	ticks_per_block = ticks_per_sample * samples_per_block;
	
		/* Recalculate mod_frequency to account for finite resolution */
	acq->mod_freq = (float) SYS_FREQ / (float) (ticks_per_phase * 2);
	
		/* Calculate ARR values for mod, demod, and cds timers */
	TIM2->ARR = (2 * ticks_per_phase) - 1;
	TIM3->ARR = (2 * ticks_per_phase) - 1;
	TIM4->ARR = (2 * ticks_per_phase * acq->mod_cycles_per_cds) - 1;
	TIM5->ARR = ticks_per_phase - 1;
	
		/* Calculate deadtimes in cycles */
	float clkfreq_mhz = SYS_FREQ/1000000;
	acq->mod_deadtime_cyc = (uint32_t) (acq->mod_deadtime_us * clkfreq_mhz);
	acq->demod_deadtime_cyc = (uint32_t) (acq->demod_deadtime_us * clkfreq_mhz);
	
		/* Recalculate actual deadtimes */
	acq->mod_deadtime_us = (float) acq->mod_deadtime_cyc/ (float) clkfreq_mhz;
	acq->demod_deadtime_us = (float) acq->demod_deadtime_cyc/ (float) clkfreq_mhz;
	
	/* Calculate capture compare register values */
	TIM2->CCR1 = (uint32_t) (ticks_per_phase - acq->mod_deadtime_cyc - 1);
	TIM2->CCR3 = (uint32_t) (ticks_per_phase - 1);
	TIM2->CCR4 = (uint32_t) ((2 * ticks_per_phase) - acq->mod_deadtime_cyc - 1);
	
	TIM3->CCR1 = (uint32_t) (ticks_per_phase - acq->demod_deadtime_cyc - 1);
	TIM3->CCR3 = (uint32_t) (ticks_per_phase - 1);
	TIM3->CCR4 = (uint32_t) ((2 * ticks_per_phase) - acq->demod_deadtime_cyc - 1);
	
	TIM4->CCR3 = ticks_per_phase * acq->mod_cycles_per_cds;
	TIM4->CCR4 = ticks_per_phase * acq->mod_cycles_per_cds;
	
	TIM5->CCR1 = (uint32_t) (acq->settle_time_us * clkfreq_mhz); 
	
		/* Calculate number of CNV pulses per cycle */
	blocks_per_phase = (uint16_t) (ticks_per_phase/ticks_per_block); // Calculate number of blocks that will fit
	acq->cnv_cycles = blocks_per_phase * samples_per_block; // Multiply number of blocks by number of samples per block
	acq->blocks_per_cycle = 2 * blocks_per_phase; // Convert blocks per phase to blocks per cycle for external use
	
	TIM8->RCR = acq->cnv_cycles - 1; // Update TIM8->RCR
	
	TIM8->ARR = SYS_FREQ / acq->adc_samp_freq - 1;
	
	TIM8->CCR1 = SYS_FREQ / acq->adc_samp_freq - 12U; // 60 ns pulse (must be greater than 1/f_osc to 
										// ensure flip flop triggers).
	
	TIM15Config(acq->mod_cycles_per_avg);
	
	acq->flags |= ACQ_FLAG_PARAM_SETUP;
}

void GPIOmodclocks(struct acq_param * acq)
{
	acq->flags |= ACQ_FLAG_GPIO_MOD;
	
	gpioInitPin(TIM2_CH1_PORT, TIM2_CH1_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM2_CH3_PORT, TIM2_CH3_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM3_CH1_PORT, TIM3_CH1_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM3_CH3_PORT, TIM3_CH3_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	
	
}

void TIMmodclocks(struct acq_param * acq)
{
	acq->flags &= ~ACQ_FLAG_GPIO_MOD;
	
	gpioInitPin(TIM2_CH1_PORT, TIM2_CH1_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM2_CH3_PORT, TIM2_CH3_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioSetAF(TIM2_CH1_PORT, TIM2_CH1_PIN, TIM2_CH1_AF);
	gpioSetAF(TIM2_CH3_PORT, TIM2_CH3_PIN, TIM2_CH3_AF);
	
	gpioInitPin(TIM3_CH1_PORT, TIM3_CH1_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM3_CH3_PORT, TIM3_CH3_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioSetAF(TIM3_CH1_PORT, TIM3_CH1_PIN, TIM3_CH1_AF);
	gpioSetAF(TIM3_CH3_PORT, TIM3_CH3_PIN, TIM3_CH3_AF);
}

void GPIOcdsclocks(struct acq_param * acq)
{
	acq->flags |= ACQ_FLAG_GPIO_CDS;

	gpioInitPin(TIM4_CH4_PORT, TIM4_CH4_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM4_CH3_PORT, TIM4_CH3_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	
}

void TIMcdsclocks(struct acq_param * acq)
{
	acq->flags &= ~ACQ_FLAG_GPIO_CDS;
	
	gpioInitPin(TIM4_CH4_PORT, TIM4_CH4_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioInitPin(TIM4_CH3_PORT, TIM4_CH3_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MED, GPIO_NO_PUPD);
	gpioSetAF(TIM4_CH4_PORT, TIM4_CH4_PIN, TIM4_CH4_AF);
	gpioSetAF(TIM4_CH3_PORT, TIM4_CH3_PIN, TIM4_CH3_AF);
}

void setmodphase(struct acq_param * acq, uint16_t phase)
{
	if(acq->flags & ACQ_FLAG_GPIO_MOD){
		if(phase == 0){
			GPIOA->BSRR |= 1U << TIM2_CH1_PIN;
			GPIOB->BSRR |= 1U << (TIM2_CH3_PIN + 16);
			GPIOC->BSRR |= (1U << TIM3_CH1_PIN) | (1U << (TIM3_CH3_PIN + 16));
			acq->flags &= ~ACQ_FLAG_GPIOMODPOL;
		}
		if(phase == 1) {
			GPIOA->BSRR |= 1U << (TIM2_CH1_PIN + 16);
			GPIOB->BSRR |= 1U << TIM2_CH3_PIN;
			GPIOC->BSRR |= (1U << (TIM3_CH1_PIN + 16)) | (1U << TIM3_CH3_PIN);
			acq->flags |= ACQ_FLAG_GPIOMODPOL;
		}
	}
}

void setcdsphase(struct acq_param * acq, uint8_t phase1, uint8_t phase2)
{
	if(acq->flags & ACQ_FLAG_GPIO_CDS){
		if(phase1 == 1){
			GPIOB->BSRR |= (1U << TIM4_CH3_PIN);
			acq->flags |= ACQ_FLAG_GPIOCDS_SW1;
		}
		if(phase1 == 0){
			GPIOB->BSRR |= (1U << (TIM4_CH3_PIN + 16));
			acq->flags &= ~ACQ_FLAG_GPIOCDS_SW1;
		}
		if(phase2 == 1){
			GPIOB->BSRR |= (1U << TIM4_CH4_PIN);
			acq->flags |= ACQ_FLAG_GPIOCDS_SW2;
		}
		if(phase2 == 0){
			GPIOB->BSRR |= (1U << (TIM4_CH4_PIN + 16));
			acq->flags &= ~ACQ_FLAG_GPIOCDS_SW2;
		}
		
	}
}

int8_t getGpioPhase(struct acq_param * acq)
{
	int8_t phase[2];
	if(acq->flags & ACQ_FLAG_GPIOCDS_SW1) phase[0] = 1;
	if(acq->flags & ACQ_FLAG_GPIOCDS_SW1) phase[1] = 1;
	
	if(!(phase[0] ^ phase[1])) return 1;
	else return (phase[0] << 1) - 1;

}

void initModTimers(struct acq_param * acq)
{
	acq->flags &= ~(ACQ_FLAG_GPIO_CDS | ACQ_FLAG_GPIO_MOD);
	
	TIM2Init();		// Initialize timers
	TIM3Init();
	TIM4Init();
	TIM5Init();
	TIM8Init();
	TIM15Init();
	
	acq->flags |= ACQ_FLAG_MODTIMRDY;
	
}



void setGain(struct acq_param * acq, uint16_t g)
{
	if(g){
		acq->gain_state = 1;
		gpioSetPin(GAIN_60_DB_Port, GAIN_60_DB_Pin);
		gpioResetPin(GAIN_40_DB_Port, GAIN_40_DB_Pin);
	}else{
		gpioSetPin(GAIN_40_DB_Port, GAIN_40_DB_Pin);
		gpioResetPin(GAIN_60_DB_Port, GAIN_60_DB_Pin);
		acq->gain_state = 0;
	}
	acq->lsb_size_nV = getLSBSize_nV(getGain(acq));
	updateDeadBand(acq);
}

float getLSBSize_nV(double gain)
{
	float nVLSB = Vref/(1U << 29);
	nVLSB *= 1000000000/gain;
	return nVLSB; 
}

void updateDeadBand(struct acq_param * acq)
{
	acq->codeDeadBand = (int16_t) (acq->Vos_dac_deadband_nV / acq->lsb_size_nV);
}

double getGain(struct acq_param * acq)
{
	if(acq->gain_state) return gain60;
	else return gain40;
}

void relaySetState(struct acq_param * acq, uint8_t relayNum, uint8_t state)
{
	switch(relayNum){
		case 1:
			if(state){
				GPIOA->BSRR |= (1U << K1_S_L_Pin);
				acq->relay_states |= RELAY_K1_SET;
			}
			else{
				GPIOB->BSRR |= (1U << K1_R_L_Pin);
				acq->relay_states &= ~RELAY_K1_SET;
			}
			break;
			
		case 2:
			if(state){
				GPIOA->BSRR |= (1U << K2_S_L_Pin);
				acq->relay_states |= RELAY_K2_SET;
			}
			else{
				GPIOB->BSRR |= (1U << K2_R_L_Pin);
				acq->relay_states &= ~RELAY_K2_SET;
			}
			break;
			
		case 3:
			if(state){
				GPIOA->BSRR |= (1U << K3_S_L_Pin);
				acq->relay_states |= RELAY_K3_SET;
			}
			else{
				GPIOB->BSRR |= (1U << K3_R_L_Pin);
				acq->relay_states &= ~RELAY_K3_SET;
			}
			break;
	}

	TIM7->CR1 |= TIM_CR1_CEN; // Enable TIM7 for 5 ms delay before resetting all
}

