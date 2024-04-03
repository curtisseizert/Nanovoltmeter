#ifndef SERIAL_IO_H
#define SERIAL_IO_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "sys_cfg.h"
#include "stdint.h"
#include "uart.h"
#include "acq.h"


extern volatile char uartTxBuf[UART_TX_BUFFER_SIZE];
extern volatile char uartRxBuf[UART_RX_BUFFER_SIZE];
extern volatile uint16_t ind, flags;

extern volatile struct acq_param acq1, acq2;

extern volatile uint8_t cmdInd[2];

void parseInput(char * inputcmd);

void gpioCDSCmd(uint8_t phase);

void sendParameterString(struct acq_param * acq);

void sendRegValue(uint16_t reg, uint8_t val);


#endif