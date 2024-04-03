#ifndef I2C_H
#define I2C_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"

#define I2C1_SCL_PORT			GPIO_PORT_B
#define I2C1_SCL_PIN			GPIO_PIN_6
#define I2C1_SCL_AF				AF4
#define I2C1_SDA_PORT			GPIO_PORT_B
#define I2C1_SDA_PIN			GPIO_PIN_7
#define I2C1_SDA_AF				AF4


void I2C1Init(void);
void I2C1DMAInit(void);
void I2C1SetPeripheralAddress(uint8_t addr);
void I2C1Enable(void);

void I2C1SendData(uint8_t addr, uint8_t * buf, uint8_t size);
void I2C1ReceiveData(uint8_t addr, uint8_t * buf, uint8_t size);

#endif