
#include "i2c.h"

void i2c_init(I2C_TypeDef * i2c)
{
	
}

/// @brief Sends data over the I2C bus
/// @param i2c I2C bus to be used
/// @param addr Target peripheral address
/// @param buf Buffer of data to be sent
/// @param size Size of the data buffer
void i2c_send_data(I2C_TypeDef * i2c, uint8_t addr, uint8_t * buf, uint8_t size)
{
			/* Reconfigure ADDR and NBYTES bits */
	i2c->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk);
	i2c->CR2 |= (uint32_t) (size << I2C_CR2_NBYTES_Pos) | ((uint32_t) addr << 1U);
	
		/* Send data */
	i2c->CR2 &= ~I2C_CR2_RD_WRN;
	
		/* Clear transmit register*/
	i2c->ISR |= I2C_ISR_TXE;
	i2c->TXDR = buf[0];
	
		/* Start the transfer */
	i2c->CR2 |= I2C_CR2_START;
	
		/* Fill the TX register */
	for(uint8_t i = 1; i < size; i++){
		while(!(i2c->ISR & I2C_ISR_TXIS));
		i2c->TXDR = buf[i];
		
	}
	
		/* Wait for transfer to complete */
	while(!(i2c->ISR & I2C_ISR_STOPF));
	i2c->ICR |= I2C_ICR_STOPCF;
}

/// @brief Receives data over the I2C bus
/// @param i2c I2C bus for the transfer
/// @param addr Target peripheral address
/// @param buf Buffer for data to be received
/// @param size Size of the data to be received
void i2c_receive_data(I2C_TypeDef * i2c, uint8_t addr, uint8_t * buf, uint8_t size)
{
		/* Reconfigure ADDR and NBYTES bits */
	i2c->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk);
	i2c->CR2 |= (uint32_t) (size << I2C_CR2_NBYTES_Pos) | ((uint32_t) addr << 1U);
	
		/* Clear STOP Flag */
	i2c->ICR |= I2C_ICR_STOPCF;
	
		/* Send data */
	i2c->CR2 |= I2C_CR2_RD_WRN;
	
		/* Clear receive register */
	buf[0] = (uint8_t) i2c->RXDR;
	
		/* Start the transfer */
	i2c->CR2 |= I2C_CR2_START;
	
		/* Receive Data */
	for(uint8_t i = 0; i < size; i++){
		while(!(i2c->ISR & I2C_ISR_RXNE));
		buf[i] = (uint8_t) i2c->RXDR;
	}
	i2c->CR2 |= I2C_CR2_STOP;
}
/*
void I2C_DMAInit(I2C_TypeDef * i2c)
{
		// Setup autonomous control register 
	i2c->AUTOCR |= I2C_AUTOCR_TCDMAEN;				// DMA request on transfer complete
	
	i2c->CR1 |= I2C_CR1_RXDMAEN | I2C_CR1_TXDMAEN;

}
*/

/// @brief Sets the I2C peripheral address
/// @param i2c I2C bus for the peripheral
/// @param addr Target peripheral address
void i2c_set_peripheral_address(I2C_TypeDef * i2c, uint8_t addr)
{
	i2c->CR2 &= ~I2C_CR2_SADD_Msk;
	i2c->CR2 |= ((uint32_t) addr << I2C_CR2_SADD_Pos);
}

/// @brief Enables I2C
/// @param i2c I2C bus to be enabled
void i2c_enable(I2C_TypeDef * i2c)
{
		/* Enable I2C1 */
	i2c->CR1 |= I2C_CR1_PE;
}
