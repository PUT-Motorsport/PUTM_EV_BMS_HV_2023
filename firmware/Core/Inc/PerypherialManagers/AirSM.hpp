/*
 * AirSM.hpp
 *
 *  Created on: Aug 10, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_AIRSM_HPP_
#define INC_PERYPHERIALMANAGERS_AIRSM_HPP_

#include <stdint.h>

enum struct AIRstateEnum
{
	Open,
	Precharge,
	Closed
};

class AccumulatorIsolationRelaySM
{
	constexpr static uint32_t PRECHARGE_TIME{5000}; // ms

	bool TS_active_allowed{false};
	AIRstateEnum state{AIRstateEnum::Open};
	uint32_t precharge_start{0};

public:
	constexpr void set_TS(bool ts_active)
	{
		TS_active_allowed = ts_active;
	}

	constexpr void update(uint32_t tick)
	{

		if (not TS_active_allowed)
		{
			state = AIRstateEnum::Open;
		}

		switch (state)
		{
		case AIRstateEnum::Open:
		{
			if (TS_active_allowed)
			{
				state = AIRstateEnum::Precharge;
				precharge_start = tick;
			}
			break;
		}

		case AIRstateEnum::Precharge:
		{
			if ((int)tick - (int)precharge_start > (int)PRECHARGE_TIME)
			{
				state = AIRstateEnum::Closed;
			}
			break;
		}

		case AIRstateEnum::Closed:
			return;
		}
	}

	constexpr AIRstateEnum get() const
	{
		return state;
	}
};

#endif /* INC_PERYPHERIALMANAGERS_AIRSM_HPP_ */
