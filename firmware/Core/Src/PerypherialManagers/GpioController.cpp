/*
 * Gpio.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <PerypherialManagers/GpioController.hpp>

Gpio::Gpio(const GPIO_TypeDef * const port, const uint32_t pin, const bool is_inverted) : port(port), pin(pin), is_inverted(is_inverted) { }

GpioOut::GpioOut(const GPIO_TypeDef *port, const uint32_t pin) : Gpio(port, pin, false) { }

GpioOut::GpioOut(const GPIO_TypeDef *port, const uint32_t pin, const bool is_inverted) : Gpio(port, pin, is_inverted) { }

void GpioOut::activate()
{
	HAL_GPIO_WritePin((GPIO_TypeDef*)(this->port), this->pin, (this->is_inverted ? GPIO_PIN_RESET : GPIO_PIN_SET));
}

void GpioOut::deactivate()
{
	HAL_GPIO_WritePin((GPIO_TypeDef*)(this->port), this->pin, (this->is_inverted ? GPIO_PIN_SET : GPIO_PIN_RESET));
}

void GpioOut::toggle()
{
	HAL_GPIO_TogglePin((GPIO_TypeDef*)(this->port), this->pin);
}

GpioIn::GpioIn(const GPIO_TypeDef * const port, const uint32_t pin) : Gpio(port, pin, false) { }

GpioIn::GpioIn(const GPIO_TypeDef * const port, const uint32_t pin, const bool is_inverted) : Gpio(port, pin, is_inverted) { }

bool GpioIn::isActive()
{
	/*
	 * 			truth table
	 *
	 *		port | is_inv | out
	 * 	   ======|========|======
	 *		  0  |    0   |  0
	 *		  1  |    0   |  1
	 *		  0  |    1   |  1
	 *		  1  |    1   |  0
	 *
	 *	  basically a XOR operation
	 *
	 */
	return((HAL_GPIO_ReadPin((GPIO_TypeDef*)(this->port), this->pin) == GPIO_PIN_SET) != this->is_inverted);
}
