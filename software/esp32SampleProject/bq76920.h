#ifndef BQ76920_H
#define BQ76920_H

#define BQ76920_DEBUG 1


class bq76920 {
  public:
    typedef enum {
      E_OK  = 0x00,
      E_ERROR
    }error_codes;

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
      float cells[5];
      uint8_t enabled_cells;
      float total_voltage;
      float die_temperature;
      float system_current;
      uint8_t status_reg;
      float inst_power;
      float total_power;
      float average_power;
      float uv_limit_actual;
      float ov_limit_actual;
    } condensed_afe_data;
    
    // class constructor
    bq76920(uint8_t i2cAddress, boolean crc);
    
    //checks that the chip is present and reads calibration data and other one time stuff
    error_codes init(byte alertPin, byte bootPin = -1, uint8_t i2cSda=21, uint8_t i2cScl=22, uint32_t i2cSpeed=100000);
    
    // returns the value of the SYS_STAT register
    uint8_t getStatus(void);

    // charging control
    void enableCharging(void);
    void disableCharging(void);

    // discharge control
    void enableDischarging(void);
    void disableDischarging(void);

    // protection configuration
    void setSenseResistor(uint16_t mOhms);
    void setCurrentProtection(threshold range, 
          short_circuit_delay_us sc_delay, short_circuit_discharge_mv sc_voltage,
          over_current_delay_ms oc_delay, over_current_discharge_mv oc_voltage );
    void setOvUvProtection(under_voltage_delay_s uv_delay, uint8_t uvLimit, over_voltage_delay_s  ov_delay, uint8_t ovLimit);
    float getUvLimitActual(void);
    float getOvLimitActual(void);
    void resetErrorCondition(error_control error);
    error_control getErrorCondition(void);
    
    // status read
    int32_t readCurrent(void);
    uint32_t readTotalVoltage(void);
    uint32_t readCellVolgate(uint8_t cell);
    int32_t readDieTemperature(void);

    condensed_afe_data readAllDataAtOnce(condensed_afe_data data);
    
    // balancingControl
    void enableBalancingPin(balancing_output balance);
    float computeInstPower(condensed_afe_data data);


    void shutDownBms(void);

    // helper functions
    const char *byte2char(int x);
    uint8_t readRegister(byte address);
    uint16_t readRegisters(byte address);
    
  private:

    // variables
    uint8_t chipI2CAddress;
    boolean CRC;
    static bq76920* instancePointer;
    uint32_t adcOffset;
    uint32_t adcGain;
    uint16_t shuntValue;
    
    // functions
    uint8_t crc8_ccitt_update (uint8_t inCrc, uint8_t inData);
    boolean readRegisters(byte address, uint8_t len, uint8_t * data);
    void writeRegister(byte address, int data);
};

#endif
