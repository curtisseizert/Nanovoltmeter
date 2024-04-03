/**

	OCTOSPI Setup for STM32F446ZE
	Author: Curtis Seizert
	Updated: 24 Aug 2023
	
	*/
	


	
#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "ospi.h"

static uint32_t OCTOSPI_IR_ONELINE_CMD = (OCTOSPI_ONE_LINE << OCTOSPI_CCR_DMODE_Pos);

static uint32_t OCTOSPI_IR_FOURLINE_CMD = (OCTOSPI_FOUR_LINES << OCTOSPI_CCR_DMODE_Pos);



/**
	*	@brief	Configures GPIOs for OCTOSPI
	* @param none
	* @retvalue none
	*/

static void OCTOSPIGPIOInit(void)
{
	
		// Setup GPIO pins
	gpioInitPin(OCTOSPI_CLK_PORT, OCTOSPI_CLK_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);
	gpioInitPin(OCTOSPI_NCS_PORT, OCTOSPI_NCS_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_UP);
	gpioInitPin(OCTOSPI_IO4_PORT, OCTOSPI_IO4_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);
	gpioInitPin(OCTOSPI_IO5_PORT, OCTOSPI_IO5_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);
	gpioInitPin(OCTOSPI_IO6_PORT, OCTOSPI_IO6_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);
	gpioInitPin(OCTOSPI_IO7_PORT, OCTOSPI_IO7_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);

		// Setup alternate function for GPIO Pins
	gpioSetAF(OCTOSPI_CLK_PORT, OCTOSPI_CLK_PIN, 10);
	gpioSetAF(OCTOSPI_NCS_PORT, OCTOSPI_NCS_PIN, 10);
	gpioSetAF(OCTOSPI_IO4_PORT, OCTOSPI_IO4_PIN, 10);
	gpioSetAF(OCTOSPI_IO5_PORT, OCTOSPI_IO5_PIN, 10);
	gpioSetAF(OCTOSPI_IO6_PORT, OCTOSPI_IO6_PIN, 10);
	gpioSetAF(OCTOSPI_IO7_PORT, OCTOSPI_IO7_PIN, 3);

}

/**
	*	@brief	Configures OCTOSPIM for use with AD403x-24
	* @param none
	* @retvalue none
	*/

static void OCTOSPIMInit(void)
{
	OCTOSPIM->PCR[0] |= (3U << OCTOSPIM_PCR_IOHSRC_Pos)
									| (1U << OCTOSPIM_PCR_IOLSRC_Pos)
									| OCTOSPIM_PCR_IOLEN 
									|	OCTOSPIM_PCR_NCSEN
									|	OCTOSPIM_PCR_CLKEN;
	
	OCTOSPIM->PCR[0] &= ~(OCTOSPIM_PCR_IOHEN | OCTOSPIM_PCR_DQSEN);
	OCTOSPIM->PCR[1] &= ~(OCTOSPIM_PCR_IOHEN | OCTOSPIM_PCR_IOLEN 
										| OCTOSPIM_PCR_NCSEN | OCTOSPIM_PCR_CLKEN | OCTOSPIM_PCR_DQSEN);
}

/**
	*	@brief	Configures OCTOSPI for indirect reads
	* @param none
	* @retvalue none
	*/

void OCTOSPIInit(void)
{
	
	OCTOSPIGPIOInit();
	OCTOSPIMInit();
	
	
	// Setup data length register
	OCTOSPI1->DLR = OCTOSPI_DATA_SIZE;
	
	// Setup CCR
	OCTOSPI1->CCR = OCTOSPI_FOUR_LINES;
	
	// Setup Alternate bytes register
	OCTOSPI1->ABR = 0;
	
	// Setup Address Register
	OCTOSPI1->AR = 0;
	
	// Setup Device Control Register
	OCTOSPI1->DCR1 = (OCTOSPI_MTYP << OCTOSPI_DCR1_MTYP_Pos) | // MTYPE 02 (Standard)
									(1U << OCTOSPI_DCR1_DEVSIZE_Pos);				// Devsize = 4 bytes

	
	OCTOSPI1->DCR2 = (OCTOSPI_PRESCALER << OCTOSPI_DCR2_PRESCALER_Pos);
	
	// Setup control register
	OCTOSPI1->CR = 	(OCTOSPI_FMODE_IR << OCTOSPI_CR_FMODE_Pos) |	// Indirect read		
									(OCTOSPI_FIFO_THRESHOLD << OCTOSPI_CR_FTHRES_Pos); // Set FIFO Threshold
									
	// Setup TCR
	OCTOSPI1->TCR |= OCTOSPI_TCR_SSHIFT;

}

/**
	*	@brief	enables OCTOSPI
	* @param none
	* @retvalue none
	*/

void OCTOSPIEnable(void)
{
	OCTOSPI1->CR |= OCTOSPI_CR_EN;	// Set enable bit to 1
}

/**
	*	@brief	disables OCTOSPI
	* @param none
	* @retvalue none
	*/

void OCTOSPIDisable(void)
{
	OCTOSPI1->CR &= ~OCTOSPI_CR_EN;	// Set enable bit to 1
}

/**
	*	@brief	makes the NCS pin a GPIO output for SW control
	* @param none
	* @retvalue none
	*/

void makeNCSgpio(void)
{
	gpioInitPin(OCTOSPI_NCS_PORT, OCTOSPI_NCS_PIN, GPIO_OUTPUT, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_UP);
	GPIOA->BSRR |= (1U << OCTOSPI_NCS_PIN);
}

/**
	*	@brief	makes the (GPIO) NCS pin hardware controlled for OSPI
	* @param none
	* @retvalue none
	*/

void retakeNCS(void)
{
	gpioInitPin(OCTOSPI_NCS_PORT, OCTOSPI_NCS_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_UP);
	gpioSetAF(OCTOSPI_NCS_PORT, OCTOSPI_NCS_PIN, 10);
}

/**
	*	@brief	enables DMA for OCTOSPI transfers
	* @param none
	* @retvalue none
	*/

/*
void octospiDMAInit(void)
{
	// DMA2 Stream 7 Ch 3 for OCTOSPI
	// Circular mode
	
	GPDMA1_Channel1->CCR |= (3U << DMA_CCR_PRIO_Pos)
													| DMA_CCR_TCIE;
	
	GPDMA1_Channel1->CTR2 |= (40U << DMA_CTR2_REQSEL_Pos)
	
	
		// Enable DMA2 clock
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; // Enable 
	
	
		// Wait for DMA2 Stream 0 enable bit to clear before config
	while(DMA2_Stream7->CR & DMA_SxCR_EN);

		// Setup DMA2 Stream 7 Configureation register
	DMA2_Stream7->CR = 	DMA_SxCR_CIRC									// Enable circular mode
										|	DMA_SxCR_MINC									// Enable memory increment mode
										| (2UL << DMA_SxCR_PSIZE_Pos)		// 32-bit peripheral data size
										| (2UL << DMA_SxCR_MSIZE_Pos)		// 32-bit memory data size
										| (3UL << DMA_SxCR_PL_Pos)			// Very high priority level
										|	(3UL << DMA_SxCR_CHSEL_Pos);	// Channel 3

}

void octospiDMAConfig(uint32_t srcAdd, uint32_t destAdd, uint16_t dsize)
{
	DMA2_Stream7->PAR = srcAdd; // Set peripheral address
	DMA2_Stream7->M0AR = destAdd; // Set memory address
	DMA2_Stream7->NDTR = dsize; // Set data size
}


void octospiEnableDMA(void)
{
	DMA2_Stream7->CR |= DMA_SxCR_EN; // Enable DMA2 Stream 7
	OCTOSPI->CR |= OCTOSPI_CR_DMAEN;
}
*/
/**
	*	@brief	disables DMA for OCTOSPI transfers
	* @param none
	* @retvalue none
	*/

void OCTOSPIDisableDMA(void)
{
	OCTOSPI1->CR &= ~OCTOSPI_CR_DMAEN;
}


/**
	*	@brief	sets the data length for OCTOSPI transfers
	* @param uint32_t len: data size in bytes
	* @retvalue none
	*/

void OCTOSPISetDataLength(uint32_t len)
{
	OCTOSPI1->DLR = len - 1;
}

/**
	*	@brief	Reads data (4 bytes) from OCTOSPI bus using one data line
	* @param none
	* @retvalue uint32_t data
	*/

uint32_t OCTOSPIReadOneLine(void)
{
	OCTOSPI1->CCR = OCTOSPI_IR_ONELINE_CMD; // Indirect read mode, 4 lines for data
	OCTOSPI1->IR = 0U; // Trigger read by writing to OCTOSPI_IR
	
	while((OCTOSPI1->SR & OCTOSPI_SR_TCF) != OCTOSPI_SR_TCF); // Wait for operation to complete
	
	OCTOSPI1->FCR |= OCTOSPI_FCR_CTCF;
	return (uint32_t) OCTOSPI1->DR; // Read from FIFO
}

/**
	*	@brief	Reads data (4 bytes) from OCTOSPI bus using one data line using DMA
	* @param none
	* @retvalue none
	*/

void OCTOSPIReadOneLineDMA(void)
{
	OCTOSPI1->CCR = OCTOSPI_IR_ONELINE_CMD; // 
}

/**
	*	@brief	Reads data (4 bytes) from OCTOSPI bus using four data lines
	* @param none
	* @retvalue uint32_t data
	*/

uint32_t OCTOSPIReadFourLine(void)
{
	OCTOSPI1->CCR = OCTOSPI_IR_FOURLINE_CMD; // Indirect read mode, 4 lines for data
	OCTOSPI1->IR = 0U; // Trigger read by writing to OCTOSPI_IR
	
	while((OCTOSPI1->SR & OCTOSPI_SR_TCF) != OCTOSPI_SR_TCF); // Wait for operation to complete
	
	OCTOSPI1->FCR |= OCTOSPI_FCR_CTCF;
	return (uint32_t) OCTOSPI1->DR; // Read from FIFO
}

/**
	*	@brief	Reads data (4 bytes) from OCTOSPI bus using four data lines using DMA
	* @param none
	* @retvalue none
	*/

void OCTOSPIReadFourLineDMA(void)
{
	OCTOSPI1->CCR = OCTOSPI_IR_FOURLINE_CMD; // Indirect read mode, 4 lines for data
}

uint32_t OCTOSPIRead(void)
{
	OCTOSPI1->IR = 0U; // Trigger read by writing to OCTOSPI_IR
	
	while(OCTOSPI1->SR & OCTOSPI_SR_BUSY); // Wait for operation to complete
	
	OCTOSPI1->FCR |= OCTOSPI_FCR_CTCF;
	return (uint32_t) OCTOSPI1->DR; // Read from FIFO
}

/**
	*	@brief	Reads data (4 bytes) from OCTOSPI FIFO register
	* @param none
	* @retvalue uint32_t data
	*/

uint32_t OCTOSPIReadFIFO(void)
{
	return (uint32_t) OCTOSPI1->DR;
}

