#ifndef DMA_H
#define DMA_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"


/* DMA CHANNEL DESCRIPTION 
	*
	*	CH0: SPI2
	*
	*	CH1: OCTOSPI1
	*		- Trigger: falling edge of EXTI0
	*		- Request: OCTOSPI1
	*		- Source DR: OCTOSPI1->DR
	*	
	*	CH2: I2C1
	*	 
	*/


struct DMA_LLI{
	uint32_t CTR1, CTR2, CBR1, CSAR, CDAR, CLLR;
};

struct DMA_LLI2D{
	uint32_t CTR1, CTR2, CBR1, CSAR, CDAR, CTR3, CBR2, CLLR;
};

extern uint16_t blocks_per_cycle;
extern uint32_t ch3_cllr0;


#define DMA_CFG(_CHNUM) void DMA_CH##_CHNUM##_Config(uint32_t srcAddr, uint32_t destAddr, uint16_t len);

DMA_CFG(0)	
DMA_CFG(1)	
DMA_CFG(2)	
DMA_CFG(3)	
DMA_CFG(4)	
DMA_CFG(5)	
DMA_CFG(6)	
DMA_CFG(12)	
	
#undef DMA_CFG

#define DMA_SETSRC(_CHNUM) void DMA_CH##_CHNUM##_SetSource(uint32_t srcAddr);

DMA_SETSRC(0)	
DMA_SETSRC(1)	
DMA_SETSRC(2)	
DMA_SETSRC(3)	
DMA_SETSRC(4)	
DMA_SETSRC(5)	
DMA_SETSRC(6)	
DMA_SETSRC(12)	
	
#undef DMA_SETSRC

#define DMA_SETDST(_CHNUM) void DMA_CH##_CHNUM##_SetDest(uint32_t destAddr);

DMA_SETDST(0)	
DMA_SETDST(1)	
DMA_SETDST(2)	
DMA_SETDST(3)	
DMA_SETDST(4)	
DMA_SETDST(5)	
DMA_SETDST(6)	
DMA_SETDST(12)	
	
#undef DMA_SETDST

#define DMA_ENABLE(_CHNUM) void DMA_CH##_CHNUM##_Enable();

DMA_ENABLE(0)	
DMA_ENABLE(1)	
DMA_ENABLE(2)	
DMA_ENABLE(3)	
DMA_ENABLE(4)	
DMA_ENABLE(5)	
DMA_ENABLE(6)	
DMA_ENABLE(12)	
	
#undef DMA_ENABLE

void DMA_CH0_Init(void);
void DMA_CH1_Init(void);
void DMA_CH2_Init(void);
void DMA_CH2_Set_Data_Len(uint8_t len);
void DMA_CH4_Init(void);
void DMA_CH5_Init(void);
void DMA_CH12_Init(void);


#endif
