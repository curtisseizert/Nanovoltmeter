
#include "ad5686.h"
#include "spi.h"
#include "dma.h"

uint16_t AD5686_WriteDAC(uint8_t addr, uint16_t code)
{
	uint32_t data[1];


	addr &= ~(7U << 4);
	addr |= AD5686_WRITE_UPDATE;
	data[0] = (uint32_t) ((addr << 16) | code);
	
	SPI2TransmitOne(data); // transmit data

	return 0;
}

uint16_t AD5686_WriteDACDMA(uint8_t addr, uint16_t code)
{
	uint32_t data[1];


	addr &= ~(7U << 4);
	addr |= AD5686_WRITE_UPDATE;
	
	data[0] = (addr << 16) | code;
	DMA_CH1_Config((uint32_t) data, (uint32_t) &SPI2->TXDR, 4);
	DMA_CH1_Enable();
	
	SPI2->CR1 |= SPI_CR1_CSTART;

	return 0;
}

void AD5686_SetDefaultOutputs(void)
{
	AD5686_WriteDAC(MOD1_HI_DAC, MOD1_HI_DEFAULT);
	AD5686_WriteDAC(MOD2_HI_DAC, MOD2_HI_DEFAULT);
	AD5686_WriteDAC(V_OS_DAC, V_OS_DEFAULT);
	AD5686_WriteDAC(MOD_LO_DAC, MOD_LO_DEFAULT);
	AD5686_WriteDAC(MOD1_HI_DAC, MOD1_HI_DEFAULT);
	AD5686_WriteDAC(MOD2_HI_DAC, MOD2_HI_DEFAULT);
	AD5686_WriteDAC(V_OS_DAC, V_OS_DEFAULT);
	AD5686_WriteDAC(MOD_LO_DAC, MOD_LO_DEFAULT);
}
