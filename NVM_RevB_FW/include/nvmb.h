
/*  nvmb.h  */

/* Header file for NVM rev B board-specific abstraction layer */

#ifndef NVMB_H_
#define NVMB_H_

#include "stm32u5xx.h"
#include "stm32u575xx.h"

#include <stdint.h>
#include "gpio.h"
#include "sys_cfg.h"

#define USART3_BAUD				1500000



    /*  PIN DECLARATIONS  */
// Relay Control Pins
extern const Pin_t K1_S;               
extern const Pin_t K2_S;              
extern const Pin_t K3_S;               
extern const Pin_t K1_R; 
extern const Pin_t K2_R;
extern const Pin_t K3_R;

// Gain SW Pins
extern const Pin_t GAIN_40_DB_Pin;     
extern const Pin_t GAIN_60_DB_Pin;     

// AD5686 Pins
extern const Pin_t DAC_NRESET_Pin;

// AD403x-24 Pins
extern const Pin_t BUSY_C_Pin;
extern const Pin_t ADC_NRESET_Pin;
extern const Pin_t ADC_NCS_Pin;

// VBATT ADC Pins
extern const Pin_t VBATT_ADC_SW_Pin;

// OVERRANGE AND LED PINS
extern const Pin_t INPUT_OVR_LED_Pin;
extern const Pin_t NOVR_Pin;

// 5V4 PG INPUT
extern const Pin_t PG_IN_Pin;

// TIM PINS
extern const Pin_t TIM1_ETR;
extern const Pin_t TIM2_CH1;
extern const Pin_t TIM2_CH3;
extern const Pin_t TIM3_CH1;
extern const Pin_t TIM3_CH3;
extern const Pin_t TIM4_CH3;
extern const Pin_t TIM4_CH4;
extern const Pin_t TIM8_CH1N;

// SPI PINS
extern const Pin_t SPI1_SCK;
extern const Pin_t SPI1_CIPO;
extern const Pin_t SPI1_COPI;

extern const Pin_t SPI2_SCK;
extern const Pin_t SPI2_CIPO;
extern const Pin_t SPI2_COPI;
extern const Pin_t SPI2_NCS;

// USART PINS
extern const Pin_t USART3_RX;
extern const Pin_t USART3_TX;

// I2C PINS
extern const Pin_t I2C1_SCL;
extern const Pin_t I2C1_SDA;

// ALTERNATE FUNCTION DESIGNATIONS
static const gpioAF_TypeDef TIM1_ETR_AF            = AF1;
static const gpioAF_TypeDef TIM2_CH1_AF            = AF1;
static const gpioAF_TypeDef TIM2_CH3_AF            = AF1;
static const gpioAF_TypeDef TIM3_CH1_AF            = AF2;
static const gpioAF_TypeDef TIM3_CH3_AF            = AF2;
static const gpioAF_TypeDef TIM4_CH3_AF            = AF2;
static const gpioAF_TypeDef TIM4_CH4_AF            = AF2;
static const gpioAF_TypeDef TIM8_CH1N_AF           = AF3;

static const gpioAF_TypeDef SPI1_SCK_AF            = AF5;
static const gpioAF_TypeDef SPI1_CIPO_AF           = AF5;
static const gpioAF_TypeDef SPI1_COPI_AF           = AF5;

static const gpioAF_TypeDef SPI2_SCK_AF            = AF5;
static const gpioAF_TypeDef SPI2_CIPO_AF           = AF5;
static const gpioAF_TypeDef SPI2_COPI_AF           = AF5;
static const gpioAF_TypeDef SPI2_NCS_AF            = AF5;

static const gpioAF_TypeDef USART3_RX_AF           = AF7;
static const gpioAF_TypeDef USART3_TX_AF           = AF7;

static const gpioAF_TypeDef I2C1_SCL_AF            = AF4;
static const gpioAF_TypeDef I2C1_SDA_AF            = AF4;

// RELAY WRAPPER
typedef enum{
    RELAY_RESET = 0,
    RELAY_SET   = 1
} RelayState_t;

typedef struct
{
    const Pin_t * set;
    const Pin_t * reset;
    RelayState_t state;
} Relay_t;

extern Relay_t Relay_K1;
extern Relay_t Relay_K2;
extern Relay_t Relay_K3;

void relay_set_state(Relay_t * relay, RelayState_t state);
void pin_init(void);
void sys_clock_config(void);
void enablePeripheralClocks(void);
void init_housekeeping_timers(void);

void tim2_init(void);
void tim3_init(void);
void tim4_init(void);
void tim5_init(void);
void tim6_init(void);
void tim7_init(void);

uint32_t get_sys_freq(void);

void usart3_init(void);
void send_usart_data(DMA_Channel_TypeDef * dma, uint8_t len);

void AD403X_Reset(void);

#endif // NVMB_H_
