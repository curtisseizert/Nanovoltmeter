
#ifndef DMA_H_
#define DMA_H_

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"


	/* DMA Linked-List Containers */
	// Note that only fully defined nodes are supported 
typedef struct 
{
	uint32_t CTR1;
	uint32_t CTR2;
	uint32_t CBR1;
	uint32_t * CSAR;
	uint32_t * CDAR;
	uint32_t CLLR;
}DmaNode_t;

typedef struct 
{
	uint32_t CTR1, CTR2, CBR1, CSAR, CDAR, CTR3, CBR2, CLLR;
}Dma2DNode_t;

extern DmaNode_t dma_ch1_lli[2];
extern DmaNode_t dma_ch2_node;
extern DmaNode_t dma_ch4_node;

extern uint32_t dac_data[2];


	/* DMA Linked-List Convenience Functions*/
void dma_append_node(DmaNode_t * node, const DmaNode_t * next_node);
void dma_set_base_lli_addr(DMA_Channel_TypeDef * dma, const DmaNode_t * node);
void dma_set_next_node(DMA_Channel_TypeDef * dma, const DmaNode_t * node);
void dma_setup_circ_transfer(DMA_Channel_TypeDef * dma, DmaNode_t * node);
void dma_copy_node_to_reg(DMA_Channel_TypeDef * dma, DmaNode_t * node);

void dma_enable_channel(DMA_Channel_TypeDef * dma);
void dma_set_data_bytes(DMA_Channel_TypeDef * dma, uint16_t len);

void DMA_CH0_Init(void);
void DMA_CH1_Init(uint32_t * CSAR);
void DMA_CH2_Init(void);
void DMA_CH4_Init(uint32_t * CDAR);


extern uint16_t blocks_per_cycle;
extern uint32_t ch3_cllr0;

#endif // DMA_H_
