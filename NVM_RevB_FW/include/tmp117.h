
    /*  tmp117.h    */

#ifndef TMP117_H_
#define TMP117_H_

#include <stdint.h>

#include "stm32u5xx.h"
#include "stm32u575xx.h"


#define TMP117_REG_TEMP				0x00
#define TMP117_REG_CONFIG			0x01
#define TMP117_REG_HIGH_LIM		0x02
#define TMP117_REG_LOW_LIM		0x03
#define	TMP117_REG_EEPROM_UL	0x04
#define TMP117_REG_EEPROM1		0x05
#define TMP117_REG_EEPROM2		0x06
#define TMP117_REG_EEPROM3		0x07
#define TMP117_REG_DEV_ID			0x0F

#define TMP117_CFG_HIGH_ALERT_Pos	15U
#define TMP117_CFG_LOW_ALERT_Pos	14U
#define TMP117_CFG_DATA_RDY_Pos		13U
#define TMP117_CFG_EEPROM_BSY_Pos	12U
#define TMP117_CFG_MOD_Pos				10U
#define TMP117_CFG_CONV_Pos				7U
#define TMP117_CFG_AVG_Pos				5U
#define TMP117_CFG_TNA_Pos				4U
#define TMP117_CFG_POL_Pos				3U
#define TMP117_CFG_DRALERT_Pos		2U
#define TMP117_CFG_SOFT_RESET_Pos	1U

#define TMP117_MODE_CONTINUOUS		(0U << TMP117_CFG_MOD_Pos)
#define TMP117_MODE_SHUTDOWN			(1U << TMP117_CFG_MOD_Pos)
#define TMP117_MODE_ONE_SHOT			(3U << TMP117_CFG_MOD_Pos)

#define TMP117_AVG_NO_AVERAGING		(0U << TMP117_CFG_AVG_Pos)
#define TMP117_AVG_8_AVERAGES			(1U << TMP117_CFG_AVG_Pos)
#define TMP117_AVG_32_AVERAGES		(2U << TMP117_CFG_AVG_Pos)
#define TMP117_AVG_64_AVERAGES		(3U << TMP117_CFG_AVG_Pos)

#define TMP117_INPUT_ADDR		0x48 	// 0x48
#define TMP117_ADC_ADDR			0x49 	// 0x49
#define TMP117_REF_ADDR			0x4A	// 0x4A


#define TMP117_DEFAULT_CONFIG	(TMP117_MODE_CONTINUOUS | TMP117_AVG_8_AVERAGES)

#define TMP117_FLAG_DMA_IS_INIT		1U

typedef struct __TMP117_Handle_TypeDef
{
	I2C_TypeDef * i2c;
	uint16_t code;
	uint8_t addr;
	uint8_t flags;
} TMP117_t;


void tmp117_init(TMP117_t * tmp117);
void tmp117_send_reg_addr(TMP117_t * tmp117, uint8_t reg);

int16_t tmp117_read_register(TMP117_t * tmp117, uint8_t reg);
float tmp117_get_temp(TMP117_t * tmp117);

float tmp117_code_to_temperature(int16_t code);
void TMP117nextData(TMP117_t * tmp117);


void TMP117SetupDMA(void);
void DMA_CH3_LLIinit(void);

#endif // TMP117_H_
