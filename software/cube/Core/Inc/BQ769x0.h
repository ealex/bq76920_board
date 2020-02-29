/*
 * BQ769x0.h
 *
 *  Created on: Feb 29, 2020
 *      Author: rottten
 */

#ifndef INC_BQ769X0_H_
#define INC_BQ769X0_H_

#include "stm32l0xx.h"


// exported structures
typedef enum {
  threshold_lower,
  threshold_upper
} threshold;

typedef enum {
  scd_44_22_mv,
  scd_67_33_mv,
  scd_89_44_mv,
  scd_111_56_mv,
  scd_133_67_mv,
  scd_155_78_mv,
  scd_178_89_mv,
  scd_200_100_mv
}short_circuit_discharge_mv;

typedef enum {
  scd_70_us,
  scd_100_us,
  scd_200_us,
  scd_400_us
}short_circuit_delay_us;

typedef enum {
  ocd_8_ms,
  ocd_20_ms,
  ocd_40_ms,
  ocd_80_ms,
  ocd_160_ms,
  ocd_320_ms,
  ocd_640_ms,
  ocd_1280_ms,
}over_current_delay_ms;

typedef enum {
  ocd_17_8_mv,
  ocd_22_11_mv,
  ocd_28_14_mv,
  ocd_33_17_mv,
  ocd_39_19_mv,
  ocd_44_22_mv,
  ocd_50_25_mv,
  ocd_56_28_mv,
  ocd_61_31_mv,
  ocd_67_33_mv,
  ocd_72_36_mv,
  ocd_78_39_mv,
  ocd_83_42_mv,
  ocd_89_44_mv,
  ocd_94_47_mv,
  ocd_100_50_mv
}over_current_discharge_mv;

typedef enum {
  uvd_1_s,
  uvd_4_s,
  uvd_8_s,
  uvd_16_s
} under_voltage_delay_s;

typedef enum {
  ovd_1_s,
  ovd_2_s,
  ovd_4_s,
  ovd_8_s
} over_voltage_delay_s;

typedef enum {
  balance_none,
  balance_c0,
  balance_c1,
  balance_c2,
  balance_c3,
  balance_c4
} balancing_output;

typedef enum {
	error_ext_alert,
	error_uv,
	error_ov,
	error_scd,
	error_ocd,
	error_all,
	error_none
} error_control;

typedef struct {
	uint16_t cells[15];
	uint16_t total_voltage;
	int32_t die_temperature;
	int16_t system_current;
	uint8_t status_reg;
	uint16_t inst_power;
	uint16_t total_power;
	uint16_t average_power;
	uint16_t uv_limit_actual;
	uint16_t ov_limit_actual;
} condensed_afe_data;

typedef struct {
	// bit mask of active cells
	uint16_t enabled_cells;

	// current sense configuration
	threshold range;
	short_circuit_delay_us sc_delay;
	short_circuit_discharge_mv sc_voltage;
	over_current_delay_ms oc_delay;
	over_current_discharge_mv oc_voltage;
	uint16_t shuntValue;
	int16_t chargeCurrent_mA;

	// voltage sense configuration
	under_voltage_delay_s uv_delay;
	uint8_t uvLimit;
	over_voltage_delay_s  ov_delay;
	uint8_t ovLimit;
} afe_config;



// exported functions
uint8_t bqInit(I2C_TypeDef *I2Cx, condensed_afe_data * afeData, afe_config *config);
uint8_t bqAct(void);
void bqDisableAll(void);
void bqEnableAll(void);
void bqBalance(void);

#endif /* INC_BQ769X0_H_ */
