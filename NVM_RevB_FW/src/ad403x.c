
	/** 						ad403x.c 
	 * 
	 * 		Basic driver implementation for AD4030-24 and AD4032-24
	 * 
	 **/

#include "ad403x.h"
#include "spi.h"
#include "tim.h"

/// @brief Default values for SPI bus when in register access mode
static SPI_Init_t spi_init_reg_access = {
	.CR1 = SPI_CR1_SSI,
	.CR2 = (1U << SPI_CR2_TSIZE_Pos),
	.CFG1 = (REG_ACCESS_DATA_SIZE << SPI_CFG1_DSIZE_Pos) 
		| (1U << SPI_CFG1_MBR_Pos) | (REG_ACCESS_DATA_SIZE << SPI_CFG1_CRCSIZE_Pos),
	.CFG2 = SPI_CFG2_SSM | SPI_CFG2_MASTER
};

static SPI_Init_t spi_saved_config;

/// @brief Resets the ADC, depends upon previous setup of housekeeping timers for delay
/// @param adc Container for relevant pin and peripheral addresses
void ad403x_reset(const AD403X_t * adc)
{
	gpio_reset_pin(* adc->nreset_pin);
	delay_us(10);
	gpio_set_pin(* adc->nreset_pin);
	delay_us(5000);
}

/// @brief Places the AD403X in register access mode
/// @param adc Container for relevant pin and peripheral addresses
void ad403x_enter_reg_access(const AD403X_t * adc)
{
	uint32_t data = REG_ACCESS_CODE;
	spi_saved_config = spi_init_from_reg_values(adc->spi);

	spi_init(adc->spi, &spi_init_reg_access);
	spi_enable(adc->spi);

	gpio_reset_pin(* adc->ncs_pin);		// Pull NCS high
	(void) spi_transmit_receive_one(adc->spi, &data);
	gpio_set_pin(* adc->ncs_pin); 		// Pull NCS high
}

/// @brief Takes the AD403X out of register access mode 
/// @param adc Container for relevant pin and peripheral addresses
void ad403x_exit_reg_access(const AD403X_t * adc)
{
	uint32_t data = AD403X_EXIT_CFG_MODE | (AD403X_REG_EXIT_CFG_MODE << 8);

	gpio_reset_pin(* adc->ncs_pin);		// Pull NCS high
	(void) spi_transmit_receive_one(adc->spi, &data);
	gpio_set_pin(* adc->ncs_pin); 		// Pull NCS high
	
		// A check to not mess up spi settings if this is called before 
		// ad403x_enter_reg_access
	if(spi_saved_config.CFG2 == 0) spi_saved_config = spi_init_from_reg_values(adc->spi);
	
	spi_init(adc->spi, &spi_saved_config);
}

/// @brief Writes a value to a register of the AD403X (requires being in register access mode)
/// @param adc Container for relevant pin and peripheral addresses
/// @param addr Register address
/// @param value Value to be written to the register
void ad403x_write_register(const AD403X_t * adc, uint16_t addr, uint8_t value)
{
	uint32_t data = (uint32_t) value;

	addr &= ~(1U << 15);
	data |= (uint32_t) (addr << 8);
	
	gpio_reset_pin(* adc->ncs_pin);		// Pull NCS high
	(void) spi_transmit_receive_one(adc->spi, &data);
	gpio_set_pin(* adc->ncs_pin); 		// Pull NCS high
	
}

/// @brief Writes a value to a register of the AD403X without needing to enter register access mode prior to calling.
/// @param adc Container for relevant pin and peripheral addresses
/// @param addr Register address
/// @param value Value to be written to the register
void ad403x_WriteRegisterSingle(const AD403X_t * adc, uint16_t addr, uint8_t value)
{
	ad403x_enter_reg_access(adc);
	ad403x_write_register(adc, addr, value);
	ad403x_exit_reg_access(adc);
}

/// @brief Reads an AD403X register value (must be in register access mode)
/// @param adc Container for relevant pin and peripheral addresses
/// @param addr Register address
/// @return Value read from the register
uint8_t ad403x_read_register(const AD403X_t * adc, uint16_t addr)
{
	uint32_t data;
	uint32_t val;
	addr |= (1U << 15);
	data = (uint32_t) (addr << 8);
	
	gpio_reset_pin(* adc->ncs_pin);		// Pull NCS high
	val = spi_transmit_receive_one(adc->spi, &data);
	gpio_set_pin(* adc->ncs_pin); 		// Pull NCS high
	
	return (uint8_t) (val & 0xFF);
}

/// @brief Reads an AD403X register value without needing to be in register access mode
/// @param adc Container for relevant pin and peripheral addresses
/// @param addr Register address
/// @return Value read from the register
uint8_t ad403x_read_register_single(const AD403X_t * adc, uint16_t addr)
{
	uint8_t val;
	ad403x_enter_reg_access(adc);
	
	val = ad403x_read_register(adc, addr);
	
	ad403x_exit_reg_access(adc);

	return val;
}

