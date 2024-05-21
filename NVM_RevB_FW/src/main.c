
	/* main.c */

#include "stm32u5xx.h"
#include "stm32u575xx.h"

#include "main.h"
#include "acq.h"
#include "ad5686.h"
#include "ad403x.h"
#include "tmp117.h"
#include "serial_io.h"
#include "nvmb.h"
#include "fifo.h"

// Containers for acquisition parameters and intermediate results
// acq1 represents the current acquisition
// acq2 is used for on-the-fly modification of acquisition parameters and is copied to acq1
// on a MEAS:INIT command
AcqParam_t acq1, acq2;

volatile uint16_t data_flags;
volatile uint32_t task_flags;

// Variable for garbage results
volatile uint32_t garbage;

// Container for raw ADC results
volatile AD403XData_t ad403x_data;

// Sinc filter container
SincFilter_t sinc;

// FIFO for storing/sending results
static FIFO_t reading_fifo = { .data_reqd = FIFO_VAVG_MASK};

// Buffer for data being sent over USART3 (via GPDMA1_Channel2)
volatile char uart_tx_buffer[UART_TX_BUFFER_SIZE];

// Circular buffer container for data received over USART3
static volatile UartRx_t uart_rx = {
	.dma = GPDMA1_Channel4
};

// Container for DAC channel codes and associated peripheral addresses
static AD5686_t ad5686 = {
	.spi = SPI2,
	.dma = GPDMA1_Channel1,
	.channel_codes = {MOD1_HI_DEFAULT, V_OS_DEFAULT, MOD2_HI_DEFAULT, MOD_LO_DEFAULT}
};

// Container for ADC associated SPI bus address and GPIOs
static const AD403X_t ad4030 = {
	.spi = SPI1,
	.ncs_pin = (Pin_t *) &ADC_NCS_Pin,
	.nreset_pin = (Pin_t *) &ADC_NRESET_Pin
};

// Container for TMP117 devices
static TMP117_t tmp117[3] = {
	{.i2c = I2C1, .addr = TMP117_INPUT_ADDR},
	{.i2c = I2C1, .addr = TMP117_ADC_ADDR},
	{.i2c = I2C1, .addr = TMP117_REF_ADDR},
};

// Initialization parameters for SPI bus associated with AD4030-24
static const SPI_Init_t spi1_init = {
	.CR1 = SPI_CR1_SSI | SPI_CR1_SPE,
	.CR2 = (1U << SPI_CR2_TSIZE_Pos),
	.CFG1 = SPI_CFG1_BPASS | (AD403X_AVERAGING_DSIZE << SPI_CFG1_DSIZE_Pos)
			| (7U << SPI_CFG1_CRCSIZE_Pos),
	.CFG2 = SPI_CFG2_MASTER | SPI_CFG2_SSM | (2U << SPI_CFG2_COMM_Pos)
};

// Initialization parameters for SPI bus associated with AD5686
static const SPI_Init_t spi2_init = {
	.CR1 = SPI_CR1_SPE,
	.CR2 = (1U << SPI_CR2_TSIZE_Pos),
	.CFG1 = (1U << SPI_CFG1_MBR_Pos) | (SPI2_DSIZE << SPI_CFG1_DSIZE_Pos)
			| (SPI2_DSIZE << SPI_CFG1_CRCSIZE_Pos),
	.CFG2 = SPI_CFG2_SSOE | SPI_CFG2_CPHA | SPI_CFG2_MASTER | 
		(1U << SPI_CFG2_MSSI_Pos) | (1U << SPI_CFG2_COMM_Pos)
};

// Default acquisition parameters
static const AcqParam_t AcqParam_default = {
	.adc = &ad4030,
	.adc_data = (AD403XData_t *) &ad403x_data,
	.sinc = (SincFilter_t *) &sinc,
	.mod_freq = 1800,
	.mod_cycles_per_avg = 1800,
	.mod_cycles_per_update = 18,
	.mod_cycles_per_cds = 18,
	.adc_samp_freq = 1000000,
	.log2SampAvg = 6,
	.settle_time_us = (float) 15.0,
	.Vos_dac_deadband_nV = (float) 40.0,
	.mod_deadtime_us = (float) 0,
	.demod_deadtime_us = (float) 0.1,
	.sinc_order = 2
};

int main(void)
{
		// Declare and/or initialize FIFO_t, AcqParam_t, AcqConst_t containers
	acq1 = AcqParam_default;
	acq2 = AcqParam_default;
	sinc_reset_filter(&sinc);

	AcqConst_t acq_const = {
		.v_ref = (double) 5.0,
		.gain_lo = 202.6915746,
		.gain_hi = 2004.87526
	};

	acq1.acq_const = &acq_const;
	acq2.acq_const = &acq_const;
	uart_rx_t_init((UartRx_t *)&uart_rx, GPDMA1_Channel4);
	
		/************************************************
		*		SYSTEM & INTERNAL PERIPHERAL SETUP		*
		*************************************************/
		
		// Setup system clocks and power 
	sys_clock_config();
	
		// Configure GPIOs and interrupts 
	pin_init();
	nvicInit();
		
		// Set default gain
	set_gain(&acq1, GAIN_STATE_HI);	
	set_gain(&acq2, GAIN_STATE_HI);
	
		// Perform setup with modulator off but switch phase defined
	gpio_mod_clocks(&acq1);
	gpio_cds_clocks(&acq1);
	set_mod_phase(&acq1, MOD_PHASE_1);
	set_cds_phase(&acq1, SW1_CM_SW2_IN);
	
		// Initialize housekeeping timers and set relays to default states
	init_housekeeping_timers();
	set_relay_defaults();
	lptim1_init();
	//enable_lp_timer(LPTIM1);
		
		// Initialize SPI, I2C, and DAC
	spi_init(SPI1, &spi1_init);
	spi_init(SPI2, &spi2_init);
	spi_enable(SPI1);
	spi_enable(SPI2);
	//i2c_init(tmp117[0].i2c);
	//i2c_enable(tmp117[0].i2c);
	DACInit();
	
			/* Enable USART3 */
	usart3_init();
	DMA_CH2_Init();
	dma_enable_channel(GPDMA1_Channel2);
	DMA_CH4_Init((uint32_t *) uart_rx.buffer);
	dma_enable_channel(GPDMA1_Channel4);
	ADCInit();
	
				/************************************
				*	EXTERNAL PERIPHERAL SETUP		*
				*************************************/
				
		/* Wait for 5V4 PG before configuration ADC and DAC */
	while(gpio_get_state(PG_IN_Pin) == GPIO_STATE_LO); // 
	
		/* Calculate acquisition parameters, setup AD403X and timers */
	setup_acquisition(&acq1);
	
		/* Set defaults for AD5686 */
	ad5686_write_all(&ad5686);
	
		/* Initialize TMP117 */
	//tmp117_init(&tmp117[0]);

	spi_dma_enable(ad5686.spi);
	DMA_CH1_Init(&ad5686.channel_codes[1]);
	dma_enable_channel(ad5686.dma);
	spi_enable(ad5686.spi);


	
	// Enable modulator timers and interrupts from AD4032 BUSY pin 
	NVIC_EnableIRQ(EXTI0_IRQn);
	start_acquisition(&acq1);
	garbage = SPI1->RXDR;
	//start_lp_timer(LPTIM1);

	while(1)
	{
			// TASK PRIORITIZATION SYSTEM 
			// Increments through possible tasks starting with highest priority.
			// If it hits a set task flag, the task is performed and the iteration
			// begins again from 0.
		for(uint16_t task_bit = 0; task_bit <= MAX_TASK_BIT; task_bit++)
		{
			uint32_t task_masked = (1UL << task_bit) & task_flags;

			switch(task_masked)
			{
				case TASK_FLAG_NO_TASK:
					break;
				case TASK_FLAG_PROCESS_CYCLE:
					process_data_cycle(&acq1);
					ad5686.channel_codes[1] += calculate_vos_dac_increment(&acq1);
					ad5686.channel_codes[1] = 
						ad5686_format_data_write(V_OS_DAC, (uint16_t) ad5686.channel_codes[1]);
					dma_enable_channel(ad5686.dma);
					task_flags &= ~TASK_FLAG_PROCESS_CYCLE;
					break;
				case TASK_FLAG_PROCESS_BLOCK:
					fifo_write_v_avg(&reading_fifo, get_block_v_avg(&acq1));
					fifo_write_other(&reading_fifo, acq1.v_os, FIFO_VOS_MASK);
					task_flags &= ~TASK_FLAG_PROCESS_BLOCK;
					task_flags |= TASK_FLAG_SEND_DATA;
					break;
				case TASK_FLAG_PROCESS_INPUT:
					parse_rx_buffer((UartRx_t *)&uart_rx);
					task_flags &= ~TASK_FLAG_PROCESS_INPUT;
					break;
				case TASK_FLAG_SEND_DATA:
					if(send_serial_result(&reading_fifo) == SERIAL_IO_NO_ERROR){
						task_flags &= ~TASK_FLAG_SEND_DATA;
					};
					break;
			}

			if(task_masked != TASK_FLAG_NO_TASK) break;
		}
	}	
}

/// @brief Sets interrupt priorities and enables interrupts
/// @param None 
void nvicInit(void)
{
		// Set Interrupt Priority
	NVIC_SetPriority(EXTI0_IRQn, 0);
	NVIC_SetPriority(TIM3_IRQn, 2);
	NVIC_SetPriority(USART3_IRQn, 3);
	NVIC_SetPriority(TIM7_IRQn, 9);
	NVIC_SetPriority(LPTIM1_IRQn,7);
	NVIC_SetPriority(TIM15_IRQn, 4);
	
		// Enable interrupts
	NVIC_EnableIRQ(TIM7_IRQn);
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(USART3_IRQn);
	NVIC_EnableIRQ(LPTIM1_IRQn);
	NVIC_EnableIRQ(TIM15_IRQn);
}

/// @brief Records address and registers incoming received commands using character match interrupt
/// @param None 
void USART3_IRQHandler(void)
{
	USART3->ICR |= USART_ICR_CMCF;
	
	uart_rx_increment_index((UartRx_t *)&uart_rx);
	task_flags |= TASK_FLAG_PROCESS_INPUT;
}

void LPTIM1_IRQHandler(void)
{
	LPTIM1->ICR |= LPTIM_ICR_UECF;
	//DMA_CH3_Enable();
	//I2C1->CR2 = I2C_CR2_write[1];
	
	tmp117_get_temp(&tmp117[0]);
}

/// @brief Receives data from ADC when BUSY pin goes low
/// @param  None
/// @note Must be able to complete SPI transaction before next CNV pulse
void EXTI0_IRQHandler(void)
{
	gpio_reset_pin(ADC_NCS_Pin); 	// Pull NCS low
	SPI1->CR1 |= SPI_CR1_CSTART;

	while(!(SPI1->SR & SPI_SR_EOT));
	gpio_set_pin(ADC_NCS_Pin);		// Pull NCS high
	
	ad403x_data.buf[ad403x_data.index] = (int32_t) SPI1->RXDR;
	
	SPI1->IFCR |= SPI_IFCR_EOTC | SPI_IFCR_TXTFC;

	ad403x_data.index++;
	
	EXTI->FPR1 |= (1UL << 0);
}

/// @brief Synchronizes data processing and IO operations with modulator clock
/// @param  None
void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF; // Clear UIF
			/* Reset sample counter */
	ad403x_data.index = 0;
	
		/* It is necessary to enable TIM8 output here
		*  to ensure it doesn't go high in idle state
		*  and throw off block synchronization with 
		*  ADC OSR */

	TIM8->CCER |= TIM_CCER_CC1NE; // CH1N enable
	
	SPI2->IFCR |= SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
	spi_start(ad5686.spi);

	task_flags |= TASK_FLAG_PROCESS_CYCLE;
}

/// @brief Interrupt for overflow of TIM15->CNT signalling the completion of a block
/// @param None
void TIM15_IRQHandler(void)
{
	TIM15->SR &= ~TIM_SR_UIF;
	task_flags |= TASK_FLAG_PROCESS_BLOCK;
}

/// @brief De-energizes relay coils after a set time definied in TIM7_init
/// @param None
void TIM7_IRQHandler(void)
{
	TIM7->SR &= ~TIM_SR_UIF; // Reinitialize counter
	TIM7->EGR |= TIM_EGR_UG; // Reinitialize counter
	
		/* Set all relay outputs to low */
	gpio_reset_pin(K1_R);
	gpio_reset_pin(K2_R);
	gpio_reset_pin(K3_R);
	gpio_reset_pin(K1_S);
	gpio_reset_pin(K2_S);
	gpio_reset_pin(K3_S);
}

