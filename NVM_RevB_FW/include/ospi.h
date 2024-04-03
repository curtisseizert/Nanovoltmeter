#ifndef OCTOSPI_H
#define OCTOSPI_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"
#include "gpio.h"

	/*	OCTOSPI CCR Defines */	
#define OCTOSPI_SKIP_PHASE					0		// No data phase
#define OCTOSPI_ONE_LINE						1U	// Data on one line
#define OCTOSPI_TWO_LINES						2U	// Data on one line
#define OCTOSPI_FOUR_LINES					3U	// Data on one line

#define OCTOSPI_FMODE_IW						0		// Indirect write mode
#define OCTOSPI_FMODE_IR						1U	// Indirect read mode
#define OCTOSPI_FMODE_AP						2U 	// Automatic polling mode
#define OCTOSPI_FMODE_MM						3U	// Memory mapped mode

#define OCTOSPI_ADSIZE_8_BIT				0		// 8-bit address
#define OCTOSPI_ADSIZE_16_BIT				1U 	// 16-bit address
#define OCTOSPI_ADSIZE_24_BIT				2U	// 24-bit address
#define OCTOSPI_ADSIZE_32_BIT				3U	// 32-bit address



/*******************************************
	*				PROJECT-SPECIFIC DEFINES				*
	******************************************/



	/*	OCTOSPI CR Register Settings 	*/
#define OCTOSPI_MTYP			 					2U 	// Standard Memory Type
#define OCTOSPI_PRESCALER 					0U 	// Prescaler of 2
#define OCTOSPI_PMM									0		// Polling match mode
#define OCTOSPI_APMS								0		// Automatic poll mode stop
#define OCTOSPI_TOIE								0		// Timeout interrupt enable
#define	OCTOSPI_SMIE								0		// Status match interrupt enable
#define	OCTOSPI_FTIE								0		// FIFO Threshold interrupt enable
#define	OCTOSPI_TCIE								0		// Transfer complete interrupt enable
#define	OCTOSPI_TEIE								0		// Transfer error interrupt enable
#define OCTOSPI_FIFO_THRESHOLD 			3U 	// FIFO Threshold of 4
#define	OCTOSPI_FSEL								0		// Flash memory selection
#define	OCTOSPI_DFM									0		// Dual flash mode
#define OCTOSPI_SSHIFT							0		// Sample shift
#define OCTOSPI_TCEN								0		// Timeout counter enable
#define	OCTOSPI_DMAEN								1U	// DMA enable
#define	OCTOSPI_ABORT								0		// Abort request

	/*	OCTOSPI DCR Register Settings */
#define OCTOSPI_FSIZE								0		// Flash memory size
#define OCTOSPI_CSHT								0		// Chip select high time
#define	OCTOSPI_CKMODE							0		// Clock mode

	/*	OCTOSPI DLR Register Settings */
#define OCTOSPI_DATA_SIZE						3U 	// Data size of 4

	/* OCTOSPI CCR Register Settings */
	/* Valid for indirect read */
#define OCTOSPI_DDRM								0		// DDR Mode
#define OCTOSPI_DHHC								0		// DDR Hold
#define OCTOSPI_SIOO								0		// Send instruction only once
#define OCTOSPI_FMODE								OCTOSPI_FMODE_IR	// Functional mode
#define OCTOSPI_DMODE								3U	// Data mode
#define OCTOSPI_DCYC								0		// Number of dummy cycles
#define OCTOSPI_ABSIZE							0		// Alternate bytes size
#define OCTOSPI_ABMODE							OCTOSPI_SKIP_PHASE // Alternate bytes mode
#define OCTOSPI_ADSIZE							OCTOSPI_ADSIZE_8_BIT // Address size
#define OCTOSPI_ADMODE							OCTOSPI_SKIP_PHASE // Address mode
#define OCTOSPI_IMODE								OCTOSPI_SKIP_PHASE // Instruction mode


	/* OCTOSPI PIN DEFINES */
#define OCTOSPI_CLK_PORT						GPIO_PORT_A
#define OCTOSPI_CLK_PIN							GPIO_PIN_3
#define OCTOSPI_NCS_PORT						GPIO_PORT_A
#define OCTOSPI_NCS_PIN							GPIO_PIN_2
#define OCTOSPI_IO4_PORT						GPIO_PORT_C
#define OCTOSPI_IO4_PIN							GPIO_PIN_1
#define OCTOSPI_IO5_PORT						GPIO_PORT_C
#define OCTOSPI_IO5_PIN							GPIO_PIN_2
#define OCTOSPI_IO6_PORT						GPIO_PORT_C
#define OCTOSPI_IO6_PIN							GPIO_PIN_3
#define OCTOSPI_IO7_PORT						GPIO_PORT_C
#define OCTOSPI_IO7_PIN							GPIO_PIN_0



void OCTOSPIInit(void);

void OCTOSPIEnable(void);
void OCTOSPIDisable(void);

void makeNCSgpio(void);
void retakeNCS(void);

void OCTOSPIDMAInit(void);
void OCTOSPIDMAConfig(uint32_t srcAdd, uint32_t destAdd, uint16_t dsize);

void OCTOSPIEnableDMA(void);
void OCTOSPIDisableDMA(void);

void OCTOSPISetDataLength(uint32_t len);

uint32_t OCTOSPIReadOneLine(void);
void OCTOSPIReadOneLineDMA(void);

uint32_t OCTOSPIReadFourLine(void);
void OCTOSPIReadFourLineDMA(void);

uint32_t OCTOSPIRead(void);

uint32_t OCTOSPIReadFIFO(void);




#endif 
