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


static int32_t adcOffset;
static uint32_t adcGain;
static condensed_afe_data * data;
static afe_config * config;
static uint8_t afeStatus=0;

static volatile uint32_t ticks;

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

	// reset data register
	data->status_reg = 0;
	data->balStatus = 0;
	data->balTarget = 0;

	// read calibration data
	adcOffset = (int32_t) readRegister(ADCOFFSET);  // convert from 2's complement
	adcGain = (uint32_t)365+(uint32_t)((readRegister(ADCGAIN1)&(uint8_t)0b00001100)<<(uint8_t)1)
			+(uint32_t)((readRegister(ADCGAIN2)&(uint8_t)11100000)>>(uint8_t)5);

	// now apply all settings
	setCurrentProtection(config->range,
			config->sc_delay, config->sc_voltage,
			config->oc_delay, config->oc_voltage);
	setOvUvProtection(config->uv_delay, config->uvLimit, config->ov_delay, config->ovLimit);

	config->cell_max_voltage = getRealOv();
	config->cell_min_voltage = getRealUv();

	// prepare SysTick
	ticks = 0;
	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk;

	return 1;
}

/**
 *	@brief	This function updates the data from the AFE
 *	@retval	(uint8_t)1 if the system needs to pay attention to the AFE, 0 otherwise
 */
uint8_t bqAct(void) {
	//uint8_t retVal = 0x00;
	uint8_t tempVal;
	// get AFE status and reset all flags
	tempVal = readRegister(SYS_STAT);
	writeRegister(SYS_STAT,0b10111111);

	afeStatus = afeStatus | (0b00001111&tempVal);

	// fast act loop
#if 0
	if(0b00001111 & tempVal) {
		// OV, UV , OC , SCD reaction
		bqDisableAll();
	}
#endif

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
	data->outStatus = 0x00;
}

void bqEnableAll(void) {
	uint8_t tmp;
	tmp = readRegister(SYS_CTRL2);
	tmp = tmp | 0b00000011;
	writeRegister(SYS_CTRL2, tmp);
	data->outStatus = 0x01;
}

void bqResetStatus(void) {
	afeStatus = 0x00;
}

void bqBalance(void) {
	if(1==data->balStatus) {
		if(0!=data->balTarget) {
			// target is already set
			uint8_t selected_cell = 0xFF;
			uint16_t selectedCellVoltage = 0x00;
			// pick the highest cell and discharge it
			for(uint8_t cnt=0;cnt<15;cnt++) {
				if(config->enabled_cells&(1<<cnt)) {
					if(data->cells[cnt]>data->balTarget) {
						if(data->cells[cnt] > selectedCellVoltage ) {
							selected_cell=cnt;
							selectedCellVoltage = data->cells[cnt];
						}
					}
				}
			}
			if(0xFF==selected_cell) {
				// no more cells
				writeRegister(CELLBAL1, 0x00);
				writeRegister(CELLBAL2, 0x00);
				writeRegister(CELLBAL3, 0x00);
				data->balTarget = 0x00;
				data->balStatus = 0x00;
			} else {
				// enable balance for selected cell
				if(5>selected_cell) {	// cells 0,1,2,3,4
					writeRegister(CELLBAL1, (1<<selected_cell));
				} else if (10>selected_cell) { // cells 5,6,7,8,9
					writeRegister(CELLBAL2, (1<<(selected_cell-5)));
				} else { // cells 10,11,12,13,14
					writeRegister(CELLBAL3, (1<<(selected_cell-10)));
				}
			}
		} else {
			uint16_t minCell = 0xFFFF;
			// determine the target
			for(uint8_t cnt=0;cnt<15;cnt++) {
				if(config->enabled_cells&(1<<cnt)) {
					if(data->cells[cnt]<minCell) {
						minCell = data->cells[cnt];
					}
				}
			}
			// picked up the target, loop next time
			data->balTarget = minCell+1; // 1mV over the minimum cell
		}
	} else {
		writeRegister(CELLBAL1, 0x00);
		writeRegister(CELLBAL2, 0x00);
		writeRegister(CELLBAL3, 0x00);
	}
}

static void processDataRegisters(void) {
	data->status_reg = afeStatus;

	// cell voltage
	for(uint8_t cnt=0; cnt<15;cnt++) {
		if(0==(config->enabled_cells&(1<<cnt))) {
			data->cells[cnt] = 0;
		} else {
			data->cells[cnt] = convertCellVoltage(cnt);
		}
	}
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

	// instant power
	data->inst_power = (int16_t)(((int32_t)data->total_voltage*(int32_t)data->system_current)/1000);

	// get SysTick data and determine current power share, add it to the energy register
	uint32_t localTicks = ticks;
	ticks = 0;
#define TICKS_PER_HOUR	((int64_t)3600*1000);
	// compute Wh
	int64_t temp = (int32_t)data->total_voltage*(int32_t)data->system_current; // get instant power in uW
	temp = (temp*(int32_t)localTicks) / TICKS_PER_HOUR;
	data->total_power += temp;
}

static uint16_t convertCellVoltage(uint8_t cellIndex) {
	uint8_t high;
	uint8_t low;
	high = afeRawData[cellIndex*2];
	low = afeRawData[(cellIndex*2)+1];
	uint16_t rawAdcValue = ((uint16_t)(high<<8) | (uint16_t)low) & 0x3FFF;
	uint16_t outData = (uint16_t)((((uint32_t)adcGain * (uint32_t)rawAdcValue) + (uint32_t)(adcOffset*1000))/1000);
	return outData;
}

static uint16_t convertPackVolage(void) {
	// V (BAT) = 4 x GAIN x ADC(cell) + (#Cells x OFFSET)
	// GAIN is stored in units of μV/LSB, while OFFSET is stored in mV units.
	uint8_t high;
	uint8_t low;
	high = afeRawData[BAT_HI_BYTE-VC1_HI_BYTE];
	low = afeRawData[BAT_LO_BYTE-VC1_HI_BYTE];
	uint16_t rawAdcValue = (uint16_t)((uint16_t)high<<(uint8_t)8) | (uint16_t)low;
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
	reg |= range;
	reg |= sc_delay;
	reg |= sc_voltage;
	writeRegister(PROTECT1, reg);

	reg = readRegister(PROTECT2) & 0b10000000;
	reg |= oc_delay;
	reg |= oc_voltage;
	writeRegister(PROTECT2, reg);
}

static void setOvUvProtection(under_voltage_delay_s uv_delay, uint8_t uvLimit, over_voltage_delay_s  ov_delay, uint8_t ovLimit) {
	uint8_t reg = readRegister(PROTECT3) & 0b00001111;
	reg |= uv_delay;
	reg |= ov_delay;
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

void bqHandler(void) {
	ticks++;
}
