// Creator:  Jan Węgrzynowski
// Date: 2023.05.01
// Subject: Extended Kalman Filter for State of Charge estimation
// Description:
//      This is a header file for the Extended Kalman Filter for State of Charge estimation.
//      The code is written in C and optimized for ARM Cortex-M7.

/// Optimized assembly code for demonstration with GCC 10.3
/// Fully loop unrolled and vectorized and inlined
/// Used compile option: -O3 -mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wall -Wpedantic -Wextra -Werror -fsingle-precision-constant
/// https://godbolt.org/z/4T179r9rW
/// It is strongly recommended to use "-fsingle-precision-constant" flag when compiling the C code as not all constants are defined as floats, and ARM Cortex-M7 does not support double precision floating point operations.
/// For maximum performance it is recommended to use "-O3" flag when compiling the C code.

#pragma once
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"{
#endif 

#define STATE_DIM 3

typedef struct {
    float data[STATE_DIM][STATE_DIM];
} Matrix;


typedef struct {
    float data[STATE_DIM];
} Vector_row;


typedef struct {
    float data[STATE_DIM];
} Vector_col;


/// @brief EKF initialization with initial state and covariance matrix, default values for SoC estimation = 0.98
/// @param x State vector
/// @param P Covariance matrix

void EKF_init(Vector_col* x, Matrix* P);


/// @brief Update of the Extended Kalman Filter for the SoC estimation
/// @param x  State vector
/// @param P  Covariance matrix
/// @param battery_voltage cell voltage [V]
/// @param battery_current battery current [A] (positive for discharge)
/// @param charging true if charging using grid charger

void EKF_update(Vector_col* x, Matrix* P, float battery_voltage, float battery_current, bool charging);

/// @brief Get the SoC from the state vector
/// @param x State vector
/// @return State of charge [-] (0: empty, 1: full)

float EKF_get_SoC(const Vector_col *x);


/// @brief Set the SoC in the state vector based on the cell voltage
///     Use this function to initialize the SoC
///     only if there is no prior information about the SoC.
///     It is recomended save SoC in EEPROM or other nonvolatile memory and load it on startup using EKF_set_SoC function.
/// @param x State vector
/// @param voltage cell voltage [V]

void EKF_set_SoC_based_on_voltage(Vector_col* x, float voltage);


/// @brief Set the SoC in the state vector
///     Use this function to initialize the SoC from prior information.
/// @param x State vector
/// @param soc State of charge [-] (0: empty, 1: full)

void EKF_set_SoC(Vector_col* x, float soc);


#ifdef __cplusplus
}
#endif