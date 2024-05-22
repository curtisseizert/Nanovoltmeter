	
	/* DRIVER HEADER FOR AD403x in NVM */
	
#ifndef AD403X_H_
#define AD403X_H_

#include <stdint.h>

#include "stm32u575xx.h"
#include "stm32u5xx.h"
#include "gpio.h"


	/* REGISTER ADDRESSES */
#define AD403X_REG_INTERFACE_CONFIG_A			0x00
#define AD403X_REG_INTERFACE_CONFIG_B			0x01
#define AD403X_REG_DEVICE_CONFIG				0x02
#define AD403X_REG_CHIP_TYPE					0x03
#define AD403X_REG_PRODUCT_ID_L					0x04
#define AD403X_REG_PRODUCT_ID_H					0x05
#define AD403X_REG_CHIP_GRADE					0x06
#define AD403X_REG_SCRATCH_PAD					0x0A
#define AD403X_REG_SPI_REVISION					0x0B
#define AD403X_REG_VENDOR_L						0x0C
#define AD403X_REG_VENDOR_H						0x0D
#define AD403X_REG_STREAM_MODE					0x0E
#define AD403X_REG_EXIT_CFG_MODE				0x14
#define AD403X_REG_AVG							0x15
#define AD403X_REG_OFFSET_BASE					0x16
#define AD403X_REG_OFFSET_LB					0x16
#define AD403X_REG_OFFSET_MB					0x17
#define AD403X_REG_OFFSET_HB					0x18
#define AD403X_REG_GAIN_LB						0x1C
#define AD403X_REG_GAIN_HB						0x1D
#define AD403X_REG_MODES						0x20
#define AD403X_REG_OSCILATOR					0x21
#define AD403X_REG_OUTPUT_DRVR					0x22
#define AD403X_REG_PAT0							0x23
#define AD403X_REG_PAT1							0x24
#define AD403X_REG_PAT2							0x25
#define AD403X_REG_PAT3							0x26
#define AD403X_REG_DIG_DIAG						0x34
#define AD403X_REG_DIG_ERR						0x35


/* INTERFACE_CONFIG_A */
#define AD403X_CFG_SW_RESET						((1U << 7) | 1U )
#define AD403X_CFG_SDO_ENABLE					(1U << 4)

/* MODES */
#define AD403X_SW_RESET_MSK						((1U << 7) | 1U )
#define AD403X_LANE_MODE_MSK					((1U << 7) | (1U << 6))
#define AD403X_CLK_MODE_MSK						((1U << 5) | (1U << 4))
#define AD403X_DDR_MODE_MSK						(1U << 3)
#define AD403X_SDR_MODE							0x00
#define AD403X_DDR_MODE							(1U <<3)
#define AD403X_OUT_DATA_MODE_MSK				((1U <<2) | (1U <<1) | (1U <<0))
#define AD403X_24_DIFF							0x00
#define AD403X_16_DIFF_8_COM					0x01
#define AD403X_24_DIFF_8_COM					0x02
#define AD403X_30_AVERAGED_DIFF					0x03
#define AD403X_32_PATTERN						0x04

/* EXIT_CFG_MD */
#define AD403X_EXIT_CFG_MODE					0x01

/* OFFSET */
#define AD403X_OFFSET_0							0x00
#define AD403X_OFFSET_1							0x01
#define AD403X_OFFSET_2							0x02

/* GAIN */
#define AD403X_GAIN_LSB							0x00
#define AD403X_GAIN_MSB							0x01

/* LANE MODE */
#define AD403X_ONE_LANE							0x00
#define AD403X_TWO_LANES						(1U << 6)
#define AD403X_FOUR_LANES						(1U << 7)

/* CLK MODE */
#define AD403X_SPI_COMPATIBLE_MODE				0x00
#define AD403X_ECHO_CLOCK_MODE					(1U << 4)
#define AD403X_CLOCK_MASTER_MODE				(1U << 5)

/* POWER MODE */
#define AD403X_NORMAL_MODE 						0x00
#define AD403X_LOW_POWER_MODE					((1U << 1) | (1U << 0))

/* AVG */
#define AD403X_AVG_FILTER_RESET					(1U << 7)
#define AD403X_CONFIG_TIMING					0x2000
#define AD403X_REG_READ_DUMMY					0x00
#define AD403X_REG_WRITE        				0x00
#define AD403X_REG_READ		    				(1U << 7)
#define AD403X_REG_CHAN_OFFSET(ch, pos)			(AD403X_REG_OFFSET_BASE + (3 * ch) + pos)
#define AD403X_REG_CHAN_GAIN(ch, pos)			(AD403X_REG_GAIN_BASE + (2 * ch) + pos)

/* IO */
#define AD403X_DRIVER_STRENGTH_MASK				(1U << 0)
#define AD403X_NORMAL_OUTPUT_STRENGTH			0x00
#define AD403X_DOUBLE_OUTPUT_STRENGTH			(1U << 1)

/* OUT_DATA_PAT */
#define AD403X_OUT_DATA_PAT						0x5A5A0F0F
#define AD403X_TRIGGER_PULSE_WIDTH_NS			0x0A
#define AD403X_GAIN_MAX_VAL_SCALED				19997

#define REG_ACCESS_DATA_SIZE					(24U - 1)
#define REG_ACCESS_CODE								((uint32_t) 0xBFFF00)

/* NVM-SPECIFIC DEFINES */
#define AD403X_DEFAULT_MODE						(AD403X_ONE_LANE | AD403X_30_AVERAGED_DIFF)


typedef struct{
	SPI_TypeDef * spi;
	Pin_t * ncs_pin;
	Pin_t * nreset_pin;

}AD403X_t;

void ad403x_reset(const AD403X_t * adc);
void ad403x_enter_reg_access(const AD403X_t * adc);
void ad403x_exit_reg_access(const AD403X_t * adc);
void ad403x_write_register(const AD403X_t * adc, uint16_t addr, uint8_t value);
void ad403x_WriteRegisterSingle(const AD403X_t * adc, uint16_t addr, uint8_t value);
uint8_t ad403x_read_register(const AD403X_t * adc, uint16_t addr);
uint8_t ad403x_read_register_single(const AD403X_t * adc, uint16_t addr);


#endif // AD4030_H_
