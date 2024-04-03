
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "main.h"
#include "ad5686.h"
#include "ad403x.h"
#include "serial_io.h"


volatile uint16_t ind = 0;
volatile uint16_t flags = 0;
volatile int16_t Vos_dac_code = 0x4A80;


float Vos, lsb_size_nV;
double Vref, gain40, gain60, Vavg;
volatile int gain_state;

volatile uint32_t spi1_ncs_hi = SPI1_NCS_HI;

volatile struct acq_param acq1, acq2;

volatile char uartTxBuf[UART_TX_BUFFER_SIZE];
volatile char uartRxBuf[UART_RX_BUFFER_SIZE];


/* Command index: first position is command to be processed
*		second position is next command to be received */
volatile uint8_t cmdInd[2] = {0,0};
static volatile uint8_t cmdCount = 0;
static volatile uint32_t dacData[4] = {V_OS_DEFAULT, MOD1_HI_DEFAULT, MOD2_HI_DEFAULT, MOD_LO_DEFAULT};
static volatile uint8_t dacCmd[4] = {AD5686_WRT_UP_DAC_B, AD5686_WRT_UP_DAC_A, AD5686_WRT_UP_DAC_C, AD5686_WRT_UP_DAC_D};
static volatile uint16_t mod1HiCode = MOD1_HI_DEFAULT;
static volatile uint16_t mod2HiCode = MOD2_HI_DEFAULT;
static volatile uint16_t modLoCode = MOD_LO_DEFAULT;

volatile int64_t partial_avg[2]; // Averages made at HTE and TCE for DMA 0
volatile int32_t * AD4032_data;


static int32_t cds_offset = 0;	// rolling value that is updated each cds phase
																// for determining DAC updates
volatile int32_t offset_accum = 0;
volatile int16_t offset_counter = 0;
volatile int64_t avg_accum = 0;

volatile uint32_t spi2rxbuf;

volatile uint16_t tmp_reg;
static float Vos_dac_deadband_nV, Vos_dac_deadband_V;
static int16_t codeDeadBand; // Codes within zero and +/- this value will give no DAC update

int main(void)
{
	
		/* 1. Set default parameters */
	setAcquisitionDefaults(&acq1);
	setAcquisitionDefaults(&acq2);

	Vref = (double) 5.0;
	gain40 = (double) 202.6915746;
	gain60 = (double) 2004.87526;
	Vos_dac_code = V_OS_DEFAULT;

	
		/********************************************
		*			SYSTEM & INTERNAL PERIPHERAL SETUP		*
		*********************************************/
		
		
		/* Setup system clocks and power */
	sysConfig();
	
		/* Configure GPIOs and interrupts */
	gpioInit();
	nvicInit();
		
		
		/* Set gain */
	setGain(&acq1, 1);	
	setGain(&acq2, 1);
	
	
		/* Perform setup with modulator off but switch phase defined */
	GPIOmodclocks(&acq1);
	GPIOcdsclocks(&acq1);
	setmodphase(&acq1, 1);
	setcdsphase(&acq1, 1,0);

	
		/* 4. Initialize TIM7 and set relays to default states */
	TIM7Init();
	TIM6Init();
	LPTIM1Init();
	LPTIM1Enable();
	setRelayDefaults();
	
		/* 5. Initialize SPI, I2C, and DAC */
	SPIInit();
	SPI2EnableEOTInt();
	I2C1Init();
	I2C1Enable();
	
	DACInit();
	
			/* Enable UART4 */
	UART4Init();
	ADCInit();


		/* Testing */
	//GPIOcdsclocks(&acq1);
	//setcdsphase(&acq1,0,1);
	//flags |= SKIP_VOS_DAC_UPDATE_FLAG;
	//acq1.flags |= ACQ_FLAG_GPIOCDS_SET;
	
	
	
				/**********************************
				*			EXTERNAL PERIPHERAL SETUP		*
				**********************************/
				
		/* Wait for 5V4 PG before configuration ADC and DAC */
	while(!(GPIOC->IDR & (1U << PG_IN_Pin))); // 
	
		/* Calculate acquisition parameters, setup AD403X and timers */
	setupAcquisition(&acq1);
	
		/* Set defaults for AD5686 */
	AD5686_SetDefaultOutputs();
	
	
		/* Initialize TMP117 */
	TMP117Init();
	//TMP117SetupDMA();
	
		/* SPI2 DMA */
	for(uint8_t i = 0; i < 4; i++){
		dacData[i] |= (dacCmd[i] << 16);
	}
	
	
	SPI2DMAEnable();

	DMA_CH1_Init();
	DMA_CH1_Config((uint32_t) dacData, (uint32_t) &SPI2->TXDR, 4);
	DMA_CH1_Enable();
	SPI2Enable();
	

				/**********************************
				*		START MEASUREMENT CYCLE				* 
				**********************************/
	
	
		/* Enable modulator timers and interrupts from AD4032 BUSY pin */
	ind = 0;
	NVIC_EnableIRQ(EXTI0_IRQn);
	startAcquisition(&acq1);
	

	LPTIM1Start();
		
	while(1){

		while(cmdCount){
			parseInput(&uartRxBuf[UART_RX_CMD_SIZE * cmdInd[0]]);
			cmdCount--;
		}


	}	
	
}



void nvicInit(void)
{
		// Set Interrupt Priority
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(SPI2_IRQn, 1);
	NVIC_SetPriority(TIM3_IRQn, 2);
	NVIC_SetPriority(UART4_IRQn, 3);
	NVIC_SetPriority(TIM7_IRQn, 9);
	NVIC_SetPriority(GPDMA1_Channel0_IRQn, 2);
	NVIC_SetPriority(GPDMA1_Channel1_IRQn, 4);
	NVIC_SetPriority(GPDMA1_Channel2_IRQn, 5);
	NVIC_SetPriority(GPDMA1_Channel3_IRQn, 6);
	NVIC_SetPriority(GPDMA1_Channel12_IRQn, 8);
	NVIC_SetPriority(LPTIM1_IRQn,7);
	
		// Enable interrupts
	NVIC_EnableIRQ(GPDMA1_Channel0_IRQn);
	NVIC_EnableIRQ(GPDMA1_Channel1_IRQn);
	NVIC_EnableIRQ(GPDMA1_Channel2_IRQn);
	NVIC_EnableIRQ(GPDMA1_Channel12_IRQn);
	NVIC_EnableIRQ(GPDMA1_Channel3_IRQn);
	NVIC_EnableIRQ(SPI2_IRQn);
	NVIC_EnableIRQ(TIM7_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(UART4_IRQn);
	NVIC_EnableIRQ(LPTIM1_IRQn);

	
}



void UART4_IRQHandler(void)
{
	UART4->ICR |= USART_ICR_CMCF;
	cmdInd[1] = (cmdInd[1] + 1) %	CMD_BUFFER_LEN;	
	
	GPDMA1_Channel4->CCR |= DMA_CCR_SUSP;
	GPDMA1_Channel4->CCR |= DMA_CCR_RESET;
	
	GPDMA1_Channel4->CBR1 = UART_RX_BUFFER_SIZE;
	GPDMA1_Channel4->CDAR = (uint32_t) &uartRxBuf[UART_RX_CMD_SIZE * cmdInd[1]];
	
	GPDMA1_Channel4->CCR |= DMA_CCR_EN;
	

	cmdCount++;

}

void LPTIM1_IRQHandler(void)
{
	LPTIM1->ICR |= LPTIM_ICR_UECF;
	DMA_CH3_Enable();
	I2C1->CR2 = I2C_CR2_write[1];

	
	TMP117getTemp();
}

void EXTI0_IRQHandler(void)
{
	//SPI1->TXDR = 0UL;
	SPI1->CR1 |= SPI_CR1_CSTART;
	GPIOA->BSRR |= SPI1_NCS_LO; // Pull NCS low
	
	while(!(SPI1->SR & SPI_SR_EOT));
	GPIOA->BSRR |= SPI1_NCS_HI; // Pull NCS high
	
	AD4032_data[ind] = (int32_t) SPI1->RXDR;
	
	SPI1->IFCR |= SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
	

	ind++;
	
	EXTI->FPR1 |= (1UL << 0);
}

void GPDMA1_Channel0_IRQHandler(void)
{
		/* At half transfer, average the elements of the data array thus far */
	if(GPDMA1_Channel0->CSR & DMA_CSR_HTF){
		partial_avg[0] = 0;
		for(uint16_t i = 0; i < acq1.array_size/2; i++){
			partial_avg[0] += AD4032_data[i] >> 2;
		}
		partial_avg[0] /= acq1.array_size/2;
		GPDMA1_Channel0->CFCR |= DMA_CFCR_HTF;
	}
		
		/* At full transfer, average the remaining elements*/
	if(GPDMA1_Channel0->CSR & DMA_CSR_TCF){
		partial_avg[1] = 0;
		for(uint16_t i = acq1.array_size/2; i < acq1.array_size; i++){
			partial_avg[1] += AD4032_data[i] >> 2;
		}
		partial_avg[1] /= acq1.array_size/2;
		GPDMA1_Channel0->CFCR |= DMA_CFCR_TCF;
		
		//DMA_CH0_Config((uint32_t) &SPI1->RXDR, (uint32_t) AD4032_data, acq1.array_size*sizeof(uint32_t));
		//DMA_CH0_Enable();
	}
	
}

void GPDMA1_Channel2_IRQHandler(void)
{
	GPDMA1_Channel2->CFCR |= DMA_CFCR_TCF;
	GPDMA1_Channel2->CCR |= DMA_CCR_RESET;
	
	
	DMA_CH2_Callback();
}

void GPDMA1_Channel1_IRQHandler(void)
{
	GPDMA1_Channel1->CFCR |= DMA_CFCR_TCF;
	GPDMA1_Channel1->CCR |= DMA_CCR_RESET;
	DMA_CH1_Config((uint32_t) dacData, (uint32_t) &SPI2->TXDR, 4);
	

}

void DMA_CH2_Callback(void)
{
	while(!(UART4->ISR & USART_ISR_IDLE));
	
	UART4->ICR |= USART_ICR_TCCF;
}

void GPDMA1_Channel3_IRQHandler(void)
{
	GPDMA1_Channel3->CFCR |= DMA_CFCR_TCF;
	GPDMA1_Channel3->CCR |= DMA_CCR_RESET;
	GPDMA1_Channel3->CLLR = ch3_cllr0;
	
	TMP117UpdateTemps();
}

void SPI2_IRQHandler(void)
{
	SPI2->IFCR |= SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
	spi2rxbuf = SPI2->RXDR;
}

void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF; // Clear UIF
			/* Reset sample counter */
	ind = 0;
	
	uint16_t block_cnt = TIM15GetCNT();
	block_cnt += acq1.mod_cycles_per_avg - 1;
	block_cnt %= acq1.mod_cycles_per_avg;

	
		/* It is necessary to enable TIM8 output here
		*  to ensure it doesn't go high in idle state
		*  and throw off block synchronization with 
		*  ADC OSR
	*/
	TIM8->CCER |= TIM_CCER_CC1NE; // CH1N enable
	
	dacData[0] = (dacCmd[0] << 16) | Vos_dac_code;
	
	DMA_CH1_Enable();
	SPI2->CR1 |= SPI_CR1_CSTART;
	
	//DMA_CH0_Config((uint32_t) &SPI1->RXDR, (uint32_t) AD4032_data, acq1.array_size*sizeof(uint32_t));
	//DMA_CH0_Enable();

	
	if(checkBlockSyncErr()) flags |= BLOCK_SYNC_ERROR_FLAG;
	

	//updateVosDAC();
	
	processDataCycle(block_cnt);
	

}
void TIM7_IRQHandler(void)
{
	TIM7->SR &= ~TIM_SR_UIF; // Reinitialize counter
	TIM7->EGR |= TIM_EGR_UG; // Reinitialize counter
	
		/* Set all relay outputs to low */
	gpioResetPin(K1_R_L_Port, K1_R_L_Pin);
	gpioResetPin(K2_R_L_Port, K2_R_L_Pin);
	gpioResetPin(K3_R_L_Port, K3_R_L_Pin);
	gpioResetPin(K1_S_L_Port, K1_S_L_Pin);
	gpioResetPin(K2_S_L_Port, K2_S_L_Pin);
	gpioResetPin(K3_S_L_Port, K3_S_L_Pin);
}

/**
	*	@brief	Sets relays to default states (K1R, K2S, K3S)
	* @param none
	* @retvalue none
	*/

void setRelayDefaults(void)
{
	gpioSetPin(K1_R_L_Port, K1_R_L_Pin);
	gpioSetPin(K2_S_L_Port, K2_S_L_Pin);
	gpioSetPin(K3_R_L_Port, K3_R_L_Pin);
	
	TIM7->CR1 |= TIM_CR1_CEN; // Enable TIM7 for 5 ms delay
}


	/* DATA SENDING FUNCTIONS */



	/* DATA PROCESSING FUNCTIONS */

void processDataCycle(uint16_t index)
{
	int8_t phase;
	
	/* Determine CDS phase based on index */
	if((2 * index / acq1.mod_cycles_per_cds) & 0x01) phase = 1;
	else phase = -1;
	
	/* Assign CDS phase if GPIO CDS is enabled */
	if(acq1.flags & ACQ_FLAG_GPIO_CDS){
		phase = getGpioPhase(&acq1);
	}

	if(index == 0){
		processDataBlock();
	}
	
	if(checkOverrange()) flags |= OVERRANGE_FLAG;
	
	avg_accum += phase * getAverage(AD4032_data, acq1.array_size)/4;
	offset_accum += phase * getOffset(AD4032_data, acq1.array_size)/4;
	offset_counter++;

	/*
	block_avg[index] = cds_phase[index] * (partial_avg[0] + partial_avg[1])/2;
	block_offset[index] = cds_phase[index] * (partial_avg[0] - partial_avg[1])/2;
	*/

	
	
	
	if((offset_counter >= acq1.mod_cycles_per_update) && !(flags & SKIP_VOS_DAC_UPDATE_FLAG)){
		offset_accum /= acq1.mod_cycles_per_update;
		if(offset_accum > codeDeadBand) Vos_dac_code++;
		if(offset_accum < codeDeadBand) Vos_dac_code--;
		
		Vos = (float) adcCodeToVolts(offset_accum)/acq1.mod_cycles_per_avg;
		offset_accum = 0;
		offset_counter = 0;
	}
	
	
}

void processDataBlock(void)
{
	uint8_t str_len;
	
	Vavg = adcCodeToVolts(avg_accum)/(double) acq1.mod_cycles_per_avg;
	Vos = (float) adcCodeToVolts((int64_t)offset_accum)/ (float) acq1.mod_cycles_per_avg;
	
	avg_accum = 0;
		
	
	
	if(!(flags & OVERRANGE_FLAG)){	
		
		//str_len = sprintf(uartTxBuf, "%6.6f\n\r", 1000000*Vavg);
		//str_len = sprintf(uartTxBuf, "%8.8f, %8.8f\n\r", 1000000*Vavg, 1000000*Vos);
		str_len = sprintf(uartTxBuf, "%4.4f, %4.4f, %2.2f, %2.2f, %2.2f\n\r", 1000000*Vavg, 1000000*Vos, temps[0], temps[1], temps[2]);
		//UART4SendString(uartTxBuf);
	}else{
		//str_len = sprintf(uartTxBuf, "%6.6f OVR\n\r", 1000000*Vavg);
		//str_len = sprintf(uartTxBuf, "%8.8f, %8.8f OVR\n\r", 1000000*Vavg, 1000000*Vos);
		str_len = sprintf(uartTxBuf, "%4.4f, %4.4f, %2.2f, %2.2f, %2.2f\n\r", 1000000*Vavg, 1000000*Vos, temps[0], temps[1], temps[2]);
		//UART4SendString(uartTxBuf);
	}
	
	sendData(uartTxBuf, str_len);
	flags &= ~(BLOCK_SYNC_ERROR_FLAG | OVERRANGE_FLAG);

	flags |= SEND_UART_FLAG;

}

uint8_t checkOverrange(void)
{
	uint8_t OVR = 0;
	
	for(uint16_t i = 0; i < acq1.array_size; i++){
		OVR |= (uint8_t) AD4032_data[i];
	}
	OVR >>= 1;
	OVR &= 0x01;
	
	return OVR;
}

int32_t getAverage(int32_t * array, uint16_t size)
{
	int64_t avg = array[0];
	for(uint32_t i = 1; i < size; i++){
		avg += array[i];
	}
	
	avg /= size;
	return (int32_t) avg;
}

int32_t getOffset(int32_t * array, uint16_t size)
{
	int32_t offset = 0;
	int32_t diff;
	
	for(uint32_t i = 0; i < acq1.array_size/2; i++){
		diff = AD4032_data[i] - AD4032_data[i + acq1.array_size/2];
		offset += diff;
	}
	
	offset /= acq1.array_size;
	return (int32_t) offset;
}

int32_t getCDSOffset(int32_t * array, int8_t * phase, uint16_t size)
{
	int64_t offset = 0;
	int16_t totalPhase = 0;
	
	for(uint32_t i = 0; i < size-1; i++){
		offset -= array[i] * phase[i];
		totalPhase += phase[i];
	}
	
	if(totalPhase){
		offset -= array[size - 1] * phase[size - 1];
		size--;
	}
	
	offset /= size;
	return (int32_t) offset;
}

double adcCodeToVolts(int64_t code)
{
	double volts = (double) code;
	volts /= (1U << 30); 	// Divide by number of codes
	volts *= 2*Vref; 				// Multiply by Vref * 2
	
	if(acq1.gain_state) volts /= gain60; // Divide by gain
	else volts /= gain40;
	
	return volts;
}

void updateVosDAC(void)
{
	if(!(flags & SKIP_VOS_DAC_UPDATE_FLAG)){
		SPI2->TXDR = (AD5686_WRT_UP_DAC_B << 16) | Vos_dac_code;
		SPI2->CR1 |= SPI_CR1_CSTART;
	}
	
}

uint8_t checkBlockSyncErr(void) // Must be run at a change of phase
{
	if(GPIOA->IDR & GPIO_IDR_ID0) return 1;
	return 0;
}

	/* TEMP SENSOR FUNCTIONS */




