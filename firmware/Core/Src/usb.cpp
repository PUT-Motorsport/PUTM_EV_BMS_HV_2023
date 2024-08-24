/*
 * usb.cpp
 *
 *  Created on: Aug 22, 2024
 *      Author: lenovo
 */

#include <main.h>
#include <app_freertos.h>
#include <StackData.hpp>

static bool done { false };

void StartTask09(void *argument)
{
	while(true)
	{
		osDelay(100);
		if(FullStackDataInstance::get().usb_events.communication_test and not done)
		{
			while(READ_BIT(FLASH->SR, FLASH_SR_BSY_Msk) != 0);

			if(HAL_FLASH_Unlock() != HAL_OK) continue;

			while(READ_BIT(FLASH->SR, FLASH_SR_BSY_Msk) != 0);

			SET_BIT(FLASH->CR, FLASH_CR_OPTLOCK_Msk);

			if(HAL_FLASH_OB_Unlock() != HAL_OK) continue;

			//pattern 14 - 2 row
			SET_BIT(FLASH->OPTR, FLASH_OPTR_nBOOT1_Msk);
			CLEAR_BIT(FLASH->OPTR, FLASH_OPTR_nBOOT0_Msk);
			CLEAR_BIT(FLASH->OPTR, FLASH_OPTR_nSWBOOT0_Msk);

			SET_BIT(FLASH->CR, FLASH_CR_OPTSTRT_Msk);

			while(READ_BIT(FLASH->SR, FLASH_SR_BSY_Msk) != 0);

			HAL_FLASH_OB_Lock();
			HAL_FLASH_Lock();

			done = true;
		}
	}
}
