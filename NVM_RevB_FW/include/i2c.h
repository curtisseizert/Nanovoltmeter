
#ifndef I2C_H_
#define I2C_H_

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"

void i2c_init(I2C_TypeDef * i2c);
void i2c_send_data(I2C_TypeDef * i2c, uint8_t addr, uint8_t * buf, uint8_t size);
void i2c_receive_data(I2C_TypeDef * i2c, uint8_t addr, uint8_t * buf, uint8_t size);
void i2c_set_peripheral_address(I2C_TypeDef * i2c, uint8_t addr);
void i2c_enable(I2C_TypeDef * i2c);

#endif // I2C_H_
