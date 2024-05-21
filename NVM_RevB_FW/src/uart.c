
#include "uart.h"
#include "dma.h"



void USART3DisableDMATx(void)
{
	USART3->CR3 &= ~(USART_CR3_DMAT);
}

void USART3EnableDMATx(void)
{
	USART3->CR3 |= USART_CR3_DMAT;
}

void sendDataBlocking(char * buf, uint16_t len)
{
	for(uint8_t i = 0; i < len; i++){
		USART3->TDR = buf[i];
		while(!(USART3->ISR & USART_ISR_TC));
	}
}
