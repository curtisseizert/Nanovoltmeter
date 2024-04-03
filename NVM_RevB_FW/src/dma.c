
#include "dma.h"

	/* DMA CH0 is for SPI1 reads from ADC */
	
#define DMA_CFG(_CHNUM) void DMA_CH##_CHNUM##_Config(uint32_t srcAddr, uint32_t destAddr, uint16_t len) \
{ GPDMA1_Channel##_CHNUM->CSAR = srcAddr; \
	GPDMA1_Channel##_CHNUM->CDAR = destAddr; \
	GPDMA1_Channel##_CHNUM->CBR1 = len; }


DMA_CFG(0)	
DMA_CFG(1)	
DMA_CFG(2)	
DMA_CFG(3)	
DMA_CFG(4)	
DMA_CFG(5)	
DMA_CFG(6)	
DMA_CFG(12)
	
#undef DMA_CFG
	
	#define DMA_SETSRC(_CHNUM) void DMA_CH##_CHNUM##_SetSource(uint32_t srcAddr){ GPDMA1_Channel##_CHNUM->CSAR = srcAddr;}

DMA_SETSRC(0)	
DMA_SETSRC(1)	
DMA_SETSRC(2)	
DMA_SETSRC(3)	
DMA_SETSRC(4)	
DMA_SETSRC(5)	
DMA_SETSRC(6)	
DMA_SETSRC(12)	
	
#undef DMA_SETSRC

#define DMA_SETDST(_CHNUM) void DMA_CH##_CHNUM##_SetDest(uint32_t destAddr){GPDMA1_Channel##_CHNUM->CDAR = destAddr;}

DMA_SETDST(0)	
DMA_SETDST(1)	
DMA_SETDST(2)	
DMA_SETDST(3)	
DMA_SETDST(4)	
DMA_SETDST(5)	
DMA_SETDST(6)	
DMA_SETDST(12)	
	
#undef DMA_SETDST


#define DMA_ENABLE(_CHNUM) void DMA_CH##_CHNUM##_Enable(){GPDMA1_Channel##_CHNUM->CCR |= DMA_CCR_EN;}

DMA_ENABLE(0)	
DMA_ENABLE(1)	
DMA_ENABLE(2)	
DMA_ENABLE(3)	
DMA_ENABLE(4)	
DMA_ENABLE(5)	
DMA_ENABLE(6)	
DMA_ENABLE(12)	
	
#undef DMA_ENABLE


static uint32_t DMAZero32 = 0;

	
void DMA_CH0_Init(void)
{
	GPDMA1_Channel0->CTR1 |= DMA_CTR1_DINC								// Increment source addr
												| (2U << DMA_CTR1_DDW_LOG2_Pos)
												| (2U << DMA_CTR1_SDW_LOG2_Pos) // 32-bit word
												| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
												| (0U << DMA_CTR1_SBL_1_Pos);	// 1 word burst at src
	
	GPDMA1_Channel0->CTR2 |= (6U << DMA_CTR2_REQSEL_Pos);	 // SPI1 RX Request

	GPDMA1_Channel0->CCR |= DMA_CCR_HTIE | DMA_CCR_TCIE 
													|	(3U << DMA_CCR_PRIO_Pos); // high priority
}

void DMA_CH1_Init(void)
{
	GPDMA1_Channel1->CTR1 |= DMA_CTR1_SINC								// Increment source addr
												| (2U << DMA_CTR1_DDW_LOG2_Pos)
												| (2U << DMA_CTR1_SDW_LOG2_Pos) // 32-bit word
												| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
												| (0U << DMA_CTR1_SBL_1_Pos);	// 1 word burst at src
	
	GPDMA1_Channel1->CTR2 |= (9U << DMA_CTR2_REQSEL_Pos)	 // SPI2 TX Request
												| DMA_CTR2_DREQ;
	
	GPDMA1_Channel1->CCR |= DMA_CCR_TCIE
												| (1U << DMA_CCR_PRIO_Pos); // low priority, mid weight
}


void DMA_CH2_Init(void)
{
	GPDMA1_Channel2->CTR1 |= DMA_CTR1_SINC								// Increment source addr
												| (0U << DMA_CTR1_DDW_LOG2_Pos)
												| (0U << DMA_CTR1_SDW_LOG2_Pos) // 8-bit word
												| (0U << DMA_CTR1_DBL_1_Pos)		// 32-byte burst at dest
												| (31U << DMA_CTR1_SBL_1_Pos);	// 32-byte burst at src
	
	GPDMA1_Channel2->CTR2 |= (1U << DMA_CTR2_TRIGPOL_Pos) // Rising edge trigger
												//| (43U << DMA_CTR2_TRIGSEL_Pos) // TIM15 UE trigger
												//| (3U << DMA_CTR2_TRIGM) 				// Programmed burst level
												|	(31U << DMA_CTR2_REQSEL_Pos)	 // UART4 TX Request
												| DMA_CTR2_DREQ;
	
		
	GPDMA1_Channel2->CCR |= DMA_CCR_TCIE
												| (1U << DMA_CCR_PRIO_Pos); // low priority, mid weight

}



void DMA_CH2_Set_Data_Len(uint8_t len)
{
	/* Format length bits */
	//len &= 0x3F;
	
	GPDMA1_Channel2->CBR1 &= ~DMA_CBR1_BNDT_Msk;
	GPDMA1_Channel2->CBR1 |= len;
	
	//len--;
	
	//GPDMA1_Channel2->CTR1 &= ~(DMA_CTR1_SBL_1_Msk);
	//GPDMA1_Channel2->CTR1 |= (len << DMA_CTR1_SBL_1_Pos);
	

}

void DMA_CH4_Init(void)
{
	GPDMA1_Channel4->CTR1 |= DMA_CTR1_DINC								// Increment dest addr
												| (0U << DMA_CTR1_DDW_LOG2_Pos)
												| (0U << DMA_CTR1_SDW_LOG2_Pos) // 8-bit word
												| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
												| (0U << DMA_CTR1_SBL_1_Pos);	// 1 word burst at src
	
	GPDMA1_Channel4->CTR2 |= (30U << DMA_CTR2_REQSEL_Pos);	 // UART4 RX Request

	
	GPDMA1_Channel4->CSAR = (uint32_t) &UART4->RDR; // Source ADDRESS IS UART4 RDR
	
	GPDMA1_Channel4->CCR |= DMA_CCR_TCIE
												| (1U << DMA_CCR_PRIO_Pos); // low priority, mid weight

}

void DMA_CH5_Init(void)
{
	GPDMA1_Channel5->CTR1 |= (2U << DMA_CTR1_DDW_LOG2_Pos)
												| (2U << DMA_CTR1_SDW_LOG2_Pos) // 8-bit word
												| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
												| (0U << DMA_CTR1_SBL_1_Pos);	// 1 word burst at src
	
	GPDMA1_Channel4->CTR2 |= (7U << DMA_CTR2_REQSEL_Pos);	 // SPI1_TX request

	
	GPDMA1_Channel4->CCR |= (3U << DMA_CCR_PRIO_Pos); // high priority
	
	DMA_CH5_Config((uint32_t) &DMAZero32, (uint32_t) &SPI1->TXDR, 4);

}

void DMA_CH12_Init(void)
{
	GPDMA1_Channel12->CTR1 |= DMA_CTR1_SINC | DMA_CTR1_DINC// Increment source addr
												| (0U << DMA_CTR1_DDW_LOG2_Pos)
												| (0U << DMA_CTR1_SDW_LOG2_Pos) // 8-bit word
												| (31U << DMA_CTR1_DBL_1_Pos)		// 32-byte burst at dest
												| (31U << DMA_CTR1_SBL_1_Pos);	// 32-byte burst at src
	
	GPDMA1_Channel12->CTR2 |= DMA_CTR2_SWREQ;
	
	GPDMA1_Channel12->CCR |= DMA_CCR_TCIE
												| (1U << DMA_CCR_PRIO_Pos); // low priority, mid weight
	GPDMA1_Channel12->CBR1 |= 128;
}
