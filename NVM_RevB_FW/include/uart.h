
#ifndef uart_h
#define uart_h


#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"
#include "dma.h"
#include "sys_cfg.h"
#include <stdint.h>

#define UART4_BAUD				1500000

#define UART_RX_CMD_SIZE					32		// Length in bytes of a command
#define CMD_BUFFER_LEN						4			// Number of commands that can fit in buffer

#define UART_TX_BUFFER_SIZE				64
#define UART_RX_BUFFER_SIZE				(UART_RX_CMD_SIZE * CMD_BUFFER_LEN)

#define UART4_RX_PORT			GPIO_PORT_C
#define UART4_RX_PIN			GPIO_PIN_11
#define UART4_RX_AF				AF8
#define UART4_TX_PORT			GPIO_PORT_C
#define UART4_TX_PIN			GPIO_PIN_10
#define UART4_TX_AF				AF8

extern volatile char uartTxBuf[UART_TX_BUFFER_SIZE];
extern volatile char uartRxBuf[UART_RX_BUFFER_SIZE];


void UART4Init(void);
void UART4DisableDMATx(void);
void UART4EnableDMATx(void);

void sendDataBlocking(char * buf, uint8_t len);

void UART4SendChar(uint8_t c);

void sendData(char * buf, uint8_t len);


#endif
