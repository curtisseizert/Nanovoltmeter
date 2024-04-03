

#ifndef ADC_H
#define ADC_H


#include "stm32u5xx.h"
#include "stm32u575xx.h"


static float ADC_V25 = (float) 0.76;
static float ADC_AVG_SLOPE = (float) 0.0025;

void ADCInit(void);
void adcEnable(void);
void adcStart(uint16_t chan);

void adcDMAInit(void);
void adcDMAConfig(uint32_t srcAdd, uint32_t destAdd, uint16_t dsize);
void adcDMAEnable(void);
	

void adcWaitforConv(void);
uint16_t adcGetData(void);
void adc1Disable(void);
float adcGetTemp(void);


#endif
