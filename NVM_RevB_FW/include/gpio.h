
#ifndef GPIO_H
#define GPIO_H

#include "stm32u5xx.h"
#include "stm32u575xx.h"


	/* GPIO PIN DEFINES */
	
// Relay Control Pins	
#define K1_S_L_Pin								GPIO_PIN_9
#define K1_S_L_Port								GPIO_PORT_A
#define K2_S_L_Pin								GPIO_PIN_10
#define K2_S_L_Port								GPIO_PORT_A
#define K3_S_L_Pin								GPIO_PIN_11
#define K3_S_L_Port								GPIO_PORT_A
#define K1_R_L_Pin								GPIO_PIN_3
#define K1_R_L_Port								GPIO_PORT_B
#define K2_R_L_Pin								GPIO_PIN_4
#define K2_R_L_Port								GPIO_PORT_B
#define K3_R_L_Pin								GPIO_PIN_5
#define K3_R_L_Port								GPIO_PORT_B

// Gain SW Pins
#define GAIN_40_DB_Pin						GPIO_PIN_12
#define GAIN_40_DB_Port						GPIO_PORT_C
#define GAIN_60_DB_Pin						GPIO_PIN_2
#define GAIN_60_DB_Port						GPIO_PORT_D

// AD5686 Pins
#define DAC_NRESET_Pin						GPIO_PIN_10
#define DAC_NRESET_Port						GPIO_PORT_B

// AD403x-24 Pins
#define BUSY_C_Pin								GPIO_PIN_0
#define BUSY_C_Port								GPIO_PORT_A
#define ADC_NRESET_Pin						GPIO_PIN_1
#define ADC_NRESET_Port						GPIO_PORT_H
#define ADC_NCS_Pin								GPIO_PIN_2
#define ADC_NCS_Port							GPIO_PORT_A

// VBATT ADC Pins
#define VBATT_ADC_SW_Pin					GPIO_PIN_9
#define VBATT_ADC_SW_Port					GPIO_PORT_C


// OVERRANGE AND LED PINS
#define INPUT_OVR_LED_Pin					GPIO_PIN_8
#define INPUT_OVR_LED_Port				GPIO_PORT_A
#define NOVR_Pin									GPIO_PIN_13
#define NOVR_Port									GPIO_PORT_C

// 5V4 PG INPUT
#define PG_IN_Pin									GPIO_PIN_15
#define PG_IN_Port								GPIO_PORT_C


	/* GPIO CLOCK MASK */
#define GPIO_CLK_MSK							

typedef enum{
	GPIO_PORT_A = 0U,
	GPIO_PORT_B = 1U,
	GPIO_PORT_C = 2U,
	GPIO_PORT_D = 3U,
	GPIO_PORT_E = 4U,
	GPIO_PORT_F = 5U,
	GPIO_PORT_G = 6U,
	GPIO_PORT_H = 7U,
} gpioPort_TypeDef;

typedef enum{
	GPIO_PIN_0	 = 0U,
	GPIO_PIN_1	 = 1U,
	GPIO_PIN_2	 = 2U,
	GPIO_PIN_3	 = 3U,
	GPIO_PIN_4	 = 4U,
	GPIO_PIN_5	 = 5U,
	GPIO_PIN_6	 = 6U,
	GPIO_PIN_7	 = 7U,
	GPIO_PIN_8	 = 8U,
	GPIO_PIN_9	 = 9U,
	GPIO_PIN_10	 = 10U,
	GPIO_PIN_11	 = 11U,
	GPIO_PIN_12	 = 12U,
	GPIO_PIN_13	 = 13U,
	GPIO_PIN_14	 = 14U,
	GPIO_PIN_15	 = 15U
} gpioPin_TypeDef;

typedef enum{
	GPIO_INPUT 	= 0U,
	GPIO_OUTPUT = 1U,
	GPIO_AF			=	2U,
	GPIO_ANALOG	=	3U
} gpioMode_TypeDef;

typedef enum{
	GPIO_PUSH_PULL	= 0U,
	GPIO_OPEN_DRAIN	=	1U
} gpioOtype_TypeDef;

typedef enum{
	GPIO_SPEED_LO		=			0U,
	GPIO_SPEED_MED	=			1U,
	GPIO_SPEED_FAST	=			2U,
	GPIO_SPEED_MAX	=			3U
} gpioSpeed_TypeDef;

typedef enum{
	GPIO_NO_PUPD		=			0U,
	GPIO_PULL_UP		=			1U,
	GPIO_PULL_DOWN	=			2U
} gpioPupd_TypeDef;

typedef struct gpio_init_TypeDef{
	gpioPort_TypeDef gpioPort;
	gpioPin_TypeDef gpioPin;
	gpioMode_TypeDef mode;
	gpioOtype_TypeDef otype;
	gpioSpeed_TypeDef ospeed;
	gpioPupd_TypeDef pupd;
} gpio_init_TypeDef;

typedef enum{
	AF0 	= 0U,
	AF1 	= 1U,
	AF2 	= 2U,
	AF3 	= 3U,
	AF4 	= 4U,
	AF5 	= 5U,
	AF6 	= 6U,
	AF7 	= 7U,
	AF8 	= 8U,
	AF9 	= 9U,
	AF10 	= 10U,
	AF11 	= 11U,
	AF12 	= 12U,
	AF13 	= 13U,
	AF14 	= 14U,
	AF15 	= 15U,

} gpioAF_TypeDef;

void gpioInit(void);

void interruptConfigRising(uint8_t gpiox, uint8_t pin);
void interruptConfigFalling(uint8_t gpiox, uint8_t pin);


void gpioInitPin(gpioPort_TypeDef port, gpioPin_TypeDef pin, gpioMode_TypeDef mode, gpioOtype_TypeDef otype, gpioSpeed_TypeDef ospeed, gpioPupd_TypeDef pupd);
//void gpioInitPin(gpio_init_TypeDef * hinit);

void gpioSetAF(gpioPort_TypeDef port, gpioPin_TypeDef pin, gpioAF_TypeDef);
	
void gpioSetPin(gpioPort_TypeDef port, gpioPin_TypeDef pin);
void gpioResetPin(gpioPort_TypeDef port, gpioPin_TypeDef pin);

#endif

