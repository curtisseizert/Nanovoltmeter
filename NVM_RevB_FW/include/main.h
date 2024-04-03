/**
	*	main.h
	*	main header file
	*
	*/


#ifndef MAIN_H
#define MAIN_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "uart.h"
#include "sys_cfg.h"
#include "tim.h"
#include "gpio.h"
#include "adc.h"
#include "ospi.h"
#include "spi.h"
#include "dac.h"
#include "i2c.h"
#include "dma.h"
#include "tmp117.h"
#include "acq.h"



extern volatile struct acq_param acq1, acq2;

extern volatile uint16_t ind, flags;
extern volatile int16_t Vos_dac_code;

extern volatile int32_t * AD4032_data;
extern volatile int8_t * cds_phase;

extern float Vos;
extern double Vref, gain40, gain60, Vavg;


void nvicInit(void);
void EXTI0_IRQHandler(void);
void TIM2_IRQHandler(void);
void TIM6_IRQHandler(void);
void TIM7_IRQHandler(void);

void DMA_CH2_Callback(void);


void setRelayDefaults(void);


	/* Functions for processing ADC data */
void processDataBlock(void);
void processDataCycle(uint16_t index);
void updateVosDAC(void);

uint8_t checkOverrange(void);
uint8_t checkBlockSyncErr(void);

int32_t getAverage(int32_t * array, uint16_t size);
int32_t getOffset(int32_t * array, uint16_t size);
int32_t getCDSOffset(int32_t * array, int8_t * phase, uint16_t size);

double adcCodeToVolts(int64_t code);



#endif

