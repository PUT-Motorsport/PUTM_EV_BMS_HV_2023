/*
 * SOCManager.cpp
 *
 *  Created on: Jul 4, 2023
 *      Author: Piotr Lesicki
 */

#include <main.h>

#include <app_freertos.h>
#include <StackData.hpp>

void vSOCManagerTask(void *argument)
{
//	size_t num = 0;

	while(true)
	{
//		for(size_t i = 0; i < cell_count; i++)
//		{
//			if(num == i)
//				FullStackDataInstance::getAndModify().ltc_data.discharge[i] = true;
//			else
//				FullStackDataInstance::getAndModify().ltc_data.discharge[i] = false;
//		}
//		num++;
//		if (num >= cell_count) num = 0;


		osDelay(100);
	}
}
