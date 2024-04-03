
#include "i2c.h"

void I2C1GPIOInit(void)
{
		// Configure GPIO pins
	gpioInitPin(I2C1_SCL_PORT, I2C1_SCL_PIN, GPIO_AF, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_NO_PUPD);
	gpioInitPin(I2C1_SDA_PORT, I2C1_SDA_PIN, GPIO_AF, GPIO_OPEN_DRAIN, GPIO_SPEED_FAST, GPIO_NO_PUPD);
	
	// Configure GPIO alternate function registers
	gpioSetAF(I2C1_SCL_PORT, I2C1_SCL_PIN, I2C1_SCL_AF);
	gpioSetAF(I2C1_SDA_PORT, I2C1_SDA_PIN, I2C1_SDA_AF);
}

void I2C1Init(void)
{
	I2C1GPIOInit();
	
		/* Setup I2C_TIMNGR */
	I2C1->TIMINGR |= 0x00602173; 							// Value taken from CubeMX for 400 kHz fast mode at 64 MHz PCLK
	
	//I2C1->CR1 |= I2C_CR1_STOPFACLR;
}

void I2C1DMAInit(void)
{
		/* Setup autonomous control register */
	I2C1->AUTOCR |= I2C_AUTOCR_TCDMAEN;				// DMA request on transfer complete
	
	I2C1->CR1 |= I2C_CR1_RXDMAEN | I2C_CR1_TXDMAEN;

}

void I2C1SetPeripheralAddress(uint8_t addr)
{
	I2C1->CR2 &= ~I2C_CR2_SADD_Msk;
	I2C1->CR2 |= (addr << I2C_CR2_SADD_Pos);
}

void I2C1Enable(void)
{
		/* Enable I2C1 */
	I2C1->CR1 |= I2C_CR1_PE;
}

void I2C1SendData(uint8_t addr, uint8_t * buf, uint8_t size)
{
		/* Reconfigure ADDR and NBYTES bits */
	I2C1->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk);
	I2C1->CR2 |= (size << I2C_CR2_NBYTES_Pos) | (addr << 1);
	
		/* Send data */
	I2C1->CR2 &= ~I2C_CR2_RD_WRN;
	
		/* Clear transmit register if it is not empty */
	if(!(I2C1->ISR & I2C_ISR_TXE)) I2C1->ISR |= I2C_ISR_TXE;
	I2C1->TXDR = buf[0];
	
		/* Start the transfer */
	I2C1->CR2 |= I2C_CR2_START;
	
		/* Fill the TX register */
	for(uint8_t i = 1; i < size; i++){
		while(!(I2C1->ISR & I2C_ISR_TXIS));
		I2C1->TXDR = buf[i];
		
	}
	
		/* Wait for transfer to complete */
	while(!(I2C1->ISR & I2C_ISR_STOPF));
	I2C1->ICR |= I2C_ICR_STOPCF;
}

void I2C1ReceiveData(uint8_t addr, uint8_t * buf, uint8_t size)
{
		/* Reconfigure ADDR and NBYTES bits */
	I2C1->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk);
	I2C1->CR2 |= (size << I2C_CR2_NBYTES_Pos) | (addr << 1);
	
		/* Clear STOP Flag */
	I2C1->ICR |= I2C_ICR_STOPCF;
	
		/* Send data */
	I2C1->CR2 |= I2C_CR2_RD_WRN;
	
		/* Clear receive register */
	buf[0] = I2C1->RXDR;
	
		/* Start the transfer */
	I2C1->CR2 |= I2C_CR2_START;
	
		/* Receive Data */
	for(uint8_t i = 0; i < size; i++){
		while(!(I2C1->ISR & I2C_ISR_RXNE));
		buf[i] = I2C1->RXDR;
	}
	I2C1->CR2 |= I2C_CR2_STOP;
}
