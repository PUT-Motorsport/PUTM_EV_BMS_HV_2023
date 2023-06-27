#ifndef LTC_STACK_H
#define LTC_STACK_H

#include "main.h"




#define LTCS_IN_STACK	15
#define CELLS_IN_LTC	9

#define LTC_ADC_MD		0b11
#define LTC_ADC_DCP		0b0
#define LTC_CFG_REFON	0b1
#define LTC_CFG_ADCOPT	0b1
#define LTC_CFG_GPIO	0b11111

#define LTC_REFRESH_PERIOD	50
#define LTC_ADC_DELAY	8

#define CELL_VOLTAGE_MIN	3000
#define CELL_VOLTAGE_MAX	4180
#define CELL_TEMPERATURE_MIN	40
#define CELL_TEMPERATURE_MAX	550
#define CELL_TEMPERATURE_CHARGING_MAX	410

#define CELL_VOLTAGE_ERR_CNTR_THRESHOLD		9
#define CELL_CURRENT_ERR_CNTR_THRESHOLD		9
#define CELL_TEMPERATURE_ERR_CNTR_THRESHOLD	19

#define CELL_ERROR_VOLTAGE_FLAG			0x01
#define CELL_ERROR_TEMPERATURE_FLAG		0x02
#define CELL_ERROR_CURRENT_FLAG		0x04

#define LTC_BALANCE_ROUND_PERIOD	60000

struct stack_data_type{
	// measurements
	uint16_t voltages[9 * LTCS_IN_STACK];
	int16_t temperatures[3 * LTCS_IN_STACK];
	// summary
	uint32_t total_voltage_mv;
	int16_t temperature_max;
	uint16_t cell_minimum_voltage;
	// discharge
	uint8_t discharge[9 * LTCS_IN_STACK];
	// errors
	uint8_t voltages_err_cntr[9 * LTCS_IN_STACK];
	uint8_t temperatures_err_cntr[9 * LTCS_IN_STACK];
	uint8_t current_err_cntr;
	uint8_t error;
	// measurement time
	uint32_t data_refresh_tick;
	// minimum cell
	int minimum_cell_no;
	// balancing
	uint8_t balance_activation_flag;
};

void LtcInitPec15Table();

uint16_t LtcPec15(uint8_t *data , int len);

void LtcInit(SPI_HandleTypeDef *hspi, GPIO_TypeDef *cs_gpio, uint16_t cs_pin);

void LtcCommunicationThread();

void LtcWakeupSleep();

void LtcWakeupIdle();

void LtcTxCallback();

void LtcCsPinSet(uint8_t pin_state);

void LtcSendConfig(uint8_t discharge_activation);

void LtcStartAdcCell();

void LtcStartAdcGpio();

void LtcStartReadCell(uint8_t group);

void LtcStartReadGpio(uint8_t group);

void LtcReadCell(uint8_t group);

void LtcReadGpio(uint8_t group);

void LtcStackDataReorder();

int16_t LtcCalculateTemperature(uint16_t gpio_voltage);

void LtcErrorCheck();

uint8_t LtcGetStackError();

void LtcStackSummary();

void LtcClearCellAdc();

void LtcClearGpioAdc();

void LtcStackBalance();



#endif



