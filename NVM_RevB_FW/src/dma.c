	/* dma.c */

#include "dma.h"
#include "uart.h"

	/** DMA CHANNEL USAGE
	 * 
	 * 	**Note: All non-peripheral addresses must be set at runtime.
	 * 
	 * 	CH0: Reserved for transfers of ADC data without complete SPI automation (due to 
	 * 			use of software NCS)
	 * 
	 *  CH1: SPI2 TX for writes to AD5686
	 * 		-Uses a 2-element linked list with index 0 for routine writes to V_os channel
	 * 			and index 1 for other channel writes dictated by commands received over USART
	 * 		-V_os writes from saved address by starting SPI2, i.e.,
	 * 				uint32_t vos_dac_data;
	 * 				dma_ch1_lli[0].CSAR = &vos_dac_data;
	 * 					// Modify vos_dac_data value
	 * 				spi_start(SPI2);		// Sends current value of vos_dac_data
	 * 		-Added values sent as follows:
	 * 				uint32_t new_dac_data;
	 * 				dma_ch1_lli[1].CSAR = &new_dac_data;
	 * 					// Modify new_dac_data value
	 * 				dma_set_next_node(GPDMA1_Channel1, dma_ch1_lli[1]);
	 * 				spi_start(SPI2);		// Sends value from previous node
	 * 					// Wait for transaction to complete
	 * 				spi_start(SPI2);		// Sends new value
	 * 
	 * 	CH2: USART3 TX for sending serial data as ASCII character strings
	 * 		-Uses a single-element linked list for resetting the DMA channel after each transfer
	 * 		-Transfer setup as follows:
	 * 				uint8_t tx_buffer[UART_TX_BUFFER_LEN];
	 * 					// Initialize and enable USART3
	 * 				uint16_t len = sprintf(tx_buffer, "...", ...);
	 * 				dma_set_data_bytes(GPDMA1_Channel2, len);
	 * 				dma_enable_channel(GPDMA1_Channel2);
	 * 
	 * 	CH3: Reserved for the PITA of automating I2C transactions via DMA
	 * 
	 * 	CH4: USART3 RX for receiving serial data as ASCII character strings
	 * 		-Uses a single-element linked list for circular buffering
	 * 		-Meant to work in conjunction with the UartRx_t type
	 * 		-See serial_io.h and serial_io.c for more implementation details
	 * 
	 **/ 		



	

//static uint32_t DMAZero32 = 0;

uint32_t dac_data[2];

DmaNode_t dma_ch1_lli[2] = 
{
	{
	.CTR1 = (2U << DMA_CTR1_DDW_LOG2_Pos)
			| (2U << DMA_CTR1_SDW_LOG2_Pos) // 32-bit word
			| (0U << DMA_CTR1_DBL_1_Pos)	// 1 word burst at dest
			| (0U << DMA_CTR1_SBL_1_Pos),	// 1 word burst at src
	.CTR2 = (9U << DMA_CTR2_REQSEL_Pos)	 // SPI2 TX Request
			| DMA_CTR2_DREQ,
	.CBR1 = 4U,
	.CDAR = (uint32_t *) &SPI2->TXDR,
	.CLLR = DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | DMA_CLLR_UDA | DMA_CLLR_ULL
	},
	{
	.CTR1 = (2U << DMA_CTR1_DDW_LOG2_Pos)
			| (2U << DMA_CTR1_SDW_LOG2_Pos) // 32-bit word
			| (0U << DMA_CTR1_DBL_1_Pos)	// 1 word burst at dest
			| (0U << DMA_CTR1_SBL_1_Pos),	// 1 word burst at src
	.CTR2 = (9U << DMA_CTR2_REQSEL_Pos)	 // SPI2 TX Request
			| DMA_CTR2_DREQ,
	.CBR1 = 4U,
	.CDAR = (uint32_t *) &SPI2->TXDR,
	.CLLR = DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | DMA_CLLR_UDA | DMA_CLLR_ULL
	}
};

DmaNode_t dma_ch4_node = 
{
	.CTR1 = DMA_CTR1_DINC					// Increment dest addr
		| (0U << DMA_CTR1_DDW_LOG2_Pos)
		| (0U << DMA_CTR1_SDW_LOG2_Pos) 	// 8-bit word
		| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
		| (0U << DMA_CTR1_SBL_1_Pos),		// 1 word burst at src
	
	.CTR2 = (28U << DMA_CTR2_REQSEL_Pos),	// USART3 RX Request
	.CSAR = (uint32_t *) &USART3->RDR, 		// Source ADDRESS IS UART4 RDR
	
	.CBR1 = UART_RX_BUFFER_SIZE,
	.CLLR = DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | DMA_CLLR_UDA | DMA_CLLR_ULL
};

DmaNode_t dma_ch2_node = 
{
	.CTR1 = DMA_CTR1_SINC					// Increment source addr
			| (0U << DMA_CTR1_DDW_LOG2_Pos)
			| (0U << DMA_CTR1_SDW_LOG2_Pos) // 8-bit word
			| (0U << DMA_CTR1_DBL_1_Pos)	// 1-byte burst at dest
			| (31U << DMA_CTR1_SBL_1_Pos),	// 32-byte burst at src
	
	.CTR2 = (1U << DMA_CTR2_TRIGPOL_Pos) 	// Rising edge trigger
		|	(29U << DMA_CTR2_REQSEL_Pos)	// USART3 TX Request
		| DMA_CTR2_DREQ,					// Destination Request
	.CDAR = (uint32_t *) &USART3->TDR,
	.CSAR = (uint32_t *) &uart_tx_buffer,
	.CLLR = (uint32_t) (DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA 
		| DMA_CLLR_UDA | DMA_CLLR_ULL)
};

void dma_append_node(DmaNode_t * node, const DmaNode_t * new_node)
{
	node->CLLR &= 0xFFFF0000;
	node->CLLR |= ((uint32_t) new_node) & 0x0000FFFF;
}

void dma_set_base_lli_addr(DMA_Channel_TypeDef * dma, const DmaNode_t * node)
{
	dma->CLBAR = ((uint32_t) node ) & 0xFFFF0000;
}

void dma_set_next_node(DMA_Channel_TypeDef * dma, const DmaNode_t * node)
{
	dma->CLLR = DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA | DMA_CLLR_UDA | DMA_CLLR_ULL;
	dma->CLLR |= ((uint32_t) node ) & 0x0000FFFF;
}

void dma_setup_circ_transfer(DMA_Channel_TypeDef * dma, DmaNode_t * node)
{
	dma_append_node(node, node);
	dma_set_base_lli_addr(dma, node);
	dma_copy_node_to_reg(dma, node);
}

void dma_enable_channel(DMA_Channel_TypeDef * dma)
{
	dma->CCR |= DMA_CCR_EN;
}

void dma_set_data_bytes(DMA_Channel_TypeDef * dma, uint16_t len)
{
	dma->CBR1 &= ~DMA_CBR1_BNDT_Msk;
	len &= 0x3F;
	dma->CBR1 |= len;
}

void dma_copy_node_to_reg(DMA_Channel_TypeDef * dma, DmaNode_t * node)
{
	dma->CTR1 = node->CTR1;
	dma->CTR2 = node->CTR2;
	dma->CBR1 = node->CBR1;
	dma->CSAR = (uint32_t) node->CSAR;
	dma->CDAR = (uint32_t) node->CDAR;
	dma->CLLR = node->CLLR;
}


void DMA_CH0_Init(void)
{
	GPDMA1_Channel0->CTR1 |= DMA_CTR1_DINC		// Increment source addr
						| (2U << DMA_CTR1_DDW_LOG2_Pos)
						| (2U << DMA_CTR1_SDW_LOG2_Pos) // 32-bit word
						| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
						| (0U << DMA_CTR1_SBL_1_Pos);		// 1 word burst at src
	
	GPDMA1_Channel0->CTR2 |= (6U << DMA_CTR2_REQSEL_Pos);	 // SPI1 RX Request

	GPDMA1_Channel0->CCR |= DMA_CCR_HTIE | DMA_CCR_TCIE 
						|	(3U << DMA_CCR_PRIO_Pos); 		// high priority
}

void DMA_CH1_Init(uint32_t * CSAR)
{
	GPDMA1_Channel1->CCR |= (1U << DMA_CCR_PRIO_Pos); // low priority, mid weight

	dma_ch1_lli[0].CSAR = (uint32_t *) CSAR;
	dma_ch1_lli[1].CSAR = (uint32_t *) CSAR;
	dma_append_node(&dma_ch1_lli[1], &dma_ch1_lli[0]);
	dma_setup_circ_transfer(GPDMA1_Channel1, &dma_ch1_lli[0]);
}


void DMA_CH2_Init(void)
{
	GPDMA1_Channel2->CCR |= DMA_CCR_LSM				// Execute current state, update LLR
						| (1U << DMA_CCR_PRIO_Pos); // low priority, mid weight

	dma_setup_circ_transfer(GPDMA1_Channel2, &dma_ch2_node);
}

void DMA_CH4_Init(uint32_t * CDAR)
{
	dma_ch4_node.CDAR = CDAR;
	GPDMA1_Channel4->CCR |= (1U << DMA_CCR_PRIO_Pos); // low priority, mid weight

	dma_setup_circ_transfer(GPDMA1_Channel4, &dma_ch4_node);

}
