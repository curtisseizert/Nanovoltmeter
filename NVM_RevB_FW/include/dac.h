
#ifndef DAC_H_
#define DAC_H_

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"

#define DAC1_DEFAULT_OUTPUT		0xA00

void DACInit(void);


#endif // DAC_H_
