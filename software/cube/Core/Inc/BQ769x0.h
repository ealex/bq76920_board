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
  threshold_lower = 0b00000000,
  threshold_upper = 0b10000000
} threshold;

typedef enum {
  scd_44_22_mv		= 0b00000000,
  scd_67_33_mv		= 0b00000001,
  scd_89_44_mv		= 0b00000010,
  scd_111_56_mv		= 0b00000011,
  scd_133_67_mv		= 0b00000100,
  scd_155_78_mv		= 0b00000101,
  scd_178_89_mv		= 0b00000110,
  scd_200_100_mv	= 0b00000111
}short_circuit_discharge_mv;

typedef enum {
  scd_70_us			= 0b00000000,
  scd_100_us 		= 0b00001000,
  scd_200_us 		= 0b00010000,
  scd_400_us		= 0b00011000
}short_circuit_delay_us;

typedef enum {
  ocd_8_ms			= 0b00000000,
  ocd_20_ms			= 0b00010000,
  ocd_40_ms			= 0b00100000,
  ocd_80_ms			= 0b00110000,
  ocd_160_ms		= 0b01000000,
  ocd_320_ms		= 0b01010000,
  ocd_640_ms		= 0b01100000,
  ocd_1280_ms		= 0b01110000
}over_current_delay_ms;

typedef enum {
  ocd_17_8_mv		= 0b00000000,
  ocd_22_11_mv		= 0b00000001,
  ocd_28_14_mv		= 0b00000010,
  ocd_33_17_mv		= 0b00000011,
  ocd_39_19_mv		= 0b00000100,
  ocd_44_22_mv		= 0b00000101,
  ocd_50_25_mv		= 0b00000110,
  ocd_56_28_mv		= 0b00000111,
  ocd_61_31_mv		= 0b00001000,
  ocd_67_33_mv		= 0b00001001,
  ocd_72_36_mv		= 0b00001010,
  ocd_78_39_mv		= 0b00001011,
  ocd_83_42_mv		= 0b00001100,
  ocd_89_44_mv		= 0b00001101,
  ocd_94_47_mv		= 0b00001110,
  ocd_100_50_mv		= 0b00001111
}over_current_discharge_mv;

typedef enum {
  uvd_1_s			= 0b00000000,
  uvd_4_s			= 0b01000000,
  uvd_8_s			= 0b10000000,
  uvd_16_s			= 0b11000000
} under_voltage_delay_s;

typedef enum {
  ovd_1_s			= 0b00000000,
  ovd_2_s			= 0b00010000,
  ovd_4_s			= 0b00100000,
  ovd_8_s			= 0b00110000
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
	int32_t inst_power;
	//int64_t total_power;
	uint16_t average_power;
	uint8_t balStatus;
	uint16_t balTarget;
	uint8_t outStatus;
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

	// general pack settings
	uint16_t pack_max_voltage;
	uint16_t pack_max_current;
	uint16_t cell_max_voltage;
	uint16_t cell_min_voltage;
	uint16_t cell_bal_voltage;
} afe_config;



// exported functions
uint8_t bqInit(I2C_TypeDef *I2Cx, condensed_afe_data * afeData, afe_config *config);
uint8_t bqAct(void);
void bqDisableAll(void);
void bqEnableAll(void);
void bqResetStatus(void);
void bqBalance(void);

void bqHandler(void);

#endif /* INC_BQ769X0_H_ */
