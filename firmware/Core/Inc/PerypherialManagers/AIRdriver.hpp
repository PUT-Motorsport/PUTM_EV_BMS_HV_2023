/*
 * AIRdriver.hpp
 *
 *  Created on: Aug 15, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_AIRDRIVER_HPP_
#define INC_PERYPHERIALMANAGERS_AIRDRIVER_HPP_


#include "PerypherialManagers/GpioController.hpp"
#include "AirSM.hpp"
#include "main.h"

class AIRdriver{

	inline static GpioOut air_P { SIG_AIR_P_GPIO_Port, SIG_AIR_P_Pin, false };
	inline static GpioOut air_M { SIG_AIR_M_GPIO_Port, SIG_AIR_M_Pin, false };
	inline static GpioOut precharge { SIG_AIR_PRE_GPIO_Port, SIG_AIR_PRE_Pin, false };

public:
	inline static void SetState(AIRstateEnum state){
		switch (state) {
			case AIRstateEnum::Open:
				air_M.deactivate();
				air_P.deactivate();
				precharge.deactivate();
				break;

			case AIRstateEnum::Precharge:
				air_M.activate();
				air_P.deactivate();
				precharge.activate();
				break;

			case AIRstateEnum::Closed:
				air_M.activate();
				air_P.activate();
				precharge.deactivate();
				break;
		}
	}

};



#endif /* INC_PERYPHERIALMANAGERS_AIRDRIVER_HPP_ */
