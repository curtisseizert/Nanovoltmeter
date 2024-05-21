

#include "spi.h"

/// @brief Initializes SPI registers 
/// @param spi SPI bus to be initialized
/// @param init Container containing register values to be written
/// @note Also enables SPI iff SPI_CR1_SPE bit is set in init
/// @note SPIx->CFG1 bad values are not caught by this function
void spi_init(SPI_TypeDef * spi, const SPI_Init_t * init)
{
	spi->CR1 &= ~SPI_CR1_SPE;
	spi->CR1 = init->CR1 & ~SPI_CR1_SPE;
	spi->CR2 = init->CR2;
	spi->CFG1 = init->CFG1;
	spi->CFG2 = init->CFG2;
	spi->IER = init->IER;

	if(init->CR1 & SPI_CR1_SPE) 
	{
		spi_enable(spi);
		spi->IFCR |= SPI_IFCR_EOTC;
	}
}

/// @brief Extracts the register values from a SPI bus to a SPI_Init_t container
/// @param spi SPI bus with register values to be extracted
/// @return SPI_Init_t containing the register values
/// @note Intended to simplify saving the previous state of a SPI bus for retrieval after
/// @note it is modified.
SPI_Init_t spi_init_from_reg_values(SPI_TypeDef * spi)
{
	SPI_Init_t init = {
		.CR1 = spi->CR1,
		.CR2 = spi->CR2,
		.CFG1 = spi->CFG1,
		.CFG2 = spi->CFG2,
		.IER = spi->IER
	};

	return init;
}

/// @brief Enables SPI
/// @param spi SPI bus to be enabled
void spi_enable(SPI_TypeDef * spi)
{
	spi->CR1 |= SPI_CR1_SPE;
	spi->IFCR |= SPI_IFCR_EOTC;
}

/// @brief Enables DMA (both TX and RX) for the selected SPI bus
/// @param spi SPI bus for which DMA is to be enabled
void spi_dma_enable(SPI_TypeDef * spi)
{
	spi->CR1 &= ~SPI_CR1_SPE;	// Disable SPI

	spi->IER |= SPI_IER_EOTIE;
	spi->CFG1 |= SPI_CFG1_RXDMAEN | SPI_CFG1_TXDMAEN
								| (3U << SPI_CFG1_FTHLV_Pos);
	spi->CR1 |= SPI_CR1_SPE;
}

/// @brief Disables DMA (both TX and RX) for the selected SPI bus
/// @param spi SPI bus for which DMA is to be disabled
void spi_dma_disable(SPI_TypeDef * spi)
{
	spi->CR1 &= ~SPI_CR1_SPE;	// Disable SPI

	spi->IER &= ~SPI_IER_EOTIE;
	spi->CFG1 &= ~(SPI_CFG1_RXDMAEN | SPI_CFG1_TXDMAEN);

	spi->CR1 |= SPI_CR1_SPE;
}

/// @brief Enables end of transfer interrupts for the selected SPI bus
/// @param spi SPI bus for which EOT interrupts are to be enabled
void spi_enable_eot_int(SPI_TypeDef * spi)
{
	spi->IFCR |= SPI_IFCR_EOTC;
	spi->IFCR |= SPI_IFCR_TXTFC;
	spi->IER |= SPI_IER_EOTIE;
}

/// @brief Transmits data over the SPI bus
/// @param spi SPI bus over which transmission is to occur
/// @param data Data to transmit
/// @param size Number of blocks to transmit
void spi_transmit(SPI_TypeDef * spi, uint32_t * data, uint8_t size)
{
	uint8_t i = 0;
	
	while(i < size)
	{
		while(!(spi->SR & SPI_SR_TXP));
		spi->TXDR = data[i];
		i++;
	}
	while(!(spi->SR & SPI_SR_EOT));
	spi->IFCR |= SPI_IFCR_EOTC;
}

/// @brief Transmits one data block over the SPI bus
/// @param spi SPI bus over which transmission is to occur
/// @param data Data to transmit
void spi_transmit_one(SPI_TypeDef * spi, uint32_t * data)
{
	while(!(spi->SR & SPI_SR_TXP));
	
	spi->TXDR = * data;
	
	//while(!(SPI2->SR & SPI_SR_TXTF));
	
	spi->CR1 |= SPI_CR1_CSTART;
}

/// @brief Receives one data block over the SPI bus
/// @param spi SPI bus over which receipt is to occur
/// @return Value of data received
uint32_t spi_receive_one(SPI_TypeDef * spi)
{
	spi->TXDR = 0UL;
	spi->CR1 |= SPI_CR1_CSTART;

	while(!(spi->SR & SPI_SR_EOT));
	
	spi->IFCR |= SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
	
	return spi->RXDR;
}

/// @brief Performs a duplex transmit/receive operation over the SPI bus
/// @param spi SPI bus for the transfer
/// @param data Data to be written
/// @return Received data
uint32_t spi_transmit_receive_one(SPI_TypeDef * spi, uint32_t * data)
{
	while(!(spi->SR & SPI_SR_TXP));
	
	spi->TXDR = * data;
	spi->CR1 |= SPI_CR1_CSTART;

	while(!(spi->SR & SPI_SR_EOT));
	
	spi->IFCR |= SPI_IFCR_EOTC | SPI_IFCR_TXTFC;
	
	return spi->RXDR;
}

/// @brief Starts a SPI transfer
/// @param spi SPI bus for the transfer
void spi_start(SPI_TypeDef * spi)
{
	spi->CR1 |= SPI_CR1_CSTART;
}
