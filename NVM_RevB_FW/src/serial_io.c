
	/* serial_io.c */
#include <stdio.h>
#include <stdlib.h>

#include "serial_io.h"

#include "ad5686.h"
#include "ad403x.h"
#include "tim.h"
#include "nvmb.h"
#include "dma.h"
#include "cmd_handler.h"


/// @brief Moves FIFO data to a character buffer and enables DMA for sending over U(S)ART
/// @param fifo Container of data to be output to the user
/// @return SERIAL_IO_NO_ERROR if FIFO was ready and data was sent
/// @return SERIAL_IO_OUTBUFFER_NRDY if FIFO was not ready and data was not sent
/// @note Source address for the DMA transfer is determined at compile time (see dma.c)
/// @note Does not check for proper setup of U(S)ART or DMA
/// @note Does not send any results if no data are requested.
SerialErr_t send_serial_result(FIFO_t * fifo)
{
	AcqData_t * dataptr = NULL;
	uint16_t len = 0;
	uint16_t len_tot = 0;

	if(fifo_output_data(fifo, &dataptr) == FIFO_STATUS_OK)
	{
			// Fill tx buffer with requested data, comma separated
		if(fifo->data_reqd & FIFO_VAVG_MASK)
		{
			len = (uint16_t) sprintf((char *)&uart_tx_buffer[len_tot], 
				"%E, ", dataptr->v_avg);
			len_tot += len;
		} 
		if(fifo->data_reqd & FIFO_VOS_MASK)
		{
			len = (uint16_t) sprintf((char *)&uart_tx_buffer[len_tot],
				"%E, ", (double) dataptr->v_os);
			len_tot += len;
		} 
		if(fifo->data_reqd & FIFO_TEMP1_MASK)
		{
			len = (uint16_t) sprintf((char *)&uart_tx_buffer[len_tot],
				"%2.3f, ", (double) dataptr->temps[0]);
			len_tot += len;
		} 
		if(fifo->data_reqd & FIFO_TEMP2_MASK)
		{
			len = (uint16_t) sprintf((char *)&uart_tx_buffer[len_tot],
				"%2.3f, ", (double) dataptr->temps[1]);
			len_tot += len;
		} 
		if(fifo->data_reqd & FIFO_TEMP3_MASK)
		{
			len = (uint16_t) sprintf((char *)&uart_tx_buffer[len_tot],
				"%2.3f, ", (double) dataptr->temps[2]);
			len_tot += len;
		} 

		if(fifo->data_reqd != 0)
		{
			len -= 2; // Backup to overwrite the final ", "

				// Add a newline + carriage return to terminate the string
			len += sprintf((char *)&uart_tx_buffer[len], "\n\r");

			dma_set_data_bytes(GPDMA1_Channel2, len);
			dma_enable_channel(GPDMA1_Channel2);
		}
	}
	else return SERIAL_IO_OUTBUFFER_NRDY;

	return SERIAL_IO_NO_ERROR;
}

/// @brief Initializes the UartRx_t container with the corresponding DMA_Channel_TypeDef
/// @param rx UartRx_t container to be intialized
/// @param dma DMA channel used for transfers from UART RDR to buffer
void uart_rx_t_init(UartRx_t * rx, DMA_Channel_TypeDef * dma)
{
	rx->dma = dma;
	rx->ptr[0] = (uint8_t *)&rx->buffer;
}

/// @brief Increments ind_recd (index received) and saves the current DMA destination address to the pointer array
/// @param rx UartRx_t container for serial data received
void uart_rx_increment_index(UartRx_t * rx)
{
	rx->ind_recd = (++rx->ind_recd) % UART_RX_PTR_ARRAY_LEN;
	rx->ptr[rx->ind_recd] = 
		(uint8_t *) rx->dma->CDAR;
}

static uint16_t uart_rx_increment_procd(UartRx_t * rx)
{
	rx->ind_procd = (++rx->ind_procd) % UART_RX_PTR_ARRAY_LEN;
	return rx->ind_procd;
}

/// @brief Parses and performs all unprocessed commands in the serial rx buffer
/// @param rx UartRx_t container for serial data received
void parse_rx_buffer(UartRx_t * rx)
{
	uint8_t i = 0;
	
	while((rx->ind_procd != rx->ind_recd) && (i < UART_RX_PTR_ARRAY_LEN))
	{
		CmdString_t cs;
		flatten_circ_buffer(rx, &cs);
		(void) command_handler(&cs);

		i++;
	}
}

/// @brief Parses the circular buffer in the UartRx_t container and saves in a fixed-width char array
/// @param rx UartRx_t container for serial data received
/// @param buf Fixed width char array where the flattened buffer is saved
/// @return length of the command string (not including null bytes)
/// @note Fixed width buffer is UART_RX_MAX_CMD_LEN bytes
uint16_t flatten_circ_buffer(UartRx_t * rx, CmdString_t * cs)
{
	uint16_t newbuf_ind = 0;
	uint8_t * iter = rx->ptr[rx->ind_procd]; // Set the iterator
	
	uint16_t next_ind = uart_rx_increment_procd(rx);

	// If the pointer is greater than the next pointer, looping back is required
	// so we copy the command in two stages
	if(iter > rx->ptr[next_ind])
	{
		// Copy to end of the array
		while((iter < &(rx->buffer[UART_RX_BUFFER_SIZE])) && (newbuf_ind < UART_RX_MAX_CMD_LEN))
		{
			cs->buffer[newbuf_ind] = * iter;
			iter++;
			newbuf_ind++;
		}
		// Loop back to beginning
		iter = rx->buffer;
	}

	// Copy up to next pointer
	while((iter != rx->ptr[next_ind]) && (newbuf_ind < UART_RX_MAX_CMD_LEN))
	{
		cs->buffer[newbuf_ind] = * iter;
		iter++;
		newbuf_ind++;
	}

	// Zero out rest of array
	for(uint16_t i = newbuf_ind; i < UART_RX_MAX_CMD_LEN; ++i) cs->buffer[i] = 0;

	// Return length of the command
	return newbuf_ind;
}

void serial_print(const char * str)
{
	char * end = (char *)str;
	for(; end-str != SERIAL_IO_MAX_RESPONSE_LEN && *end != 0; ++end)

	USART3DisableDMATx();
	sendDataBlocking((char *)str, (uint8_t) (end - str));
	
	USART3EnableDMATx();
}
