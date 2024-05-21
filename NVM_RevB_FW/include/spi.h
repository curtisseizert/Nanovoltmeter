

#ifndef SPI_H_
#define SPI_H_

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"


	/* SPI PARAMETER DEFINES */
	
#define SPI1_PSC							1U
#define SPI2_PSC							1U
#define SPI1_DSIZE							23U // 24 bits
#define AD403X_AVERAGING_DSIZE				31U	// 32 bits
#define SPI2_DSIZE							23U // 24 bits

#define SPI_CFG1_RESET_VALUE	((uint32_t) 0x00070007)
	
typedef struct{
	uint32_t CR1;
	uint32_t CR2;
	uint32_t CFG1;
	uint32_t CFG2;
	uint32_t IER;

} SPI_Init_t;	

void spi_init(SPI_TypeDef * spi, const SPI_Init_t * init);
SPI_Init_t spi_init_from_reg_values(SPI_TypeDef * spi);

void spi_enable(SPI_TypeDef * spi);
void spi_enable_eot_int(SPI_TypeDef * spi);

void spi_dma_enable(SPI_TypeDef * spi);
void spi_dma_disable(SPI_TypeDef * spi);

void spi_transmit(SPI_TypeDef * spi, uint32_t * data, uint8_t size);
void spi_transmit_one(SPI_TypeDef * spi, uint32_t * data);
uint32_t spi_receive_one(SPI_TypeDef * spi);
uint32_t spi_transmit_receive_one(SPI_TypeDef * spi, uint32_t * data);
void spi_start(SPI_TypeDef * spi);


#endif // SPI_H_
