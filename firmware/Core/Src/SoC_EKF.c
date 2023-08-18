// Creator:  Jan Węgrzynowski
// Date: 2023.06.02
// Subject: Extended Kalman Filter for State of Charge estimation

#include "SoC_EKF.h"

/// @brief Polynomial coefficients for OCV vs SOC curve
static const float BATT_OCV_POLY[] = {2034.785202f,-9878.314180f,20304.286795f,-22998.124140f,15652.018744f,-6548.995145f,1657.814181f,-240.646928f,18.231580f,3.143621f};
static const size_t BATT_OCV_POLY_COEF_COUNT = sizeof(BATT_OCV_POLY) / sizeof(BATT_OCV_POLY[0]);

static const float BATT_D_OCV_POLY[] = {18313.066819f,-79026.513437f,142130.007563f,-137988.744839f,78260.093719f,-26195.980582f,4973.442542f,-481.293856f,18.231580f};
static const size_t BATT_D_OCV_POLY_COEF_COUNT = sizeof(BATT_D_OCV_POLY) / sizeof(BATT_D_OCV_POLY[0]);

static const float Ts = 0.1f;                   /// Sampling time [s]
static const float Nominal_capacity = 7.25439f;   /// Battery cell [Ah]


/// @brief Battery model state transition matrix created with Ts = 0.1s
static const Matrix A = {
    .data = {{1.0f, 0.0f, 0.0f}, {0.0f, 1.98899788e+00f, -0.98900757f}, {0.0f, 1.0f, 0.0f}}
};

/// @brief Battery model input matrix created with Ts = 0.1s
static const Vector_col B = {
    .data = {- Ts / Nominal_capacity / 60.0f / 60.0f, 1.0f, 0.0f}
};

/// @brief Battery model output matrix created with Ts = 0.1s
static const Vector_row C = {
    .data = {0.0f, 2.33058931e-05f, -2.32660122e-05f}
};

/// @brief Battery model output matrix created with Ts = 0.1
static const float D = {0.00698732f};

/// Battery model process noise covariance matrix tuned with Ts = 0.1s
static const Matrix Q = {
    .data = {{0.0002f, 0.0f, 0.0f},
             {0.0f, 0.02f, 0.0f},
             {0.0f, 0.0f, 0.02f }}
};

/// @brief Battery model measurement noise covariance matrix tuned with Ts = 0.1
static const float R = 2500000.0f / 10.0;
 /// @brief Increase measurement noise covariance when charging to avoid overestimation of SOC
static const float R_charge = R * 99.0f;

static inline Vector_col matrix_vector_multiply(Matrix m, Vector_col v) {
    Vector_col result;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        float dot_product = 0.0;
        for (unsigned int j = 0; j < STATE_DIM; ++j) {
            dot_product += m.data[i][j] * v.data[j];
        }
        result.data[i] = dot_product;
    }
    return result;
}

static inline Vector_col vector_scalar_multiplication(Vector_col v, float scalar) {
    Vector_col result;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        result.data[i] = v.data[i] * scalar;
    }
    return result;
}

static inline Vector_col vector_addition(Vector_col v1, Vector_col v2) {
    Vector_col result;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        result.data[i] = v1.data[i] + v2.data[i];
    }
    return result;
}

static float vector_dot_product(Vector_row v1, Vector_col v2) {
    float result = 0.0;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        result += v1.data[i] * v2.data[i];
    }
    return result;
}

static Matrix matrix_addition(Matrix a, Matrix b){
    Matrix result;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        for (unsigned int j = 0; j < STATE_DIM; ++j) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}


static Matrix vector_cross_product(Vector_col col, Vector_row row){
    Matrix result;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        for (unsigned int j = 0; j < STATE_DIM; ++j) {
            result.data[i][j] = col.data[i] * row.data[j];
        }
    }
    return result;
}


static Matrix matrix_multiply(Matrix A, Matrix B) {
    Matrix C;
    for (unsigned int i = 0; i < STATE_DIM; i++) {
        for (unsigned int j = 0; j < STATE_DIM; j++) {
            C.data[i][j] = 0;
            for (int k = 0; k < STATE_DIM; k++) {
                C.data[i][j] += A.data[i][k] * B.data[k][j];
            }
        }
    }
    return C;
}

static Matrix matrix_transpose(Matrix A){
    Matrix result;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        for (unsigned int j = 0; j < STATE_DIM; ++j) {
            result.data[i][j] = A.data[j][i];
        }
    }
    return result;
}

static Vector_row vector_matrix_multiplication(Vector_row v, Matrix M) {
    Vector_row result;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        float sum = 0;
        for (unsigned int j = 0; j < STATE_DIM; ++j) {
            sum += v.data[j] * M.data[i][j];
        }
        result.data[i] = sum;
    }
    return result;
}


static Vector_col vector_transpose(Vector_row v) {
    Vector_col result;
    for (unsigned int i = 0; i < STATE_DIM; i++) {
        result.data[i] = v.data[i];
    }
    return result;
}

static Matrix matrix_substract(Matrix a, Matrix b){
    Matrix result;
    for (unsigned int i = 0; i < STATE_DIM; ++i) {
        for (unsigned int j = 0; j < STATE_DIM; ++j) {
            result.data[i][j] = a.data[i][j] - b.data[i][j];
        }
    }
    return result;
}

float poly_eval_horner(const float * const p, size_t N, float x)
{
    float s = 0.0f;
    for(size_t i = 0; i < N ; ++i){
        s = s*x + p[i];
    }
    return s;
}

static Matrix eye_matrix(){
    Matrix res = {
        .data = {
            {1, 0, 0},
            {0, 1, 0},
            {0, 0, 1}
        }
    };
    return res;
}



static void EKF_predict(Vector_col* x, Matrix* P, float battery_current) {
    *x = vector_addition(matrix_vector_multiply(A, *x), vector_scalar_multiplication(B, battery_current));
    *P = matrix_addition(matrix_multiply(matrix_multiply(A, *P), matrix_transpose(A)), Q);
}


static void EKF_correction(Vector_col* x, Matrix* P, float battery_voltage, float battery_current, bool charging){
    float V_ocv = poly_eval_horner(BATT_OCV_POLY, BATT_OCV_POLY_COEF_COUNT, x->data[0]);

    float V_drop = vector_dot_product(C,*x) + D * battery_current;

    float V_batt_model = V_ocv - V_drop;

    float d_ocv_d_soc = poly_eval_horner(BATT_D_OCV_POLY, BATT_D_OCV_POLY_COEF_COUNT, x->data[0]);

    Vector_row H = {
        .data = {d_ocv_d_soc, C.data[1], C.data[2]}
    };

    float innovation = battery_voltage - V_batt_model;

    float S = vector_dot_product(vector_matrix_multiplication(H, *P), vector_transpose(H)) + R + R_charge * charging;

    float inv_S = 1.0f / S;

    Vector_col K = vector_scalar_multiplication(matrix_vector_multiply(*P, vector_transpose(H)), inv_S);

    *x = vector_addition(*x, vector_scalar_multiplication(K, innovation));

    *P = matrix_multiply(matrix_substract(eye_matrix(), vector_cross_product(K, H)), *P);
}


static inline float get_SoC_based_on_voltage(float voltage){
    float x = 0.5f;
    float x_prev = 0.0f;
    size_t i = 0;

    const float epsilon = 0.0001f;
    const size_t MAX_ITER = 20;

    while(fabsf(x - x_prev) > epsilon && i++ < MAX_ITER){ // Newton-Raphson method
        x_prev = x;
        float f = poly_eval_horner(BATT_OCV_POLY, BATT_OCV_POLY_COEF_COUNT, x) - voltage;
        float f_prime = poly_eval_horner(BATT_D_OCV_POLY, BATT_D_OCV_POLY_COEF_COUNT, x);
        x = x_prev - f / f_prime;
        x = fmaxf(0.0f, fminf(1.0f, x));
    }
    return x;
}


static inline float get_Voltage_based_on_SoC(float SoC){
    SoC = fmaxf(0.0f, fminf(1.0f, SoC));
    return poly_eval_horner(BATT_OCV_POLY, BATT_OCV_POLY_COEF_COUNT, SoC);
}


void EKF_init(Vector_col* x, Matrix* P){
    *x = (Vector_col) {
        .data = {0.98f, 0.0f, 0.0f}
    };

    *P = (Matrix) {
        .data = {
            {20.0f, 0, 0},
            {0, 2.0f, 0},
            {0, 0, 2.0f}
        }
    };
}


void EKF_update(Vector_col* x, Matrix* P, float battery_voltage, float battery_current, bool charging){
    EKF_predict(x, P, battery_current);
    EKF_correction(x, P, battery_voltage, battery_current, charging);
    x->data[0] = fmaxf(fminf(x->data[0], 1.0f), 0.0f);
}


float EKF_get_SoC(const Vector_col *x){
    return x->data[0];
}


void EKF_set_SoC_based_on_voltage(Vector_col* x, float voltage){
    x->data[0] = get_SoC_based_on_voltage(voltage);
}


void EKF_set_SoC(Vector_col* x, float soc){
    x->data[0] = fmaxf(fminf(soc, 1.0f), 0.0f);
}
