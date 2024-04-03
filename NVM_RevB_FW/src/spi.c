

#include "spi.h"

/*
static void spi1DMAInit(void)
{
			// DMA2 Stream 3 Ch 3 for SPI1_TX
	SPI1->CR2 |= SPI_CR2_TXEIE | SPI_CR2_TXDMAEN; // Enable TX empty interrupts and enable TX DMA
	
		// Enable DMA2 clock
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN; // Enable 
	
	
		// Wait for DMA2 Stream 3 enable bit to clear before config
	while(DMA2_Stream3->CR & DMA_SxCR_EN);

		// Setup DMA2 Stream 3 Configureation register
	DMA2_Stream3->CR = 	DMA_SxCR_CIRC									// Enable circular mode
										|	DMA_SxCR_MINC									// Enable memory increment mode
										| (1UL << DMA_SxCR_DIR_Pos)			// Set direction memory to peripheral
										| (0UL << DMA_SxCR_PSIZE_Pos)		// 8-bit peripheral data size
										| (0UL << DMA_SxCR_MSIZE_Pos)		// 8-bit memory data size
										| (1UL << DMA_SxCR_PL_Pos)			// Med priority level
										|	(3UL << DMA_SxCR_CHSEL_Pos);	// Channel 3
}

void spi1DMAConfig(uint32_t srcAdd, uint32_t destAdd, uint16_t dsize)
{
	DMA2_Stream3->PAR = srcAdd; // Set peripheral address
	DMA2_Stream3->M0AR = destAdd; // Set memory address
	DMA2_Stream3->NDTR = dsize; // Set data size
}

void spi1DMAEnable(void)
{
	DMA2_Stream3->CR |= DMA_SxCR_EN; // Enable DMA2 Stream 3
}
*/
void SPIInit(void)
{
	// Setup GPIO pins
	gpioInitPin(SPI1_SCK_PORT, SPI1_SCK_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);
	gpioInitPin(SPI1_CIPO_PORT, SPI1_CIPO_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_NO_PUPD);
	gpioInitPin(SPI1_COPI_PORT, SPI1_COPI_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);
	
	gpioInitPin(SPI2_SCK_PORT, SPI2_SCK_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);
	gpioInitPin(SPI2_CIPO_PORT, SPI2_CIPO_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_NO_PUPD);
	gpioInitPin(SPI2_COPI_PORT, SPI2_COPI_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_DOWN);
	gpioInitPin(SPI2_NCS_PORT, SPI2_NCS_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_MAX, GPIO_PULL_UP);


		// Setup alternate function for GPIO Pins
	gpioSetAF(SPI1_SCK_PORT, SPI1_SCK_PIN, SPI1_SCK_AF);
	gpioSetAF(SPI1_CIPO_PORT, SPI1_CIPO_PIN, SPI1_CIPO_AF);
	gpioSetAF(SPI1_COPI_PORT, SPI1_COPI_PIN, SPI1_COPI_AF);
	
	gpioSetAF(SPI2_SCK_PORT, SPI2_SCK_PIN, SPI2_SCK_AF);
	gpioSetAF(SPI2_CIPO_PORT, SPI2_CIPO_PIN, SPI2_CIPO_AF);
	gpioSetAF(SPI2_COPI_PORT, SPI2_COPI_PIN, SPI2_COPI_AF);
	gpioSetAF(SPI2_NCS_PORT, SPI2_NCS_PIN, SPI2_NCS_AF);
	
	/* Configure SPI1 & SPI2 Registers */
				
	
	SPI1->CR2 |= (1U << SPI_CR2_TSIZE_Pos);			
	SPI1->CFG1 |= SPI_CFG1_BPASS | // Bypass prescaler
								(SPI1_DSIZE << SPI_CFG1_DSIZE_Pos); // 24-bit data size
	
		/* Set CR1_SSI and CFG2_SSM to prevent mode fault */
	SPI1->CR1 |= SPI_CR1_SSI; // Set internal SS input to 1
	SPI1->CFG2 |= SPI_CFG2_SSM; // Software SS mgmt

								
	SPI1->CFG2 |= SPI_CFG2_MASTER; // Set MCU as controller
	
	SPI2->CR2 |= (1U << SPI_CR2_TSIZE_Pos);	// 1 block transfer
	SPI2->CFG1 |= (1U << SPI_CFG1_MBR_Pos)
								| (SPI2_DSIZE << SPI_CFG1_DSIZE_Pos); // 24-bit data size
								
	SPI2->CFG2 |= SPI_CFG2_SSOE // NCS Output enable
								| SPI_CFG2_CPHA // Falling edge of normally low SCK
								| SPI_CFG2_MASTER // Set MCU as controller
								| (1U << SPI_CFG2_MSSI_Pos)
								| (1U << SPI_CFG2_COMM_Pos);
								
	SPI1->CR1 |= SPI_CR1_SPE;
	SPI2->CR1 |= SPI_CR1_SPE;
	
	SPI1->IFCR |= SPI_IFCR_EOTC;
	SPI2->IFCR |= SPI_IFCR_EOTC;
							
}

/**
	*	@brief	enables SPI1
	* @param none
	* @retvalue none
	*/

void SPI1Enable(void)
{
	SPI1->CR1 |= SPI_CR1_SPE;
}

void SPI1DMAEnable(void)
{
	SPI1->CR1 &= ~SPI_CR1_SPE;	// Disable SPI

	SPI1->IER |= SPI_IER_EOTIE;
	SPI1->CFG1 |= SPI_CFG1_RXDMAEN
								| (3U << SPI_CFG1_FTHLV_Pos);
	SPI1->CR1 |= SPI_CR1_SPE;
		
}

void SPI1DMADisable(void)
{
	SPI1->CR1 &= ~SPI_CR1_SPE;	// Disable SPI

	SPI1->IER &= ~SPI_IER_EOTIE;
	SPI1->CFG1 &= ~SPI_CFG1_RXDMAEN;

	SPI1->CR1 |= SPI_CR1_SPE;
		
}

void SPI1EnableEOTInt(void)
{
	SPI1->IFCR |= SPI_IFCR_EOTC;
	SPI1->IFCR |= SPI_IFCR_TXTFC;
	SPI1->IER |= SPI_IER_EOTIE;
}

/**
	*	@brief	enables SPI2
	* @param none
	* @retvalue none
	*/

void SPI2Enable(void)
{
	SPI2->CR1 |= SPI_CR1_SPE;
}

/**
	*	@brief	enables SPI2
	* @param none
	* @retvalue none
	*/

void SPI2DMAEnable(void)
{
	SPI2->CR1 &= ~SPI_CR1_SPE;	// Disable SPI
	
	SPI2->CR2 = 4U;

	SPI2->IER |= SPI_IER_EOTIE;
	SPI2->CFG1 |= SPI_CFG1_TXDMAEN
								| (3U << SPI_CFG1_FTHLV_Pos);
	
}



void SPI2EnableEOTInt(void)
{
	SPI2->IFCR |= SPI_IFCR_EOTC;
	SPI2->IFCR |= SPI_IFCR_TXTFC;
	SPI2->IER |= SPI_IER_EOTIE;
}

/**	
	*	@brief	Transmits 32-bit data over SPI1
	* @param	data -  pointer to data address
	* @param 	size - number of blocks
	* @retvalue none
	*/

void SPI1Transmit(uint32_t * data, uint8_t size)
{
	uint8_t i = 0;
	
	while(i < size)
	{
		while(!(SPI1->SR & SPI_SR_TXP));
		SPI1->TXDR = data[i];
		i++;
	}
	while(!(SPI1->SR & SPI_SR_EOT));
	SPI1->IFCR |= SPI_IFCR_EOTC;
}

/**	
	*	@brief	Transmits one data block over SPI1
	* @param	data -  pointer to data address
	* @param 	size - number of blocks
	* @retvalue none
	*/

uint32_t SPI1TransmitOne(uint32_t * data)
{
	while(!(SPI1->SR & SPI_SR_TXP));
	
	SPI1->TXDR = data[0];
	
	while(!(SPI1->SR & SPI_SR_TXTF));
	
	SPI1->CR1 |= SPI_CR1_CSTART;
	
	SPI1->IFCR |= SPI_IFCR_TXTFC;

	while(!(SPI1->SR & SPI_SR_EOT));
	SPI1->IFCR |= SPI_IFCR_EOTC;
	SPI1->IFCR |= SPI_IFCR_TXTFC;
	
	return SPI1->RXDR;

}


/**	
	*	@brief	Transmits 32-bit data over SPI2
	* @param	data -  pointer to data address
	* @param 	size - number of blocks
	* @retvalue none
	*/

void SPI2Transmit(uint32_t * data, uint8_t size)
{
	uint8_t i = 0;
	
	while(i < size)
	{
		while(!(SPI2->SR & SPI_SR_TXP));
		SPI2->TXDR = data[i];
		i++;
	}
	while(!(SPI2->SR & SPI_SR_EOT));
	SPI2->IFCR |= SPI_IFCR_EOTC;
}

void SPI2TransmitOne(uint32_t * data)
{
	while(!(SPI2->SR & SPI_SR_TXP));
	
	SPI2->TXDR = data[0];
	
	//while(!(SPI2->SR & SPI_SR_TXTF));
	
	SPI2->CR1 |= SPI_CR1_CSTART;
}

uint32_t SPI1ReadOne()
{
	//while(!(SPI1->SR & SPI_SR_TXP));
	
	SPI1->TXDR = 0UL;
	SPI1->CR1 |= SPI_CR1_CSTART;

	while(!(SPI1->SR & SPI_SR_EOT));
	
	SPI1->IFCR |= SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
	
	return SPI1->RXDR;
}

uint32_t SPI2ReadOne()
{
	while(!(SPI1->SR & SPI_SR_TXP));
	
	SPI2->TXDR = 0UL;
	SPI2->CR1 |= SPI_CR1_CSTART;

	while(!(SPI2->SR & SPI_SR_EOT));
	
	SPI2->IFCR |= SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
	
	return SPI2->RXDR;
}
