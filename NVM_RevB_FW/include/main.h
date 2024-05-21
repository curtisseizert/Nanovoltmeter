/**
	*	main.h
	*	main header file
	*
	*/


#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>

#include "uart.h"
#include "tim.h"
#include "gpio.h"
#include "adc.h"
#include "spi.h"
#include "dac.h"
#include "i2c.h"
#include "dma.h"

#define MAX_TASK_BIT					31

#define TASK_FLAG_NO_TASK				0
#define TASK_FLAG_PROCESS_CYCLE			(1U << 1)
#define TASK_FLAG_PROCESS_BLOCK			(1U << 0)
#define TASK_FLAG_PROCESS_INPUT			(1U << 2)
#define TASK_FLAG_SEND_DATA				(1U << 3)


extern volatile uint16_t ind, flags;

void nvicInit(void);

void set_relay_defaults(void);




#endif // MAIN_H_
