/*
 * comm.c
 *
 *  Created on: Mar 1, 2020
 *      Author: rottten
 */

#include "stm32l0xx_ll_usart.h"
#include "stm32l0xx_ll_utils.h"
#include "comm.h"
#include "BQ769x0.h"
#include "xprintf.h"

static condensed_afe_data * data;
static afe_config * config;
static USART_TypeDef * port;
static uint8_t commBuffer[128];

static void sendBuffer(uint8_t * buffer, uint8_t size);
static void sendText(uint8_t * buffer);

#define mmio32(x)   (*(volatile unsigned long *)(x))

void commInit(USART_TypeDef *USARTx, condensed_afe_data * afeData, afe_config *afeConfig) {
	port = USARTx;
	data = afeData;
	config = afeConfig;
	xsprintf((char*)commBuffer,"+++\r\n");
	sendText(commBuffer);
}

void commAct(void) {
	uint8_t inCh;
	if(LL_USART_IsActiveFlag_RXNE(port)) {
		inCh = LL_USART_ReceiveData8(port);
		switch(inCh) {
		case 'i': // info
			xsprintf((char*)commBuffer,"\r\n+\r\n");
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%04X%04X%04X\r\n",
					LL_GetUID_Word2(),LL_GetUID_Word1(),LL_GetUID_Word0());
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%u\r\n",config->pack_max_voltage);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%u\r\n",config->cell_bal_voltage);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%u\r\n",config->chargeCurrent_mA);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%u\r\n",config->cell_max_voltage);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%u\r\n",config->cell_min_voltage);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"*\r\n");
			sendText(commBuffer);
			break;
		case 's': // status
			xsprintf((char*)commBuffer,"\r\n+\r\n");
			for(int cnt=0;cnt<15;cnt++) {
				if(config->enabled_cells&(1<<cnt)) {
					xsprintf((char*)commBuffer,"%u:%u\r\n",cnt,data->cells[cnt]);
					sendText(commBuffer);
				}

			}
			xsprintf((char*)commBuffer,"%u\r\n",data->total_voltage);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%d\r\n",data->system_current);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%d\r\n",data->die_temperature);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%02X\r\n",data->status_reg);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%d\r\n",data->outStatus);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"%d %d\r\n",data->balStatus, data->balTarget);
			sendText(commBuffer);
			xsprintf((char*)commBuffer,"*\r\n");
			sendText(commBuffer);
			break;
		case 'e' : // enable
			bqEnableAll();
			xsprintf((char*)commBuffer,"*\r\n");
			sendText(commBuffer);
			break;
		case 'd' : // disable
			bqDisableAll();
			xsprintf((char*)commBuffer,"*\r\n");
			sendText(commBuffer);
			break;
		case 'r' : // reset
			bqResetStatus();
			xsprintf((char*)commBuffer,"*\r\n");
			sendText(commBuffer);
			break;
		case 'b' : // balance start
			data->balStatus = 1;
			xsprintf((char*)commBuffer,"*\r\n");
			sendText(commBuffer);
			break;
		default:
			break;
		}
	}
}

static void sendBuffer(uint8_t * buffer, uint8_t size) {
	for(uint8_t cnt=0; cnt < size; cnt++) {
		while(0==LL_USART_IsActiveFlag_TXE(port));
		LL_USART_TransmitData8(port, buffer[cnt]);
	}
	while(0==LL_USART_IsActiveFlag_TC(port));
}

static void sendText(uint8_t * buffer) {
	uint8_t cnt=0;
	while(0!=buffer[cnt]) {
		while(0==LL_USART_IsActiveFlag_TXE(port));
		LL_USART_TransmitData8(port, buffer[cnt]);
		cnt++;
	}
	while(0==LL_USART_IsActiveFlag_TC(port));
}

