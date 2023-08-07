/*
 * SOCManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <main.h>

#include <app_freertos.h>
#include <StackData.hpp>
#include <Config.hpp>

void vSOCManagerTask(void *argument)
{
//	size_t num = 0;

	while(true)
	{
//		for(size_t i = 0; i < LtcConfig::CHAIN_SIZE; i++)
//		{
//			for(size_t j = 0; j < 9; j ++)
//			{
//				size_t index = i * 9;
//				if(num == j)
//					FullStackDataInstance::set().ltc_data.discharge[index + j] = true;
//				else
//					FullStackDataInstance::set().ltc_data.discharge[index + j] = false;
//			}
//		}
//		num++;
//		if (num >= 9) num = 0;

		osDelay(500);
	}
}
