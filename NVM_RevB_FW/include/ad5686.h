	
	/*	Basic driver for AD5686 in NVM Rev B
	*
	*
	*/

#ifndef AD5686_H
#define AD5686_H

#include "stdint.h"

/* Note: Command defines are aligned with the first byte of the transfer */

	/* COMMAND DEFINES */
#define AD5686_WRITE_DAC			0x01 << 4
#define AD5686_UPDATE_DAC			0x02 << 4
#define AD5686_WRITE_UPDATE		0x03 << 4
#define AD5686_TOGGLE_POWER		0x04 << 4
#define AD5686_NLDAC_MASK_REG	0x05 << 4
#define AD5686_SW_RESET				0x06 << 4
#define AD5686_DCEN						0x08 << 4		// Daisy chain enable
#define AD5686_READBACK				0x09 << 4
#define AD5686_NO_OP					0x0F << 4

	/* ADDRESS DEFINES */
#define AD5686_DAC_A					(1U << 0)
#define AD5686_DAC_B					(1U << 1)
#define AD5686_DAC_C					(1U << 2)
#define AD5686_DAC_D					(1U << 3)


	/* OUTPUT DEFINES */
#define MOD1_HI_DAC						(1U << 0)	// Output A
#define V_OS_DAC							(1U << 1)	// Output B
#define MOD2_HI_DAC						(1U << 2)	// Output C
#define MOD_LO_DAC						(1U << 3)	// Output D

	/* REPEAT USE DEFINES */
#define AD5686_WRT_UP_DAC_A		(AD5686_WRITE_UPDATE | AD5686_DAC_A)
#define AD5686_WRT_UP_DAC_B		(AD5686_WRITE_UPDATE | AD5686_DAC_B)
#define AD5686_WRT_UP_DAC_C		(AD5686_WRITE_UPDATE | AD5686_DAC_C)
#define AD5686_WRT_UP_DAC_D		(AD5686_WRITE_UPDATE | AD5686_DAC_D)

	/* DEFAULT DAC OUTPUTS */
#define MOD1_HI_DEFAULT				65535U	// 2.50V
#define MOD2_HI_DEFAULT				65535U	// 2.50V
#define V_OS_DEFAULT					0x4B80
#define MOD_LO_DEFAULT				4800U


uint16_t AD5686_WriteDAC(uint8_t addr, uint16_t code);
uint16_t AD5686_WriteDACDMA(uint8_t addr, uint16_t code);

void AD5686_SetDefaultOutputs(void);

#endif
