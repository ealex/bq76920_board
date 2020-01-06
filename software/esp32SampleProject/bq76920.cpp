#include <Arduino.h>
#include <Wire.h>     // I2C/TWI (for Battery Management IC)

#include "bq76920.h"
#include "registers.h"

// for the ISR to know the bq76920 instance
bq76920* bq76920::instancePointer = 0;



bq76920::bq76920(uint8_t i2cAddress, boolean crc) {
  chipI2CAddress = i2cAddress;
  CRC = crc;
}

bq76920::error_codes bq76920::init(byte alertPin, byte bootPin, uint8_t i2cSda, uint8_t i2cScl, uint32_t i2cSpeed) {
  pinMode(i2cSda, INPUT_PULLUP);
  pinMode(i2cScl, INPUT_PULLUP);
  Wire.begin(i2cSda, i2cScl); // 21 & 22 are default on ESP32
  Wire.setClock(i2cSpeed);

  // Boot IC if pin is defined (else: manual boot via push button has to be 
  // done before calling this method)
  if (bootPin >= 0)
  {
    pinMode(bootPin, OUTPUT);
    digitalWrite(bootPin, HIGH);
    delay(5);   // wait 5 ms for device to receive boot signal (datasheet: max. 2 ms)
    pinMode(bootPin, INPUT);     // don't disturb temperature measurement
    delay(10);  // wait for device to boot up completely (datasheet: max. 10 ms)
  }

  // TODO: IRQ for ALERT

  // test communication
  writeRegister(CC_CFG, 0x19);       // should be set to 0x19 according to datasheet
  if (readRegister(CC_CFG) == 0x19) {
    // write initial configuration
    writeRegister(CELLBAL1,0x00); // disable cell balancing 1-5
    writeRegister(CELLBAL2,0x00); // disable cell balancing 6-10
    writeRegister(CELLBAL3,0x00); // disable cell balancing 11-15
    writeRegister(SYS_CTRL1,0b00010000); // ADC enabled, report DIE temperature 
    writeRegister(SYS_CTRL2,0b01000000); // normal delay,CC on, CC continous, charge and discharge fets OFF

    // read calibration data
    adcOffset = (signed int) readRegister(ADCOFFSET);  // convert from 2's complement
    adcGain = 365 + (((readRegister(ADCGAIN1) & B00001100) << 1) | 
      ((readRegister(ADCGAIN2) & B11100000) >> 5)); // uV/LSB

    return bq76920::E_OK;
  } else {
    // TODO - throw error message
    return bq76920::E_ERROR;
  }
  
}


uint8_t bq76920::getStatus(void) {
  return readRegister(SYS_STAT);
}


void bq76920::enableCharging(void) {
  writeRegister(SYS_CTRL2, readRegister(SYS_CTRL2) | 0b00000001);
}


void bq76920::disableCharging(void) {
  writeRegister(SYS_CTRL2, readRegister(SYS_CTRL2) & 0b11111110);
}


void bq76920::enableDischarging(void) {
  writeRegister(SYS_CTRL2, readRegister(SYS_CTRL2) | 0b00000010);
}


void bq76920::disableDischarging(void) {
  writeRegister(SYS_CTRL2, readRegister(SYS_CTRL2) & 0b11111101);
}


void bq76920::setSenseResistor(uint16_t mOhms) {
  shuntValue = mOhms;
}


void bq76920::setCurrentProtection(threshold range, 
          short_circuit_delay_us sc_delay, short_circuit_discharge_mv sc_voltage,
          over_current_delay_ms oc_delay, over_current_discharge_mv oc_voltage ) {
  // this will overwrite protect1 and protect2 registers
  uint8_t reg = readRegister(PROTECT1) & 0b01100000;

  // range control
  switch(range) {
    case threshold_lower:
      break;
    case threshold_upper:
      reg |= 0b10000000; // SET RSNS high
      break;
  }

  switch(sc_delay) {
    case scd_70_us:
      break;
    case scd_100_us:
      reg |= 0b00001000;
      break;
    case scd_200_us:
      reg |= 0b00010000;
      break;
    case scd_400_us:
      reg |= 0b00011000;
      break;
  }

  switch(sc_voltage) {
    case scd_44_22_mv:
      break;
    case scd_67_33_mv:
      reg |= 0b00000001;
      break;
    case scd_89_44_mv:
      reg |= 0b00000010;
      break;
    case scd_111_56_mv:
      reg |= 0b00000011;
      break;    
    case scd_133_67_mv:
      reg |= 0b00000100;
      break;    
    case scd_155_78_mv:
      reg |= 0b00000101;
      break;    
    case scd_178_89_mv:
      reg |= 0b00000110;
      break;    
    case scd_200_100_mv:
      reg |= 0b00000111;
      break;
  }

  // done with PROTECT1
  writeRegister(PROTECT1, reg);

  reg = readRegister(PROTECT2) & 0b10000000;

  switch(oc_delay) {
    case ocd_8_ms:
      break;
    case ocd_20_ms:
      reg |= 0b00010000;
      break;
    case ocd_40_ms:
      reg |= 0b00100000;
      break;
    case ocd_80_ms:
      reg |= 0b00110000;
      break;
    case ocd_160_ms:
      reg |= 0b01000000;
      break;
    case ocd_320_ms:
      reg |= 0b01010000;
      break;
    case ocd_640_ms:
      reg |= 0b01100000;
      break;
    case ocd_1280_ms:
      reg |= 0b01110000;
      break;
  }

  switch(oc_voltage) {
    case ocd_17_8_mv:
      break;
    case ocd_22_11_mv:
      reg |= 0b00000001;
      break;
    case ocd_28_14_mv:
      reg |= 0b00000010;
      break;
    case ocd_33_17_mv:
      reg |= 0b00000011;
      break;
    case ocd_39_19_mv:
      reg |= 0b00000100;
      break;
    case ocd_44_22_mv:
      reg |= 0b00000101;
      break;
    case ocd_50_25_mv:
      reg |= 0b00000110;
      break;
    case ocd_56_28_mv:
      reg |= 0b00000111;
      break;
    case ocd_61_31_mv:
      reg |= 0b00001000;
      break;
    case ocd_67_33_mv:
      reg |= 0b00001001;
      break;
    case ocd_72_36_mv:
      reg |= 0b00001010;
      break;
    case ocd_78_39_mv:
      reg |= 0b00001011;
      break;
    case ocd_83_42_mv:
      reg |= 0b00001100;
      break;
    case ocd_89_44_mv:
      reg |= 0b00001101;
      break;
    case ocd_94_47_mv:
      reg |= 0b00001110;
      break;
    case ocd_100_50_mv:
      reg |= 0b00001111;
      break;
  }
  
  // done with PROTECT2
  writeRegister(PROTECT2, reg);
}


void bq76920::setOvUvProtection(under_voltage_delay_s uv_delay, uint8_t uvLimit, over_voltage_delay_s  ov_delay, uint8_t ovLimit) {
  uint8_t reg = readRegister(PROTECT3) & 0b00001111;

  switch(uv_delay) {
    case uvd_1_s:
      reg |= 00000000;
      break;
    case uvd_4_s:
      reg |= 01000000;
      break;
    case uvd_8_s:
      reg |= 10000000;
      break;
    case uvd_16_s: 
      reg |= 11000000;
      break;
  }

  switch(ov_delay) {
    case ovd_1_s:
     break;
    case ovd_2_s:
      reg |= 00010000;
      break;
    case ovd_4_s:
      reg |= 00100000;
      break;
    case ovd_8_s:
      reg |= 00110000;
      break;
  }

  writeRegister(PROTECT3, reg);
  writeRegister(UV_TRIP, uvLimit);
  writeRegister(OV_TRIP, ovLimit);
}


float bq76920::getUvLimitActual(void) {
  return (float)(((long)1 << 12 | readRegister(UV_TRIP) << 4) * adcGain / 1000 + adcOffset)/(float)1000;
  //return readRegister(UV_TRIP);
}


float bq76920::getOvLimitActual(void) {
  return (float)(((long)1 << 13 | readRegister(OV_TRIP) << 4) * adcGain / 1000 + adcOffset)/(float)1000;
  //return readRegister(OV_TRIP);
}

int32_t bq76920::readCurrent(void) {
  int16_t adcVal = readRegisters(CC_HI_BYTE);
  return(adcVal * 8.44 / shuntValue);  // mA
}

uint32_t bq76920::readTotalVoltage(void) {
  uint32_t adcVal = readRegisters(BAT_HI_BYTE);
  return(4.0 * adcGain * adcVal / 1000.0 + 4 * adcOffset);
}

uint32_t bq76920::readCellVolgate(uint8_t cell) {
  uint32_t adcVal = 0;
  switch(cell) {
    case 0:
      adcVal = 0x3FFF&readRegisters(VC1_HI_BYTE);
      break;
    case 1:
      adcVal = 0x3FFF&readRegisters(VC2_HI_BYTE);
      break;
    case 2:
      adcVal = 0x3FFF&readRegisters(VC3_HI_BYTE);
      break;
    case 3:
      adcVal = 0x3FFF&readRegisters(VC4_HI_BYTE);
      break;
    case 4:
      adcVal = 0x3FFF&readRegisters(VC5_HI_BYTE);
      break;
    default:
      return 0;
  }

  return(adcVal * adcGain / 1000 + adcOffset);
}

int32_t bq76920::readDieTemperature(void) {
  int32_t adcVal;
  int32_t vtsx;
  int32_t dieTemp;
  adcVal = ((readRegister(TS1_HI_BYTE)&0b00111111)<<8) | readRegister(TS1_LO_BYTE);
  vtsx = adcVal * 382; // mV
  dieTemp = (int)(1000*(float)(25 - (float)((((float)vtsx/1000000)-(float)1.200)/(float)0.0042)));
  return dieTemp;
}


void bq76920::enableBalancingPin(balancing_output balance) {
  uint8_t reg = readRegister(CELLBAL1) & 0b11100000;
  switch(balance) {
    case balance_none:
      break;
    case balance_c0:
      reg |=0b00000001;
      break;
    case balance_c1:
      reg |=0b00000010;
      break;
    case balance_c2:
      reg |=0b00000100;
      break;
    case balance_c3:
      reg |=0b00001000;
      break;
    case balance_c4:
      reg |=0b00010000;
      break; 
  }
  writeRegister(CELLBAL1, reg);
}


void bq76920::resetErrorCondition(error_control error) {
  uint8_t reg = readRegister(SYS_STAT);
  switch(error) {
      case error_ext_alert:
        reg = 0b00010000;
        break;
      case error_uv:
        reg = 0b00001000;
        break;
      case error_ov:
        reg = 0b00000100;
        break;
      case error_scd:
        reg = 0b00000010;
        break;
      case error_ocd:
        reg = 0b00000001;
        break;
      case error_all:
        reg = 0b10011111;
        break;
  }
  writeRegister(SYS_STAT, reg);
}
bq76920::error_control bq76920::getErrorCondition(void) {
  error_control retVal = error_none;
  uint8_t reg = readRegister(SYS_STAT);

  if(reg & 0b00010000) {
    retVal = error_ext_alert;
  } else if(reg & 0b00001000) {
    retVal = error_uv;
  } else if(reg & 0b00000100) {
    retVal = error_ov;
  } else if(reg & 0b00000010) {
    retVal = error_scd;
  } else if(reg & 0b00000001) {
    retVal = error_ocd;
  }
  return retVal;
}

void bq76920::shutDownBms(void) {
  writeRegister(SYS_CTRL1,0b00000001);
  writeRegister(SYS_CTRL1,0b00000010);
}


const char *bq76920::byte2char(int x) {
    static char b[9];
    b[0] = '\0';

    int z;
    for (z = 128; z > 0; z >>= 1)
    {
        strcat(b, ((x & z) == z) ? "1" : "0");
    }

    return b;
}

bq76920::condensed_afe_data bq76920::readAllDataAtOnce(condensed_afe_data data) {
    //condensed_afe_data data;
    
    if(0b00000001&data.enabled_cells) {
      data.cells[0] = (float)readCellVolgate(0)/1000.00;
    } else {
      data.cells[0] = (float)0;
    }
    if(0b00000010&data.enabled_cells) {
      data.cells[1] = (float)readCellVolgate(1)/1000.00;
    } else {
      data.cells[1] = (float)0;
    }
    
    if(0b00000100&data.enabled_cells) {
    data.cells[2] = (float)readCellVolgate(2)/1000.00;
    } else {
      data.cells[2] = (float)0;
    }

    if(0b00001000&data.enabled_cells) {
      data.cells[3] = (float)readCellVolgate(3)/1000.00;
    } else {
      data.cells[3] = (float)0;
    }

    if(0b00010000&data.enabled_cells) {
      data.cells[4] = (float)readCellVolgate(4)/1000.00;
    } else {
      data.cells[4] = (float)0;
    }
    
    data.system_current = (float)readCurrent()/1000.00;
    data.total_voltage = (float)readTotalVoltage()/1000.00;
    data.die_temperature = (float)readDieTemperature()/1000.00;
    data.status_reg = getStatus();
    
    return data;
}


float bq76920::computeInstPower(condensed_afe_data data) {
  if(0b10000000&&data.status_reg) {
    return data.system_current*data.total_voltage;
  } else {
    return 0;
  }
}




// PRIVATE FUNCTIONS

//----------------------------------------------------------------------------

uint8_t bq76920::crc8_ccitt_update (uint8_t inCrc, uint8_t inData)
{
    uint8_t   i;
    uint8_t   data;

    data = inCrc ^ inData;

    for ( i = 0; i < 8; i++ )
    {
        if (( data & 0x80 ) != 0 )
        {
            data <<= 1;
            data ^= 0x07;
        }
        else
        {
            data <<= 1;
        }
    }
    return data;
}


//----------------------------------------------------------------------------

void bq76920::writeRegister(byte address, int data)
{
  uint8_t crc = 0;
  Wire.beginTransmission(chipI2CAddress);
  Wire.write(address);
  Wire.write(data);
  if(true==CRC) {
    crc = crc8_ccitt_update(crc, (chipI2CAddress << 1) | 0);
        crc = crc8_ccitt_update(crc, address);
        crc = crc8_ccitt_update(crc, data);
    Wire.write(crc);
  } else {
    Wire.write(address);
    Wire.write(data);
  }
  Wire.endTransmission();
}

//----------------------------------------------------------------------------

uint8_t bq76920::readRegister(byte address)
{
  // TODO - optimize and check CRC
  uint8_t crc;
  uint8_t data;
  Wire.beginTransmission(chipI2CAddress);
  Wire.write(address);
  Wire.endTransmission();
  if(true==CRC) {
    Wire.requestFrom((uint8_t)chipI2CAddress, (uint8_t)2);
    data = Wire.read();
    crc = Wire.read();
  } else {
    Wire.requestFrom((uint8_t)chipI2CAddress, (uint8_t)1);
    data = Wire.read();
  }
  return data;
}

uint16_t bq76920::readRegisters(byte address) {
  uint8_t crc;
  uint16_t data;
  Wire.beginTransmission(chipI2CAddress);
  Wire.write(address);
  Wire.endTransmission();
  if(true==CRC) {
    Wire.requestFrom((uint8_t)chipI2CAddress, (uint8_t)4);
    data = Wire.read()<<8;
    Wire.read();
    data |= Wire.read();
    Wire.read();
  } else {
    Wire.requestFrom((uint8_t)chipI2CAddress, (uint8_t)2);
    data = Wire.read()<<8;
    data |= Wire.read();
  }
  return data;
}
