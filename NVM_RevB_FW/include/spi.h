

#ifndef SPI_H
#define SPI_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"


	/* SPI PIN DEFINES */
#define SPI1_SCK_PORT					GPIO_PORT_A
#define SPI1_SCK_PIN					GPIO_PIN_1
#define SPI1_SCK_AF						AF5
#define SPI1_CIPO_PORT					GPIO_PORT_A
#define SPI1_CIPO_PIN					GPIO_PIN_6
#define SPI1_CIPO_AF					AF5
#define SPI1_COPI_PORT					GPIO_PORT_A
#define SPI1_COPI_PIN					GPIO_PIN_7
#define SPI1_COPI_AF					AF5

#define SPI1_NCS_LO					1U << 18
#define SPI1_NCS_HI						1U << 2

#define SPI2_SCK_PORT					GPIO_PORT_B
#define SPI2_SCK_PIN					GPIO_PIN_13
#define SPI2_SCK_AF						AF5
#define SPI2_CIPO_PORT					GPIO_PORT_B
#define SPI2_CIPO_PIN					GPIO_PIN_14
#define SPI2_CIPO_AF					AF5
#define SPI2_COPI_PORT					GPIO_PORT_B
#define SPI2_COPI_PIN					GPIO_PIN_15
#define SPI2_COPI_AF					AF5
#define SPI2_NCS_PORT					GPIO_PORT_B
#define SPI2_NCS_PIN					GPIO_PIN_12
#define SPI2_NCS_AF						AF5

	/* SPI PARAMETER DEFINES */
	
#define SPI1_PSC							1U
#define SPI2_PSC							1U
#define SPI1_DSIZE						23U // 24 bits
#define SPI2_DSIZE						23U // 24 bits

void SPIInit(void);

void SPI1Enable(void);
void SPI2Enable(void);

void SPI1DMAConfig(uint32_t srcAdd, uint32_t destAdd, uint16_t dsize);
void SPI1DMAEnable(void);
void SPI1DMADisable(void);
void SPI1EnableEOTInt(void);

void SPI2Auto(void);
void SPI2DMAEnable(void);
void SPI2EnableEOTInt(void);

void SPI1Transmit(uint32_t * data, uint8_t size);
void SPI2Transmit(uint32_t * data, uint8_t size);

uint32_t SPI1TransmitOne(uint32_t * data);
void SPI2TransmitOne(uint32_t * data);

uint32_t SPI1ReadOne(void);
uint32_t SPI2ReadOne(void);

#endif
