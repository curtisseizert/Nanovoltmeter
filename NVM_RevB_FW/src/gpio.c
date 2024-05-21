

#include "gpio.h"
#include "stdint.h"

/// @brief Function for initializing the Pin_t type
/// @param port - gpioPort_TypeDef for the pin
/// @param pin - gpioPin_TypeDef for the pin
/// @return new_pin - Pin_t with members initialized
Pin_t create_pin(GPIO_TypeDef * port, gpioPin_TypeDef pin)
{
	Pin_t new_pin = {port,pin};
	return new_pin;
}


/// @brief registers a rising edge-triggered interrupt
/// @param gpio - Pin_t for the GPIO pin to be configured
void interrupt_config_rising(Pin_t gpio)
{
	// Generates a numeric representation of the GPIO port through pointer arithmetic.
	// Requires that addresses of GPIOA, GPIOB, GPIOC, etc., are sequentially and equally
	// spaced.
	uint32_t addr_offset = gpio.port - GPIOA;
	addr_offset /= (GPIOA - GPIOB);

	uint8_t exticr_ind = gpio.pin / 4;
	uint8_t exticr_pos = 8 * (gpio.pin % 4);
	
		// Configure EXTI registers
	EXTI->EXTICR[exticr_ind] &= ~(15U << exticr_pos); // Clear appropriate EXTICR bits
	EXTI->EXTICR[exticr_ind] |= (uint16_t) (addr_offset << exticr_pos); // Select EXTIx configuration
	
		// Unmask Interrupt request
	EXTI->IMR1 |= (1U << gpio.pin);
	
		// Trigger selection
	EXTI->RTSR1 |= (1U << gpio.pin);
}

/// @brief registers a falling edge-triggered interrupt
/// @param gpio - Pin_t for the GPIO pin to be configured
void interrupt_config_falling(const Pin_t gpio)
{
	uint32_t addr_offset = gpio.port - GPIOA;
	addr_offset /= (GPIOA - GPIOB);

	uint8_t exticr_ind = gpio.pin / 4;
	uint8_t exticr_pos = 8 * (gpio.pin % 4);
	
		// Configure EXTI registers
	EXTI->EXTICR[exticr_ind] &= ~(15U << exticr_pos); // Clear appropriate EXTICR bits
	EXTI->EXTICR[exticr_ind] |= (uint16_t) (addr_offset << exticr_pos); // Select EXTIx configuration
	
		// Unmask Interrupt request
	EXTI->IMR1 |= (1U << gpio.pin);
	
		// Trigger selection
	EXTI->FTSR1 |= (1U << gpio.pin);
}

/// @brief Initializes mode, output type, output speed, and pull-up/down for a GPIO pin
/// @param gpio - Pin_t for the pin to be configured
/// @param init - pointer to struct containing initialization parameters
void gpio_init_pin(Pin_t gpio, const GPIO_Init_TypeDef * init)
{
	gpio.port->MODER &= (uint32_t) ~(3U << (gpio.pin * 2));
	gpio.port->MODER |= (uint32_t) (init->mode << (gpio.pin * 2));
	
	gpio.port->OTYPER &= (uint32_t) ~(1U << gpio.pin);
	gpio.port->OTYPER |= (uint32_t) (init->otype << gpio.pin);
	
	gpio.port->OSPEEDR &= (uint32_t) ~(3U << (gpio.pin * 2));
	gpio.port->OSPEEDR |= (uint32_t) (init->ospeed << (gpio.pin * 2));
	
	gpio.port->PUPDR &= (uint32_t) ~(3U << (gpio.pin * 2));
	gpio.port->PUPDR |= (uint32_t) (init->pupd << (gpio.pin * 2));
}

/// @brief Sets the Alternate Function designation for a pin
/// @param gpio - Pin_t of the pin to be configured
/// @param AF - gpioAF_TypeDef of the alternate function for the pin
void gpio_config_af(Pin_t gpio, gpioAF_TypeDef AF)
{
	uint8_t afr = gpio.pin/8;
	uint8_t af_shift = 4 * (gpio.pin % 8);

	gpio.port->AFR[afr] &= ~(15U << af_shift);
	gpio.port->AFR[afr] |= (uint32_t) (AF << af_shift);
	
}

/// @brief Sets the output state of the pin to digital HI
/// @param gpio - Pin to be set
void gpio_set_pin(const Pin_t gpio)
{
	gpio.port->BSRR |= (1U << gpio.pin);
}

/// @brief Sets the output state of the pin to digital LO
/// @param gpio - Pin to be set
void gpio_reset_pin(const Pin_t gpio)
{
	gpio.port->BSRR |= (1U << (gpio.pin + 16));
}

/// @brief Sets the output state of the pin
/// @param gpio - Pin to be set
/// @param state - State to set the pin to
void gpio_set_state(const Pin_t gpio, PinState_t state)
{
	uint16_t shift = gpio.pin + (16 * (1 - state));
	gpio.port->BSRR |= (1U << shift);
}

PinState_t gpio_get_state(const Pin_t gpio)
{
	return (gpio.port->IDR & (1U << (uint16_t) gpio.pin)) == 0 ? GPIO_STATE_LO : GPIO_STATE_HI;
}
