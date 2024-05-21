
#include "ad5686.h"
#include "spi.h"
#include "dma.h"

/// @brief Sets the SPI bus for the AD5686
/// @param dac AD5686_t container for associated peripheral addresses
/// @param spi SPI bus address to be associated with the AD5686
void ad5686_set_spi_bus(AD5686_t * dac, SPI_TypeDef * spi)
{
	dac->spi = spi;
}

/// @brief Writes a code to the DAC with immediate update of DAC register
/// @param dac AD5686_t object
/// @param ch DAC channel to be configured
/// @param code Code to be sent
void ad5686_write_dac(AD5686_t * dac, AD5686Channel_t ch, uint16_t code)
{
	uint32_t data;

	data = (uint32_t) (ch | AD5686_WRITE_UPDATE) << 16;
	data |= (uint32_t) code;
	
	(void) spi_transmit_receive_one(dac->spi, &data); // transmit data
}

/// @brief Formats a code and channel input to correspond to a write/update command for the AD5686
/// @param ch DAC channel to be configured
/// @param code Code to be sent
/// @return Formatted code/channel/command data
uint32_t ad5686_format_data_write(AD5686Channel_t ch, uint16_t code)
{
	uint32_t data;

	data = (uint32_t) (ch | AD5686_WRITE_UPDATE) << 16;
	return data | code;
}

/// @brief Writes all saved channel codes associated with an AD5686_t container
/// @param dac AD5686_t object
/// @note Codes need not have been previously formatted with command/channel information
void ad5686_write_all(AD5686_t * dac)
{
	for(uint8_t i = 0; i < AD5686_NUM_CHANNELS; i++)
	{
		ad5686_write_dac(dac, (AD5686Channel_t) (1U << i), (uint16_t) dac->channel_codes[i]);
	}
}


