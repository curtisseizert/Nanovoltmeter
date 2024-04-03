
#include "ad403x.h"
#include "ospi.h"
#include "gpio.h"
#include "spi.h"
#include "tim.h"

void AD403X_Reset(void)
{
	gpioResetPin(ADC_NRESET_Port, ADC_NRESET_Pin);
	delay_us(10);
	gpioSetPin(ADC_NRESET_Port, ADC_NRESET_Pin);
	delay_us(5000);
}

void AD403X_EnterRegAccess(void)
{
	uint32_t data[1];
	SPI1->CR1 &= ~SPI_CR1_SPE;
	SPI1->CFG1 &= ~SPI_CFG1_DSIZE_Msk;
	SPI1->CFG1 |= (SPI1_DSIZE << SPI_CFG1_DSIZE_Pos); // 24-bit data size
	SPI1->CFG2 &= ~SPI_CFG2_COMM_Msk;
	SPI1->CR1 |= SPI_CR1_SPE;
	
	data[0] = (0xBFFF << 8);
	
	makeNCSgpio(); // Take hardware control of NCS pin from OCTOSPI
	
	GPIOA->BSRR |= (1U << (OCTOSPI_NCS_PIN + 16)); // Pull NCS low
	SPI1TransmitOne(data);
	GPIOA->BSRR |= (1U << (OCTOSPI_NCS_PIN)); // Pull NCS high
}

void AD403X_ExitRegAccess(void)
{
	uint32_t data[1];
	
	data[0] = AD403X_EXIT_CFG_MODE;
	data[0] |= (AD403X_REG_EXIT_CFG_MODE << 8);
	
	GPIOA->BSRR |= (1U << (OCTOSPI_NCS_PIN + 16)); // Pull NCS low
	SPI1TransmitOne(data);
	GPIOA->BSRR |= (1U << (OCTOSPI_NCS_PIN)); // Pull NCS high
	
	SPI1->CR1 &= ~SPI_CR1_SPE;
	SPI1->CFG1 |= (31U << SPI_CFG1_DSIZE_Pos); // 32-bit data size
	SPI1->CFG2 |= (2U << SPI_CFG2_COMM_Pos);
	SPI1->CR1 |= SPI_CR1_SPE;
	
	//retakeNCS();
}


void AD403X_WriteRegister(uint16_t addr, uint8_t value)
{
	uint32_t data[1];
	
	addr &= ~(1U << 15);
	data[0] = (uint32_t) ((addr << 8) | value);
	
	GPIOA->BSRR |= (1U << (OCTOSPI_NCS_PIN + 16)); // Pull NCS low
	SPI1TransmitOne(data);
	GPIOA->BSRR |= (1U << (OCTOSPI_NCS_PIN)); // Pull NCS high
	
}

void AD403X_WriteRegisterSingle(uint16_t addr, uint8_t value)
{
	AD403X_EnterRegAccess();
	
	AD403X_WriteRegister(addr, value);
	
	AD403X_ExitRegAccess();
}

uint8_t AD403X_ReadRegister(uint16_t addr)
{
	uint32_t data[1];
	uint32_t val;
	addr |= (1U << 15);
	data[0] = (uint32_t) (addr << 8);
	
	GPIOA->BSRR |= (1U << (OCTOSPI_NCS_PIN + 16)); // Pull NCS low
	val = SPI1TransmitOne(data);
	GPIOA->BSRR |= (1U << (OCTOSPI_NCS_PIN)); // Pull NCS high
	
	return (uint8_t) (val & 0xFF);
	
}

uint8_t AD403X_ReadRegisterSingle(uint16_t addr)
{
	uint8_t val;
	AD403X_EnterRegAccess();
	
	val = AD403X_ReadRegister(addr);
	
	AD403X_ExitRegAccess();
	
	return val;
}

