/*
 * testTask.cpp
 *
 *  Created on: Jan 17, 2025
 *      Author: lenovo
 */

#include "app_freertos.h"
#include "main.h"
#include "gpio_wrap.hpp"
#include "tim_wrap.hpp"
#include "array"
#include "tim.h"

Gpio led_err(LED_ERROR_GPIO_Port, LED_ERROR_Pin, true);
Gpio led_wrn(LED_WARNING_GPIO_Port, LED_WARNING_Pin, true);
Gpio led_ok(LED_OK_GPIO_Port, LED_OK_Pin, true);
Gpio sig_err(SIGNAL_AMS_ERROR_GPIO_Port, SIGNAL_AMS_ERROR_Pin, true);
Gpio en_12v(EN_12V_GPIO_Port, EN_12V_Pin, false);

Tim fan1(&htim2, TIM_CHANNEL_1);
Tim fan2(&htim2, TIM_CHANNEL_2);
Tim fan3(&htim2, TIM_CHANNEL_3);
Tim fan4(&htim2, TIM_CHANNEL_4);
Tim fan5(&htim3, TIM_CHANNEL_1);
Tim fan6(&htim3, TIM_CHANNEL_2);
Tim fan7(&htim3, TIM_CHANNEL_3);

std::array<Tim*, 7> fans { &fan1, &fan2, &fan3, &fan4, &fan5, &fan6, &fan7 };

void startTestTask(void *argument)
{
	sig_err.reset();

	float i = 0.f;
	float iii = 25.f;
	float inc = iii;

	size_t k = 1;
	int kinc = -1;

	en_12v.set();

	for(auto& f : fans) f->startPwm();

	while(true)
	{
		osDelay(500);

		led_err.toggle();
		led_wrn.toggle();
		led_ok.toggle();

		if(i >= 100.f) inc = -iii;
		if(i <= 0.f) inc = iii;

		if(i <= 0)
		{
			if(k == 6) kinc = -1;
			if(k == 0) kinc = 1;
			k += kinc;
		}

		i += inc;

		fans[k]->setFill(i / 10.f);
	}
}
