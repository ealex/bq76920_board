/*
 * BQ769x0.c
 *
 *  Created on: Feb 29, 2020
 *      Author: rottten
 */
#include "stm32l0xx_ll_i2c.h"
#include "BQ769x0.h"
#include "registers.h"


#define I2C_ADDRESS ((uint32_t)2*(0x18))
//#define TX_B_SIZE	64
#define RX_B_SIZE	64
static uint8_t afeRawData[RX_B_SIZE];
//static uint8_t i2cTxB[TX_B_SIZE];
static I2C_TypeDef * bqI2C;

static uint8_t bqSendData(uint8_t addr, uint8_t *buffer, uint8_t count);
static uint8_t bqReadData(uint8_t addr, uint8_t *buffer, uint8_t count);
static uint8_t writeRegister(uint8_t reg, uint8_t data);
static uint8_t readRegister(uint8_t reg);
static void setCurrentProtection(threshold range,
        short_circuit_delay_us sc_delay, short_circuit_discharge_mv sc_voltage,
        over_current_delay_ms oc_delay, over_current_discharge_mv oc_voltage );
static void setOvUvProtection(under_voltage_delay_s uv_delay, uint8_t uvLimit, over_voltage_delay_s  ov_delay, uint8_t ovLimit);
static void processDataRegisters(void);
static uint16_t convertCellVoltage(uint8_t cellIndex);
static uint16_t convertPackVolage(void);
static int16_t convertPackCurrent(void);
static int32_t convertPackDieTS1(void);
static uint16_t getRealOv(void);
static uint16_t getRealUv(void);


static uint32_t adcOffset;
static uint32_t adcGain;
static condensed_afe_data * data;
static afe_config * config;
static uint8_t afeStatus=0;

/**
 * @brief	this will start the BQ769x0 chip and check it's present
 * @param	I2Cx - the I2C peripheral, already initialized by the user
 * @retval	(uint8_t)1 if OK, (uint8_t)0 if not
 */
uint8_t bqInit(I2C_TypeDef *I2Cx, condensed_afe_data * afeData, afe_config *afeConfig) {
	bqI2C = I2Cx;
	data = afeData;
	config = afeConfig;

	// check if the chip is there
	if(0==writeRegister(CC_CFG, 0x19)) {
		return 0;
	}
	if(0x19!=readRegister(CC_CFG)) {
		return 0;
	}

	// run the initial configuration of the BQ chip
	writeRegister(CELLBAL1, 0x00);
	writeRegister(CELLBAL2, 0x00);
	writeRegister(CELLBAL3, 0x00);
	writeRegister(SYS_CTRL1,0b00010000);
	writeRegister(SYS_CTRL2,0b01000000);

	// read calibration data
	adcOffset = (signed int) readRegister(ADCOFFSET);  // convert from 2's complement
	adcGain = 365 + (((readRegister(ADCGAIN1) & 0b00001100) << 1) |
	  ((readRegister(ADCGAIN2) & 0b11100000) >> 5)); // uV/LSB

	// now apply all settings
	setCurrentProtection(config->range,
			config->sc_delay, config->sc_voltage,
			config->oc_delay, config->oc_voltage);
	setOvUvProtection(config->uv_delay, config->uvLimit, config->ov_delay, config->ovLimit);

	data->ov_limit_actual = getRealOv();
	data->uv_limit_actual = getRealUv();
	return 1;
}

/**
 *	@brief	This function updates the data from the AFE
 *	@retval	(uint8_t)1 if the system needs to pay attention to the AFE, 0 otherwise
 */
uint8_t bqAct(void) {
	uint8_t retVal = 0x00;
	uint8_t tempVal;
	// get AFE status and reset all flags
	tempVal = readRegister(SYS_STAT);
	writeRegister(SYS_STAT,0b10111111);

	afeStatus = afeStatus | (0b00001111&tempVal);

	// fast act loop
	if(0b00001111 & tempVal) {
		// OV, UV , OC , SCD reaction
		bqDisableAll();
	}

	if(0b10000000 & tempVal) {
		// read all data registers and process them
		bqReadData(VC1_HI_BYTE,afeRawData,(CC_LO_BYTE-VC1_HI_BYTE)+1);
		processDataRegisters();
	}

	if(afeStatus) {
		return 1;
	} else {
		return 0;
	}
}

void bqDisableAll(void) {
	uint8_t tmp;
	tmp = readRegister(SYS_CTRL2);
	tmp = tmp & 0b11111100;
	writeRegister(SYS_CTRL2, tmp);
}

void bqEnableAll(void) {
	uint8_t tmp;
	tmp = readRegister(SYS_CTRL2);
	tmp = tmp | 0b00000011;
	writeRegister(SYS_CTRL2, tmp);
}

void bqBalance(void) {
	writeRegister(CELLBAL1, 0x00);
	writeRegister(CELLBAL2, 0x00);
	writeRegister(CELLBAL3, 0x00);
}

static void processDataRegisters(void) {
	data->status_reg = afeStatus;

	// cell voltage
	data->cells[0] = convertCellVoltage(0);
	data->cells[1] = convertCellVoltage(1);
	data->cells[2] = convertCellVoltage(2);
	data->cells[3] = convertCellVoltage(3);
	data->cells[4] = convertCellVoltage(4);
	data->cells[5] = convertCellVoltage(5);
	data->cells[6] = convertCellVoltage(6);
	data->cells[7] = convertCellVoltage(7);
	data->cells[8] = convertCellVoltage(8);
	data->cells[9] = convertCellVoltage(9);
	data->cells[10] = convertCellVoltage(10);
	data->cells[11] = convertCellVoltage(11);
	data->cells[12] = convertCellVoltage(12);
	data->cells[13] = convertCellVoltage(13);
	data->cells[14] = convertCellVoltage(14);

	// total voltage
	data->total_voltage=convertPackVolage();

	// current
	data->system_current = convertPackCurrent();
	if((data->system_current>0)&&(data->system_current>config->chargeCurrent_mA)) {
		// over current charge protection;
		afeStatus |= 0b11000000;
		bqDisableAll();
	}
	//ts1
	data->die_temperature = convertPackDieTS1();
}

static uint16_t convertCellVoltage(uint8_t cellIndex) {
	if(0==(config->enabled_cells&(1<<cellIndex))) {
		return 0;
	} else {
		uint8_t high;
		uint8_t low;
		high = afeRawData[cellIndex*2];
		low = afeRawData[(cellIndex*2)+1];
		uint16_t rawAdcValue = ((uint16_t)(high<<8) | (uint16_t)low) & 0x3FFF;
		uint16_t outData = (uint16_t)((((uint32_t)adcGain * (uint32_t)rawAdcValue) + (uint32_t)(adcOffset*1000))/1000);
		return outData;
	}
}

static uint16_t convertPackVolage(void) {
	// V (BAT) = 4 x GAIN x ADC(cell) + (#Cells x OFFSET)
	// GAIN is stored in units of μV/LSB, while OFFSET is stored in mV units.
	uint8_t high;
	uint8_t low;
	high = afeRawData[BAT_HI_BYTE-VC1_HI_BYTE];
	low = afeRawData[BAT_LO_BYTE-VC1_HI_BYTE];
	uint16_t rawAdcValue = (uint16_t)(high<<8) | (uint16_t)low;
	uint16_t outData = (uint16_t)(((uint32_t)4*(uint32_t)adcGain*(uint32_t)rawAdcValue + ((uint32_t)4*adcOffset*1000))/(uint32_t)1000);
	return outData;
}

static int16_t convertPackCurrent(void) {
	uint8_t high;
	uint8_t low;
	high = afeRawData[CC_HI_BYTE-VC1_HI_BYTE];
	low = afeRawData[CC_LO_BYTE-VC1_HI_BYTE];
	int16_t rawAdcValue = (uint16_t)(high<<8) | (uint16_t)low;
	int16_t outData = (int16_t)((((int32_t)rawAdcValue*(int32_t)844))/((int32_t)100*(int32_t)config->shuntValue));
	return outData;
}

static int32_t convertPackDieTS1(void) {
	uint8_t high;
	uint8_t low;
	high = afeRawData[TS1_HI_BYTE-VC1_HI_BYTE];
	low = afeRawData[TS1_LO_BYTE-VC1_HI_BYTE];
	uint16_t rawAdcValue = ((uint16_t)(high<<8) | (uint16_t)low) & 0x3FFF;
	int32_t vtsx = rawAdcValue * 382; //uV
	int32_t temp = (int32_t)((int32_t)25000 - ((int32_t)vtsx-(int32_t)1200000) /(int32_t) 4);
	return temp;
}

static uint16_t getRealOv(void) {
	uint8_t raw = readRegister(OV_TRIP);
	uint16_t val =(uint16_t)((((uint32_t)(raw<<4)|(uint32_t)(1<<13))*(uint32_t)adcGain+(uint32_t)(adcOffset*1000))/(uint32_t)1000);
	return val;
}

static uint16_t getRealUv(void) {
	uint8_t raw = readRegister(UV_TRIP);
	uint16_t val =(uint16_t)((((uint32_t)(raw<<4)|(uint32_t)(1<<12))*(uint32_t)adcGain+(uint32_t)(adcOffset*1000))/(uint32_t)1000);
	return val;
}


static void setCurrentProtection(threshold range,
        short_circuit_delay_us sc_delay, short_circuit_discharge_mv sc_voltage,
        over_current_delay_ms oc_delay, over_current_discharge_mv oc_voltage ) {

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
	writeRegister(PROTECT2, reg);
}

static void setOvUvProtection(under_voltage_delay_s uv_delay, uint8_t uvLimit, over_voltage_delay_s  ov_delay, uint8_t ovLimit) {
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

static uint8_t writeRegister(uint8_t reg, uint8_t data) {
	uint8_t buf[1];
	buf[0]=data;
	return bqSendData(reg,buf,1);
}

static uint8_t readRegister(uint8_t reg) {
	uint8_t buf[1]={0};
	bqReadData(reg,buf,1);
	return buf[0];
}

static uint8_t bqSendData(uint8_t addr, uint8_t *buffer, uint8_t count) {
	LL_I2C_HandleTransfer(bqI2C, I2C_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, (count+1)
			, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_WRITE );
	while((0==LL_I2C_IsActiveFlag_NACK(bqI2C))&&(0==LL_I2C_IsActiveFlag_TXIS(bqI2C)));
	if(1==LL_I2C_IsActiveFlag_TXIS(bqI2C)) {
		LL_I2C_TransmitData8(bqI2C, addr);
		for(uint8_t cnt=0;cnt<count;cnt++) {
			while(0==LL_I2C_IsActiveFlag_TXIS(bqI2C));
			LL_I2C_TransmitData8(bqI2C, buffer[cnt]);
		}
	} else {
		LL_I2C_ClearFlag_NACK(bqI2C);
		return 0x00;
	}
	return 1;
}

static uint8_t bqReadData(uint8_t addr, uint8_t *buffer, uint8_t count) {
	LL_I2C_HandleTransfer(bqI2C, I2C_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, 1, LL_I2C_MODE_SOFTEND, LL_I2C_GENERATE_START_WRITE );
	while((0==LL_I2C_IsActiveFlag_NACK(bqI2C))&&(0==LL_I2C_IsActiveFlag_TXIS(bqI2C)));
	if(1==LL_I2C_IsActiveFlag_TXIS(bqI2C)) {
		LL_I2C_TransmitData8(bqI2C, addr);
	} else {
		return 0;
	}

	LL_I2C_HandleTransfer(bqI2C, I2C_ADDRESS, LL_I2C_ADDRSLAVE_7BIT, count, LL_I2C_MODE_AUTOEND, LL_I2C_GENERATE_START_READ );
	while((0==LL_I2C_IsActiveFlag_NACK(bqI2C))&&(0==LL_I2C_IsActiveFlag_RXNE(bqI2C)));
	if(1==LL_I2C_IsActiveFlag_RXNE(bqI2C)) {
		for(uint8_t cnt=0; cnt<count;cnt++) {
			while(0==LL_I2C_IsActiveFlag_RXNE(bqI2C));
			buffer[cnt]=LL_I2C_ReceiveData8(bqI2C);
		}
	} else {
		return 0;
	}
	return 1;
}
