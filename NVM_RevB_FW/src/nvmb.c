
/* nvmb.c */

/*  Provides a board-specific abstraction layer */
/*  for NVM rev B   */

#include "nvmb.h"
#include "tim.h"

    /* SYSTEM CLOCK AND POWER PARAMETERS*/
static const uint32_t OSC_FREQ =   24000000;   // HSE OSCILLATOR FREQUENCY   
static const uint8_t PLL1_M    =   1;          // PLL1_M = 2
static const uint8_t PLL1_N    =   15;         // PLL1_N = 24
static const uint8_t PLL1_R    =   3;          // PLL1_R = 4
static const uint8_t PLL1_Q    =   3;          // PLL1_Q = 4
static const VOSR_RANGE_TypeDef VOSR_RANGE   =   VOSR_RANGE_1;

 /*  PIN DEFINITIONS  */
// Relay Control Pins
const Pin_t K1_S                = {GPIOA, GPIO_PIN_9};
const Pin_t K2_S                = {GPIOA, GPIO_PIN_10};
const Pin_t K3_S                = {GPIOA, GPIO_PIN_11};
const Pin_t K1_R                = {GPIOB, GPIO_PIN_3};
const Pin_t K2_R                = {GPIOB, GPIO_PIN_4};
const Pin_t K3_R                = {GPIOB, GPIO_PIN_5};

// Gain SW Pins
const Pin_t GAIN_40_DB_Pin      = {GPIOC, GPIO_PIN_12};
const Pin_t GAIN_60_DB_Pin      = {GPIOD, GPIO_PIN_2};

// AD5686 Pins
const Pin_t DAC_NRESET_Pin      = {GPIOB, GPIO_PIN_10};

// AD403x-24 Pins
const Pin_t BUSY_C_Pin          = {GPIOA, GPIO_PIN_0};
const Pin_t ADC_NRESET_Pin      = {GPIOH, GPIO_PIN_1};
const Pin_t ADC_NCS_Pin         = {GPIOA, GPIO_PIN_2};

// VBATT ADC Pins
const Pin_t VBATT_ADC_SW_Pin    = {GPIOC, GPIO_PIN_9};

// OVERRANGE AND LED PINS
const Pin_t INPUT_OVR_LED_Pin   = {GPIOA, GPIO_PIN_8};
const Pin_t NOVR_Pin            = {GPIOC, GPIO_PIN_13};

// 5V4 PG INPUT
const Pin_t PG_IN_Pin           = {GPIOC, GPIO_PIN_15};

// TIM PINS
const Pin_t TIM1_ETR            = {GPIOA, GPIO_PIN_12};
const Pin_t TIM2_CH1            = {GPIOA, GPIO_PIN_15};
const Pin_t TIM2_CH3            = {GPIOB, GPIO_PIN_10};
const Pin_t TIM3_CH1            = {GPIOC, GPIO_PIN_6};
const Pin_t TIM3_CH3            = {GPIOC, GPIO_PIN_8};
const Pin_t TIM4_CH3            = {GPIOB, GPIO_PIN_8};
const Pin_t TIM4_CH4            = {GPIOB, GPIO_PIN_9};
const Pin_t TIM8_CH1N           = {GPIOA, GPIO_PIN_5};

// SPI PINS
const Pin_t SPI1_SCK            = {GPIOA, GPIO_PIN_1};
const Pin_t SPI1_CIPO           = {GPIOA, GPIO_PIN_6};
const Pin_t SPI1_COPI           = {GPIOA, GPIO_PIN_7};

const Pin_t SPI2_SCK            = {GPIOB, GPIO_PIN_13};
const Pin_t SPI2_CIPO           = {GPIOB, GPIO_PIN_14};
const Pin_t SPI2_COPI           = {GPIOB, GPIO_PIN_15};
const Pin_t SPI2_NCS            = {GPIOB, GPIO_PIN_12};

// USART PINS
const Pin_t USART3_RX           = {GPIOC, GPIO_PIN_11};
const Pin_t USART3_TX           = {GPIOC, GPIO_PIN_10};

// I2C PINS
const Pin_t I2C1_SCL            = {GPIOB, GPIO_PIN_6};
const Pin_t I2C1_SDA            = {GPIOB, GPIO_PIN_7};

/// @brief Struct containing system clock parameters
static SysConfig_t sys = {
    .osc_freq = OSC_FREQ,
    .vosr = VOSR_RANGE,
    .pll1_m = PLL1_M,
    .pll1_n = PLL1_N,
    .pll1_r = PLL1_R,
    .pll1_q = PLL1_Q,
};

Relay_t Relay_K1 = {.set = &K1_S, .reset = &K1_R};
Relay_t Relay_K2 = {.set = &K2_S, .reset = &K2_R};
Relay_t Relay_K3 = {.set = &K3_S, .reset = &K3_R};

/// @brief Performs initial configuration of system clocks
/// @param None
void sys_clock_config(void)
{
    clock_config(&sys);
    enablePeripheralClocks();
    init_housekeeping_timers();
}

/// @brief Gives the system frequency in Hz
/// @param None 
/// @return system frequency in Hz
uint32_t get_sys_freq(void)
{
    return sys.sys_freq;
}

/// @brief Enables all peripheral clocks
/// @param None
void enablePeripheralClocks(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPDMA1EN;
	
	RCC->AHB2ENR1 |= RCC_AHB2ENR1_ADC12EN |
						RCC_AHB2ENR1_GPIOHEN |
						RCC_AHB2ENR1_GPIODEN |
						RCC_AHB2ENR1_GPIOCEN |
						RCC_AHB2ENR1_GPIOBEN |
						RCC_AHB2ENR1_GPIOAEN;
	
	RCC->AHB3ENR |= RCC_AHB3ENR_DAC1EN
								|	RCC_AHB3ENR_PWREN;
	
	RCC->APB1ENR1 |= RCC_APB1ENR1_I2C1EN |
					RCC_APB1ENR1_USART3EN |
					RCC_APB1ENR1_SPI2EN |
					RCC_APB1ENR1_TIM7EN |
					RCC_APB1ENR1_TIM6EN |
					RCC_APB1ENR1_TIM5EN |
					RCC_APB1ENR1_TIM4EN |
					RCC_APB1ENR1_TIM3EN |
					RCC_APB1ENR1_TIM2EN; 
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM8EN | RCC_APB2ENR_SPI1EN |
					RCC_APB2ENR_TIM1EN | RCC_APB2ENR_TIM15EN; 
	
	RCC->APB3ENR |= RCC_APB3ENR_RTCAPBEN |
					RCC_APB3ENR_VREFEN |
					RCC_APB3ENR_LPTIM1EN |
					RCC_APB3ENR_SYSCFGEN; 
	
}

/// @brief Initializes all MCU Pins
/// @param none
void pin_init(void)
{
	GPIO_Init_TypeDef init = {
        .mode = GPIO_OUTPUT,
        .otype = GPIO_PUSH_PULL,
        .ospeed = GPIO_SPEED_LO,
        .pupd = GPIO_NO_PUPD
    };

    // GPIO SW CONTROL OUTPUT PINS
    gpio_init_pin(K1_S, &init);
    gpio_init_pin(K1_R, &init);
    gpio_init_pin(K2_S, &init);
    gpio_init_pin(K2_R, &init);
    gpio_init_pin(K3_S, &init);
    gpio_init_pin(K3_R, &init);

    gpio_init_pin(GAIN_40_DB_Pin, &init);
    gpio_init_pin(GAIN_60_DB_Pin, &init);
    gpio_set_pin(GAIN_40_DB_Pin);

    init.pupd = GPIO_PULL_DOWN;
    gpio_init_pin(VBATT_ADC_SW_Pin, &init);

    init.pupd = GPIO_PULL_UP;

    // GPIO ACTIVE LOW CONTROL OUTPUT PINS
    gpio_init_pin(ADC_NCS_Pin, &init);
    gpio_init_pin(ADC_NRESET_Pin, &init);
    gpio_init_pin(DAC_NRESET_Pin, &init);

    gpio_set_pin(ADC_NRESET_Pin);
    gpio_set_pin(DAC_NRESET_Pin);
    gpio_set_pin(ADC_NCS_Pin);

    // GPIO INPUT & EXTI PINS
    init.mode = GPIO_INPUT;
    init.pupd = GPIO_NO_PUPD;
    
    gpio_init_pin(BUSY_C_Pin, &init);
    gpio_init_pin(NOVR_Pin, &init);
    gpio_init_pin(PG_IN_Pin, &init);

    interrupt_config_falling(BUSY_C_Pin);

        /* PERIPHERAL-CONTROLLED PINS */
    // TIM PINS    
    init.mode = GPIO_AF;
    init.ospeed = GPIO_SPEED_MED;

    gpio_init_pin(TIM1_ETR, &init);
    gpio_init_pin(TIM2_CH1, &init);
    gpio_init_pin(TIM2_CH3, &init);
    gpio_init_pin(TIM3_CH1, &init);
    gpio_init_pin(TIM3_CH3, &init);
    gpio_init_pin(TIM4_CH3, &init);
    gpio_init_pin(TIM4_CH4, &init);
    gpio_init_pin(TIM8_CH1N, &init);

    gpio_config_af(TIM1_ETR, TIM1_ETR_AF);
    

    gpio_config_af(TIM8_CH1N, TIM8_CH1N_AF);


    // SPI PINS
    init.ospeed = GPIO_SPEED_MAX;
    init.pupd = GPIO_PULL_DOWN;
    gpio_init_pin(SPI1_SCK, &init);
    gpio_init_pin(SPI1_CIPO, &init);
    gpio_init_pin(SPI1_COPI, &init);
    gpio_init_pin(SPI2_SCK, &init);
    gpio_init_pin(SPI2_CIPO, &init);
    gpio_init_pin(SPI2_COPI, &init);

    init.pupd = GPIO_PULL_UP;
    gpio_init_pin(SPI2_NCS, &init);

    gpio_config_af(SPI1_SCK, SPI1_SCK_AF);
    gpio_config_af(SPI1_COPI, SPI1_COPI_AF);
    gpio_config_af(SPI1_CIPO, SPI1_CIPO_AF);
    gpio_config_af(SPI2_SCK, SPI2_SCK_AF);
    gpio_config_af(SPI2_CIPO, SPI2_CIPO_AF);
    gpio_config_af(SPI2_COPI, SPI2_COPI_AF);
    gpio_config_af(SPI2_NCS, SPI2_NCS_AF);

    // USART PINS
    init.pupd = GPIO_NO_PUPD;

    gpio_init_pin(USART3_RX, &init);
    gpio_init_pin(USART3_TX, &init);

    gpio_config_af(USART3_RX, USART3_RX_AF);
    gpio_config_af(USART3_TX, USART3_TX_AF);

    //I2C PINS
    init.otype = GPIO_OPEN_DRAIN;
    init.pupd = GPIO_PULL_UP;
    init.ospeed = GPIO_SPEED_LO;

    gpio_init_pin(I2C1_SDA, &init);
    gpio_init_pin(I2C1_SCL, &init);

    gpio_config_af(I2C1_SDA, I2C1_SDA_AF);
    gpio_config_af(I2C1_SCL, I2C1_SCL_AF);
}

/// @brief Initializes housekeeping timers used in delay and relay (re)set actions
/// @param None 
void init_housekeeping_timers(void)
{
    tim6_init();
    tim7_init();
}

/// @brief Initializes TIM2, which controls the modulator switches
/// @param None
void tim2_init(void)
{
	TIM2->CR1 |= TIM_CR1_URS;
	TIM2->CR2 |= (1U << TIM_CR2_MMS_Pos); // CNT_EN used as tim_trgo
	
	TIM2->CCMR1 |= (6U << TIM_CCMR1_OC1M_Pos) 	// CH1:  PWM Mode 1
								| TIM_CCMR1_OC1PE							// Output 1 Preload Enable
								|	TIM_CCMR1_OC1FE;						// Output 1 Fast mode enable

	
	TIM2->CCMR2 |= (4U << TIM_CCMR2_OC3M_Pos) 	// CH3: Combined PWM Mode 1
								| (1U << 16)									// Noncontiguous MSB for OC3M
								| TIM_CCMR2_OC3PE							// Output 1 Preload Enable
								|	TIM_CCMR2_OC3FE 						// Output 1 Fast mode enable
								| (7U << TIM_CCMR2_OC4M_Pos) 	// CH4: PWM Mode 2
								| TIM_CCMR2_OC4PE						// Output 1 Preload Enable
								|	TIM_CCMR2_OC4FE;						// Output 1 Fast mode enable
								
	TIM2->CCER |= TIM_CCER_CC3P;	// Invert polarity of CH3
	TIM2->CCER |= TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E;	// Enable Capture Compare 1, 3 & 4
}

/// @brief Initializes TIM3, which controls the demodulator switches
/// @param None 
void tim3_init(void)
{
	TIM3->CR1 |= TIM_CR1_URS;
	TIM3->CR2 |= (2U << TIM_CR2_MMS_Pos); // tim_trgo = UE
	
	TIM3->SMCR |= (1U << TIM_SMCR_TS_Pos) // Trigger = tim_itr1 (TIM2)
								| (6U << TIM_SMCR_SMS_Pos); // Trigger mode

	TIM3->DIER = TIM_DIER_UIE; // Update Event interrupt interrupt enable
	
	TIM3->CCMR1 |= (6U << TIM_CCMR1_OC1M_Pos) 	// CH1: PWM Mode 1
								| TIM_CCMR1_OC1PE							// Output 1 Preload Enable
								|	TIM_CCMR1_OC1FE;						// Output 1 Fast mode enable

	
	TIM3->CCMR2 |= (4U << TIM_CCMR2_OC3M_Pos) 	// CH3: Combined PWM Mode 1
								| (1U << 16)									// Noncontiguous MSB for OC3M
								| TIM_CCMR2_OC3PE							// Output 3 Preload Enable
								|	TIM_CCMR2_OC3FE 						// Output 3 Fast mode enable
								| (7U << TIM_CCMR2_OC4M_Pos) 	// CH4: PWM Mode 2
								| TIM_CCMR2_OC4PE							// Output 4 Preload Enable
								|	TIM_CCMR2_OC4FE;						// Output 4 Fast mode enable
		
	TIM3->CCER |= TIM_CCER_CC3P;	// Invert polarity of CH3
	TIM3->CCER |= TIM_CCER_CC1E | TIM_CCER_CC3E | TIM_CCER_CC4E;	// Enable Capture Compare 1, 3 & 4
}

/// @brief Initializes TIM4, which controls the CDS switches
/// @param None 
void tim4_init(void)
{
	TIM4->SMCR |= (1U << TIM_SMCR_TS_Pos) // Trigger = tim_itr1 (TIM2)
							| (6U << TIM_SMCR_SMS_Pos); // Trigger mode
	
	
	TIM4->CCMR2 |= (6U << TIM_CCMR2_OC3M_Pos) 	// CH3: PWM Mode 1
								| TIM_CCMR2_OC3PE							// Output 3 Preload Enable
								|	TIM_CCMR2_OC3FE 						// Output 3 Fast mode enable
								| (7U << TIM_CCMR2_OC4M_Pos) 	// CH4: PWM Mode 2
								| TIM_CCMR2_OC4PE							// Output 4 Preload Enable
								|	TIM_CCMR2_OC4FE;						// Output 4 Fast mode enable

	TIM4->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E;	// Enable Capture Compare 3 & 4
}

/// @brief Initializes TIM5, which controls the settling delay after switch transitions
/// @param None 
void tim5_init(void)
{
	TIM5->CR1 |= TIM_CR1_URS;
	TIM5->CR2 |= (3U << TIM_CR2_MMS_Pos); // tim_trgo = Compare Pulse
	
	TIM5->SMCR |= (1U << TIM_SMCR_TS_Pos) // Trigger = tim_itr1 (TIM2)
							| (6U << TIM_SMCR_SMS_Pos); // Trigger mode

	TIM5->CCMR1 |= (7U << TIM_CCMR1_OC1M_Pos) // CH1: PWM Mode 2
								| TIM_CCMR1_OC1PE
								| TIM_CCMR1_OC1FE; 	
	TIM5->CCR1 = 480U;
}

/// @brief Initializes TIM6, which provides blocking delays
/// @param None 
void tim6_init(void)
{
	/* Setup for blocking delays of 5ms by default */
	TIM6->CR1 |= TIM_CR1_OPM | TIM_CR1_URS;
	TIM6->EGR |= TIM_EGR_UG;
	TIM6->PSC = (get_sys_freq() / 1000000) - 1;
}

/// @brief Initializes TIM7, which provides non-blocking delays for relay (re)sets
/// @param None 
void tim7_init(void)
{
	TIM7->CR1 |= TIM_CR1_OPM | TIM_CR1_URS; // One pulse mode, overflow triggers UE
	TIM7->EGR |= TIM_EGR_UG;
	TIM7->ARR = 9999; // Set ARR to 10 ms pulse
	
	TIM7->PSC = (get_sys_freq() / 1000000) - 1; // Set prescaler to 1 tick/us
	
	TIM7->DIER |= TIM_DIER_UIE;
}

/// @brief Sets the state of a relay
/// @param relay Relay whose state is to be set
/// @param state State to set the relay to
void relay_set_state(Relay_t * relay, RelayState_t state)
{
    relay->state = state;
    if(state == RELAY_RESET) gpio_set_pin(relay->reset[0]);
    if(state == RELAY_SET) gpio_set_pin(relay->set[0]);

    TIM7->EGR |= TIM_EGR_UG; // Resets the timer to avoid runt pulses
    enable_timer(TIM7);
}

/// @brief Initializes USART3, which performs serial Tx/Rx over (isolated) USB
/// @param None 
void usart3_init(void)
{
	// Configure UART
	USART3->CR1 |= USART_CR1_CMIE | USART_CR1_FIFOEN;				// Enable character match interrupt
	USART3->CR2 |= (0x0A << USART_CR2_ADD_Pos);	// Newline "\n" for character match interrupt
	USART3->CR3 |= USART_CR3_DMAT | USART_CR3_DMAR; // Enable DMA
	
	USART3->BRR = get_sys_freq()/USART3_BAUD; // Baud rate of 1.5M, PCLK1 at 48 MHz
	
	// Enable TX and RX
	USART3->CR1 |= USART_CR1_UE | USART_CR1_TE | USART_CR1_RE;
	USART3->ICR |= USART_ICR_TCCF;
}

/// @brief Sends data over usart using DMA
/// @param dma DMA channel for USART TX
/// @param len length (in bytes) of data to be sent
void send_usart_data(DMA_Channel_TypeDef * dma, uint8_t len)
{
	dma->CBR1 = len;
	dma->CCR |= DMA_CCR_EN;
}

