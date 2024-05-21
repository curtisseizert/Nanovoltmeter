
#ifndef GPIO_H_
#define GPIO_H_

#include "stm32u5xx.h"
#include "stm32u575xx.h"

		

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
	GPIO_SPEED_LO	=			0U,
	GPIO_SPEED_MED	=			1U,
	GPIO_SPEED_FAST	=			2U,
	GPIO_SPEED_MAX	=			3U
} gpioSpeed_TypeDef;

typedef enum{
	GPIO_NO_PUPD		=			0U,
	GPIO_PULL_UP		=			1U,
	GPIO_PULL_DOWN		=			2U
} gpioPupd_TypeDef;

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

typedef struct __GPIO_Init_TypeDef{
	gpioMode_TypeDef mode;
	gpioOtype_TypeDef otype;
	gpioSpeed_TypeDef ospeed;
	gpioPupd_TypeDef pupd;
} GPIO_Init_TypeDef;

typedef struct{
	GPIO_TypeDef * port;
	gpioPin_TypeDef pin;
} Pin_t;

typedef enum{
	GPIO_STATE_LO	=	0U,
	GPIO_STATE_HI	=	1U
} PinState_t;

Pin_t create_pin(GPIO_TypeDef * port, gpioPin_TypeDef pin);

void interrupt_config_rising(Pin_t gpio);
void interrupt_config_falling(Pin_t gpio);
void gpio_init_pin(Pin_t gpio, const GPIO_Init_TypeDef * init);
void gpio_config_af(Pin_t gpio, gpioAF_TypeDef AF);

void gpio_set_pin(Pin_t gpio);
void gpio_reset_pin(Pin_t gpio);
void gpio_set_state(const Pin_t gpio, PinState_t state);
PinState_t gpio_get_state(const Pin_t gpio);

#endif // GPIO_H_

