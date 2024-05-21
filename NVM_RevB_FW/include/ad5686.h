	
	/*	Basic driver for AD5686 in NVM Rev B
	*
	*
	*/

#ifndef AD5686_H_
#define AD5686_H_

#include "stdint.h"
#include "stm32u575xx.h"
#include "stm32u5xx.h"

/* Note: Command defines are aligned with the first byte of the transfer */

	/* COMMAND DEFINES */
#define AD5686_WRITE_DAC			0x01 << 4
#define AD5686_UPDATE_DAC			0x02 << 4
#define AD5686_WRITE_UPDATE		0x03 << 4
#define AD5686_TOGGLE_POWER		0x04 << 4
#define AD5686_NLDAC_MASK_REG	0x05 << 4
#define AD5686_SW_RESET				0x06 << 4
#define AD5686_DCEN						0x08 << 4		// Daisy chain enable
#define AD5686_READBACK				0x09 << 4
#define AD5686_NO_OP					0x0F << 4

	/* ADDRESS DEFINES */
typedef enum{
	AD5686_DAC_A					= (1U << 0),
	AD5686_DAC_B					= (1U << 1),
	AD5686_DAC_C					= (1U << 2),
	AD5686_DAC_D					= (1U << 3)
}AD5686Channel_t;

	/* OUTPUT DEFINES */
#define MOD1_HI_DAC					AD5686_DAC_A	// Output A
#define V_OS_DAC					AD5686_DAC_B	// Output B
#define MOD2_HI_DAC					AD5686_DAC_C	// Output C
#define MOD_LO_DAC					AD5686_DAC_D	// Output D

	/* REPEAT USE DEFINES */
#define AD5686_WRT_UP_DAC_A		(AD5686_WRITE_UPDATE | AD5686_DAC_A)
#define AD5686_WRT_UP_DAC_B		(AD5686_WRITE_UPDATE | AD5686_DAC_B)
#define AD5686_WRT_UP_DAC_C		(AD5686_WRITE_UPDATE | AD5686_DAC_C)
#define AD5686_WRT_UP_DAC_D		(AD5686_WRITE_UPDATE | AD5686_DAC_D)

	/* DEFAULT DAC OUTPUTS */
#define MOD1_HI_DEFAULT				65535U	// 2.50V
#define MOD2_HI_DEFAULT				65535U	// 2.50V
#define V_OS_DEFAULT					0x4B80
#define MOD_LO_DEFAULT				20000U

#define AD5686_NUM_CHANNELS			4U

typedef struct{
	SPI_TypeDef * spi;
	DMA_Channel_TypeDef * dma;
	uint32_t channel_codes[AD5686_NUM_CHANNELS];
}AD5686_t;


void ad5686_set_spi_bus(AD5686_t * dac, SPI_TypeDef * spi);
void ad5686_write_dac(AD5686_t * dac, AD5686Channel_t ch, uint16_t code);
uint32_t ad5686_format_data_write(AD5686Channel_t ch, uint16_t code);

void ad5686_write_all(AD5686_t * dac);

#endif //AD5686_H_
