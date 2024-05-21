
/* TMP117 Driver for NVM REV B */

#include "tmp117.h"
#include "i2c.h"

void tmp117_init(TMP117_t * tmp117)
{
	uint8_t cfg_buf[3];
	
		/* Populate buffer for default configuration */
	cfg_buf[0] = (uint8_t) TMP117_REG_CONFIG;
	cfg_buf[1] = (uint8_t) (TMP117_DEFAULT_CONFIG & 0xFF);
	cfg_buf[2] = (uint8_t) (TMP117_DEFAULT_CONFIG >> 8);
	
		/* Send configuration data to each TMP117 */
	tmp117->i2c->CR2 |= I2C_CR2_AUTOEND;
	i2c_send_data(tmp117->i2c, tmp117->addr, cfg_buf, 3);
}

void tmp117_send_reg_addr(TMP117_t * tmp117, uint8_t reg)
{
	reg &= 0xFF;
	i2c_send_data(tmp117->i2c, tmp117->addr, &reg, 1);
}

int16_t tmp117_read_register(TMP117_t * tmp117, uint8_t reg)
{
	uint8_t buf[2];
	int16_t code;
	
	reg &= 0x0F;
	
	/*** TRANSMIT STAGE ***/
	tmp117->i2c->CR2 &= ~I2C_CR2_AUTOEND;
	tmp117->i2c->CR2 &= ~(I2C_CR2_SADD_Msk | I2C_CR2_NBYTES_Msk);
	tmp117->i2c->CR2 |= (1U << I2C_CR2_NBYTES_Pos) | ((uint32_t) tmp117->addr << 1);
	
		/* Send data */
	tmp117->i2c->CR2 &= ~I2C_CR2_RD_WRN;
	
		/* Clear transmit register if it is not empty */
	if(!(tmp117->i2c->ISR & I2C_ISR_TXE)) tmp117->i2c->ISR |= I2C_ISR_TXE;
	
		/* Start the transfer */
	tmp117->i2c->TXDR = reg;
	tmp117->i2c->CR2 |= I2C_CR2_START;
	
	while(!(tmp117->i2c->ISR & I2C_ISR_TC));
	
	/*** RECEIVE STAGE ***/
	
			/* Reconfigure ADDR and NBYTES bits */
	tmp117->i2c->CR2 &= ~I2C_CR2_NBYTES_Msk;
	tmp117->i2c->CR2 |= (2U << I2C_CR2_NBYTES_Pos) | I2C_CR2_RD_WRN;
	
		/* Clear receive register */
	buf[0] = (uint8_t) tmp117->i2c->RXDR;
	
		/* Start the transfer */
	tmp117->i2c->CR2 |= I2C_CR2_START;
	
		/* Receive Data */
	for(uint8_t i = 0; i < 2; i++){
		while(!(tmp117->i2c->ISR & I2C_ISR_RXNE));
		buf[i] = (uint8_t) tmp117->i2c->RXDR;
	}
	tmp117->i2c->CR2 |= I2C_CR2_STOP;
	code = (int16_t) (buf[1] | ( buf[0] << 8));	
	tmp117->i2c->ICR |= I2C_ICR_STOPCF;
	
	return code;
}


float tmp117_get_temp(TMP117_t * tmp117)
{
	int16_t code;
	
	code = tmp117_read_register(tmp117, 0x00);
	
	return tmp117_code_to_temperature(code);
}

float tmp117_code_to_temperature(int16_t code)
{
	float ret = code;
	return (float) ret/128;
}


/*
void TMP117nextData(TMP117_Handle_TypeDef * tmp117)
{
	I2C_SetPeripheralAddress(tmp117->i2c, tmp117->addr);
	DMA_CH3_SetDest((uint32_t) &tmp117_data[tmp_index]);
	GPDMA1_Channel3->CCR |= DMA_CCR_EN;
	
	tmp_index++;
	if(tmp_index == 3){
		for(uint8_t i = 0; i < 3; i++){
			temps[i] = TMP117codeToTemperature(tmp117_data[i]);
		}
		tmp_index = 0;
	}
}
*/
/* Stucture of the linked list is four items repeated 3x for each TMP117
	* for data retreival. Blocking transfers can be used for setup where CPU
	* time is not at a premium. The first node in the list (node 0) uses a 
	* software request generated
	*
	*	0. I2C1 config register writes for setting up 1-byte write
	*	1. I2C1 data write of 0x00
	* 2. I2C1 config register writes for setting up 2-byte read
	* 3. I2C1 data read from TMP117 
	*	4-11. Repeat above 2x
	*	
	*/

//struct DMA_LLI DMA_CH3_LLI[13];
//uint8_t TMP117_Zero = 0x00;
//uint32_t I2C_CR2_write[3], I2C_CR2_read[3];
//uint32_t ch3_cllr0;
/*

void TMP117SetupDMA(void)
{
	GPDMA1_Channel3->CLBAR = (uint32_t) &DMA_CH3_LLI[0] & 0xFFFF0000;
	
	GPDMA1_Channel3->CCR |= DMA_CCR_LAP | DMA_CCR_TCIE | (2U << DMA_CCR_PRIO_Pos);
	
	DMA_CH3_LLIinit();
	
	GPDMA1_Channel3->CTR1 = DMA_CH3_LLI[5].CTR1;
	GPDMA1_Channel3->CTR2 = DMA_CH3_LLI[5].CTR2;
	GPDMA1_Channel3->CBR1 = DMA_CH3_LLI[5].CBR1;
	GPDMA1_Channel3->CSAR = DMA_CH3_LLI[5].CSAR;
	GPDMA1_Channel3->CDAR = DMA_CH3_LLI[5].CDAR;
	GPDMA1_Channel3->CLLR = DMA_CH3_LLI[5].CLLR;
	
	I2C1DMAInit();
}
*/
/*
void DMA_CH3_LLIinit(void)
{
		// These general write and read commands are ORed with the 
		// address of the TMP117 to be used at that node in the LLI 
	uint32_t I2C_CR2_write_gen = (1U << I2C_CR2_NBYTES_Pos) | I2C_CR2_START;
	uint32_t I2C_CR2_read_gen = ((2U << I2C_CR2_NBYTES_Pos) | I2C_CR2_RD_WRN | I2C_CR2_START);
	uint32_t LLR_gen = (DMA_CLLR_UT1 | DMA_CLLR_UT2 | DMA_CLLR_UB1 | DMA_CLLR_USA
										| DMA_CLLR_UDA | DMA_CLLR_ULL);
	
	for(uint8_t i = 0; i < 3; i++){
		I2C_CR2_write[i] = (tmp117_addr[i] << 1) | I2C_CR2_write_gen;
		I2C_CR2_read[i] = (tmp117_addr[i] << 1) | I2C_CR2_read_gen;
	}
	
		// Populate LLI members 
	for(uint8_t i = 0; i < 3; i++){
		
			// i + 0  node 
		DMA_CH3_LLI[4*i].CTR1 = (0U << DMA_CTR1_DDW_LOG2_Pos)	// 8-bit word at dest
													| (0U << DMA_CTR1_SDW_LOG2_Pos) // 8-bit word at source
													| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
													| (0U << DMA_CTR1_SBL_1_Pos);	// 1 word burst at src
		DMA_CH3_LLI[4*i].CTR2 = (3U << DMA_CTR2_TCEM_Pos)		// TC at end of LL
													| (14U << DMA_CTR2_REQSEL_Pos) // I2C1 EVC Request
													| DMA_CTR2_DREQ;	 // Destination hardware request
		DMA_CH3_LLI[4*i].CBR1 = 3;
		DMA_CH3_LLI[4*i].CSAR = (uint32_t) &I2C_CR2_write[i];
		DMA_CH3_LLI[4*i].CDAR = (uint32_t) &I2C1->CR2;
		DMA_CH3_LLI[4*i].CLLR = (uint32_t) (((uint32_t) &DMA_CH3_LLI[4*i+1].CTR1 & 0x3FFF) << DMA_CLLR_LA_Pos) | LLR_gen;
		
		
			// i + 1 node 
		DMA_CH3_LLI[4*i+1].CTR1 = (0U << DMA_CTR1_DDW_LOG2_Pos)	// 32-bit word at dest
													| (0U << DMA_CTR1_SDW_LOG2_Pos) // 32-bit word at source
													| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
													| (0U << DMA_CTR1_SBL_1_Pos);	// 1 word burst at src
		DMA_CH3_LLI[4*i+1].CTR2 = (3U << DMA_CTR2_TCEM_Pos)		// TC at end of LL
													| (13U << DMA_CTR2_REQSEL_Pos) // I2C1 TX Request
													| DMA_CTR2_DREQ;	 // Destination hardware request
		DMA_CH3_LLI[4*i+1].CBR1 = 1;
		DMA_CH3_LLI[4*i+1].CSAR = (uint32_t) &TMP117_Zero;
		DMA_CH3_LLI[4*i+1].CDAR = (uint32_t) &I2C1->TXDR;
		DMA_CH3_LLI[4*i+1].CLLR = (uint32_t) (((uint32_t) &DMA_CH3_LLI[4*i+2].CTR1 & 0x3FFF) << DMA_CLLR_LA_Pos) | LLR_gen;
		
		
			// i + 2 node 
		DMA_CH3_LLI[4*i+2].CTR1 = (0U << DMA_CTR1_DDW_LOG2_Pos)	// 32-bit word at dest
													| (0U << DMA_CTR1_SDW_LOG2_Pos) // 32-bit word at source
													| (0U << DMA_CTR1_DBL_1_Pos)		// 1 word burst at dest
													| (0U << DMA_CTR1_SBL_1_Pos);	// 1 word burst at src
		DMA_CH3_LLI[4*i+2].CTR2 = (3U << DMA_CTR2_TCEM_Pos)		// TC at end of LL
													| (14U << DMA_CTR2_REQSEL_Pos) // I2C1 EVC Request
													| DMA_CTR2_DREQ;	 // Destination hardware request
		DMA_CH3_LLI[4*i+2].CBR1 = 3;
		DMA_CH3_LLI[4*i+2].CSAR = (uint32_t) &I2C_CR2_write[i];
		DMA_CH3_LLI[4*i+2].CDAR = (uint32_t) &I2C1->CR2;
		DMA_CH3_LLI[4*i+2].CLLR = (uint32_t) (((uint32_t) &DMA_CH3_LLI[4*i+3].CTR1 & 0x3FFF) << DMA_CLLR_LA_Pos) | LLR_gen;
		
		
			// i + 3 node 
		DMA_CH3_LLI[4*i+3].CTR1 = (1U << DMA_CTR1_DDW_LOG2_Pos)	// 16-bit word at dest
													| (0U << DMA_CTR1_SDW_LOG2_Pos) // 8-bit word at source
													| (1U << DMA_CTR1_DBL_1_Pos)		// 2-byte burst at dest
													| (0U << DMA_CTR1_SBL_1_Pos);	// 1-byte burst at src
		DMA_CH3_LLI[4*i+3].CTR2 = (3U << DMA_CTR2_TCEM_Pos)		// TC at end of LL
													| (12U << DMA_CTR2_REQSEL_Pos);	 // I2C1 RX Request
		DMA_CH3_LLI[4*i+3].CBR1 = 2;
		DMA_CH3_LLI[4*i+3].CSAR = (uint32_t) &I2C1->RXDR; // Source address is I2C1->RXDR
		DMA_CH3_LLI[4*i+3].CDAR = (uint32_t) &tmp117_data[i];
		DMA_CH3_LLI[4*i+3].CLLR = (uint32_t) (((uint32_t) &DMA_CH3_LLI[4*i+4].CTR1 & 0x3FFF) << DMA_CLLR_LA_Pos) | LLR_gen;
	}
	
	DMA_CH3_LLI[0].CTR2 = DMA_CTR2_SWREQ;
	
	DMA_CH3_LLI[12] = DMA_CH3_LLI[0];
	//DMA_CH3_LLI[12].CLLR = 0;
	
	ch3_cllr0 = DMA_CH3_LLI[0].CLLR;

}*/
