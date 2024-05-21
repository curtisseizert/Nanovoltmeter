
#ifndef SERIAL_IO_H_
#define SERIAL_IO_H_

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "stdint.h"
#include "acq.h"
#include "fifo.h"
#include "uart.h"

#define UART_RX_PTR_ARRAY_LEN       8
#define UART_RX_MAX_CMD_LEN         64
#define SERIAL_IO_MAX_RESPONSE_LEN  128

extern volatile uint16_t ind, flags;
extern AcqParam_t acq1, acq2;

typedef struct{
    uint8_t buffer[UART_RX_BUFFER_SIZE];    // Circular buffer containing all received data
    uint8_t * ptr[UART_RX_PTR_ARRAY_LEN];   // Array of pointers to the first element of a received string
    uint16_t ind_recd;                      // Index in .ptr for the last received string
    uint16_t ind_procd;                     // Index in .ptr for the last processed string
    DMA_Channel_TypeDef * dma;              // DMA Channel used to transfer from UART_RDR
                                            // to buffer
}UartRx_t;

typedef struct{
    uint8_t buffer[UART_RX_MAX_CMD_LEN];
}CmdString_t;

typedef enum{
    SERIAL_IO_NO_ERROR,
    SERIAL_IO_OUTBUFFER_NRDY
}SerialErr_t;

SerialErr_t send_serial_result(FIFO_t * fifo);
void serial_print(const char * str);

void uart_rx_t_init(UartRx_t * uart_rx, DMA_Channel_TypeDef * dma);
void uart_rx_increment_index(UartRx_t * uart_rx);

void parse_rx_buffer(UartRx_t * rx);
uint16_t flatten_circ_buffer(UartRx_t * rx, CmdString_t * new_buf);


#endif // SERIAL_IO_H_
