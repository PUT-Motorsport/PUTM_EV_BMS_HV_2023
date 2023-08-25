/*
 * ChargeBalanceController.hpp
 *
 *  Created on: Aug 4, 2023
 *      Author: jan
 */

#ifndef INC_PERYPHERIALMANAGERS_CHARGEBALANCECONTROLLER_HPP_
#define INC_PERYPHERIALMANAGERS_CHARGEBALANCECONTROLLER_HPP_

#include <main.h>
#include <algorithm>
#include <numeric>
#include <cmath>

class ChargeBalanceController
{
private:
    FullStackData &fsd;

public:
    constexpr ChargeBalanceController(FullStackData &fsda) : fsd{fsda} {}

    void update()
    {
        const auto &v = fsd.ltc_data.voltages;
        float max_v = *std::ranges::max_element(v.begin(), v.end());
        fsd.charge_balance.max_cell_voltage = max_v;
        float min_v = *std::ranges::min_element(v.begin(), v.end());
        fsd.charge_balance.min_cell_voltage = min_v;
        float avg_v = std::accumulate(v.begin(), v.end(), 0.0f) / v.size();
        fsd.charge_balance.avg_cell_voltage = avg_v;
        fsd.charge_balance.voltage_sum = avg_v * v.size();

        float variance = std::accumulate(v.begin(), v.end(), 0.0, [&](float acc, float x)
                                         { return acc + (x - avg_v) * (x - avg_v); }) / v.size();
        fsd.charge_balance.std_dev_cell_voltage = std::sqrt(variance);

        std::array<float, 135> vc;
        std::copy(v.begin(), v.end(), vc.begin());
        size_t n = 135 - 5; //vc.size() / 2;
        std::nth_element(vc.begin(), vc.begin()+n, vc.end());
        fsd.charge_balance.median_cell_voltage = vc[n];
    }

    constexpr void disableBalance()
    {
        std::ranges::fill(fsd.ltc_data.discharge, false);
    }

    constexpr void recalcBalance()
    {
        for (size_t i = 0; i < fsd.ltc_data.voltages.size(); i++)
        {
            const bool balance = (fsd.ltc_data.voltages[i] > fsd.charge_balance.median_cell_voltage);
            fsd.ltc_data.discharge[i] = balance;
        }
    }
};

#endif /* INC_PERYPHERIALMANAGERS_CHARGEBALANCECONTROLLER_HPP_ */
