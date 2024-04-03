

#include "adc.h"

void ADCInit(void)
{
	
	// Configure common control register
	ADC12_COMMON->CCR |= ADC_CCR_VSENSEEN						// Temp sensor enabled
											| ADC_CCR_VREFEN						// Vref channel enabled
											| (4U << ADC_CCR_PRESC_Pos) // Prescaler div by 8
											| (2U << 14);								// DAMDF = 2 
	
	ADC1->SQR1 |= (2U << ADC_SQR1_L_Pos)				// 3 Channels in sequence
								| (14U << ADC_SQR1_SQ1_Pos)		// CH14
								| (15U << ADC_SQR1_SQ2_Pos)		// CH15
								| (19U << ADC_SQR1_SQ3_Pos);	// CH19 (TEMP)
	
	ADC1->SMPR2 |= (4U << ADC_SMPR2_SMP13_Pos)	// CH13: 36 clock cycles
								| (4U << ADC_SMPR2_SMP14_Pos) // CH14: 36 clock cycles
								| (6U << ADC_SMPR2_SMP19_Pos);// CH19: 391 clock cycles

	
	ADC1->CFGR2 |= (3U << ADC_CFGR2_OVSR_Pos)  // OSR = 4
								| (2U << ADC_CFGR2_OVSS_Pos) // 2-bit right shift
								| ADC_CFGR2_ROVSE;
	
	ADC1->CR |= ADC_CR_ADVREGEN;		// Enable ADC Voltage Reg

}


void adcEnable(void)
{
	ADC1->CR |= ADC_CR_ADEN; // ADON = 1 enable ADC1
}

void adcStart(uint16_t chan)
{
	ADC1->SQR3 = 0;
	ADC1->SQR3 |= chan; // conversion in regular sequence
	
	//ADC1->SR = 0; // clear status register
	
	ADC1->CR |= ADC_CR_ADSTART; // Start conversion
}

void adcWaitforConv(void)
{
	while(!(ADC1->ISR & ADC_ISR_EOC));	// Wait for EOC flag to set
}

uint16_t adcGetData(void)
{
	return (uint16_t) ADC1->DR; // Return data register
}

void adc1Disable(void)
{
	ADC1->CR &= ADC_CR_ADEN; // Disable ADC
}

float adcGetTemp(void)
{
	float temp, vsense;
	vsense = adcGetData();
	vsense *= (float) (3.3/4096);
	temp = ((vsense - ADC_V25)/ADC_AVG_SLOPE) + 25;
	return temp;
}


