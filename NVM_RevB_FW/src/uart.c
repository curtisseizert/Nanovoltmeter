
#include "stdio.h"
#include "uart.h"
#include "dma.h"


void UART4Init(void)
{


	// Configure GPIO pins
	gpioInitPin(UART4_RX_PORT, UART4_RX_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_FAST, GPIO_NO_PUPD);
	gpioInitPin(UART4_TX_PORT, UART4_TX_PIN, GPIO_AF, GPIO_PUSH_PULL, GPIO_SPEED_FAST, GPIO_NO_PUPD);
	
	// Configure GPIO alternate function registers
	gpioSetAF(UART4_RX_PORT, UART4_RX_PIN, UART4_RX_AF);
	gpioSetAF(UART4_TX_PORT, UART4_TX_PIN, UART4_TX_AF);
	
	// Configure UART
	UART4->CR1 |= USART_CR1_CMIE | USART_CR1_FIFOEN;				// Enable character match interrupt
	UART4->CR2 |= (0x0A << USART_CR2_ADD_Pos);	// Newline "\n" for character match interrupt
	UART4->CR3 |= USART_CR3_DMAT | USART_CR3_DMAR; // Enable DMA
	
	UART4->BRR = SYS_FREQ/UART4_BAUD; // Baud rate of 1.5M, PCLK1 at 48 MHz

	// Configure DMA
	DMA_CH2_Init();	// DMA channel for TX
	DMA_CH4_Init();	// DMA channel for RX
	
	DMA_CH2_Config((uint32_t) &uartTxBuf, (uint32_t) &UART4->TDR, UART_TX_BUFFER_SIZE);
	DMA_CH4_Config((uint32_t) &UART4->RDR, (uint32_t) &uartRxBuf, UART_RX_BUFFER_SIZE);

	
	DMA_CH4_Enable();
	
	// Enable TX and RX
	UART4->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
	UART4->ICR |= USART_ICR_TCCF;
}

void UART4DisableDMATx(void)
{
	UART4->CR3 &= ~(USART_CR3_DMAT);
}

void UART4EnableDMATx(void)
{
	UART4->CR3 |= USART_CR3_DMAT;
}

void sendData(char * buf, uint8_t len)
{
	DMA_CH2_Config((uint32_t) &uartTxBuf, (uint32_t) &UART4->TDR, len);
	
	DMA_CH2_Enable();
}

void sendDataBlocking(char * buf, uint8_t len)
{
	for(uint8_t i = 0; i < len; i++){
		UART4->TDR = buf[i];
		while(!(UART4->ISR & USART_ISR_TC));
	}
}
