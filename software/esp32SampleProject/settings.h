#ifndef _SETTINGS__H_
#define _SETTINGS__H_
#pragma once

#include "bq76920.h"

class settings {
  public:
    // number of cells info
    const uint8_t enabled_cells = 0b00010111;
    const uint8_t max_number_of_cells = 5; // total number supported by the cip
    const uint8_t number_of_cells = 4; // actual number of used cells

    // current sense and protection
    const uint8_t current_sense_resistor = 1; //1mohms
    const bq76920::threshold current_protection_range = bq76920::threshold_lower;
    const bq76920::short_circuit_delay_us current_protection_scd_delay  = bq76920::scd_400_us;
    const bq76920::short_circuit_discharge_mv current_protection_scd_mv = bq76920::scd_155_78_mv;
    const bq76920::over_current_delay_ms current_protection_ocd_delay = bq76920::ocd_1280_ms;
    const bq76920::over_current_discharge_mv current_protection_ocd_mv = bq76920::ocd_17_8_mv;

    // over and under voltage settings
    const bq76920::under_voltage_delay_s cell_uv_delay = bq76920::uvd_8_s;
    const uint8_t cell_uv_limit = 0xE0;
    const float cell_uv_shutdown_limit = 2.500;
    const bq76920::over_voltage_delay_s  cell_ov_delay = bq76920::ovd_1_s;
    const uint8_t cell_ov_limit = 0xB0;

    // charge / discharge detection algorithm
    const float charge_discharge_ch_threshold = 0.050;
    const uint8_t charge_discharge_ch_limit = 3;
    const float charge_discharge_disch_threshold = -0.050;
    const uint8_t charge_discharge_disch_limit = 3;

    // temperature sensing settings


    // software limit settings
    const float minCellValue = 3.000;
    const float maxCellValue = 4.100;
    
};

#endif
