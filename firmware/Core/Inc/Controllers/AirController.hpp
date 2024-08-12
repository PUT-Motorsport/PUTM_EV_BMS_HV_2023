/*
 * AirController.hpp
 *
 *  Created on: Aug 12, 2024
 *      Author: lenovo
 */

#ifndef INC_CONTROLLERS_AIRCONTROLLER_HPP_
#define INC_CONTROLLERS_AIRCONTROLLER_HPP_

#include <Utils/AirUtils.hpp>
#include <Controllers/GpioController.hpp>

class AirController
{
	private:
		inline static GpioOut air_p { SIG_AIR_P_GPIO_Port, SIG_AIR_P_Pin, false };
		inline static GpioOut air_m { SIG_AIR_M_GPIO_Port, SIG_AIR_M_Pin, false };
		inline static GpioOut air_pre { SIG_AIR_PRE_GPIO_Port, SIG_AIR_PRE_Pin, false };

	public:
		inline static void setState(AirState state)
		{
			switch (state)
			{
				case AirState::Open:
					air_m.deactivate();
					air_p.deactivate();
					air_pre.deactivate();
					break;

				case AirState::Precharge:
					air_m.activate();
					air_p.deactivate();
					air_pre.activate();
					break;

				case AirState::Closed:
					air_m.activate();
					air_p.activate();
					air_pre.deactivate();
					break;
			}
		}
};


#endif /* INC_CONTROLLERS_AIRCONTROLLER_HPP_ */
