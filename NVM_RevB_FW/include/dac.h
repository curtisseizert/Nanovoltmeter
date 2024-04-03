
#ifndef DAC_H
#define DAC_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"


#define DAC1_OUT1_PORT					GPIO_PORT_A
#define DAC1_OUT1_PIN					GPIO_PIN_4

#define DAC1_DEFAULT_OUTPUT		0xA00

void DACInit(void);


#endif
