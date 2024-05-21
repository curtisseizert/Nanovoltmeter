
#ifndef UART_H_
#define UART_H_


#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"
#include "dma.h"
#include "sys_cfg.h"
#include <stdint.h>



#define UART_RX_CMD_SIZE					64		// Length in bytes of a command
#define CMD_BUFFER_LEN						8		// Min number of commands that can fit in buffer

#define UART_TX_BUFFER_SIZE				64
#define UART_RX_BUFFER_SIZE				(UART_RX_CMD_SIZE * CMD_BUFFER_LEN)

extern volatile char uart_tx_buffer[UART_TX_BUFFER_SIZE];
extern volatile char uart_rx_buffer[UART_RX_BUFFER_SIZE];


void USART3Init(void);
void USART3DisableDMATx(void);
void USART3EnableDMATx(void);

void sendDataBlocking(char * buf, uint16_t len);

void USART3SendChar(uint8_t c);

void sendData(char * buf, uint8_t len);


#endif // UART_H_
