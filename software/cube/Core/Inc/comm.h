/*
 * comm.h
 *
 *  Created on: Mar 1, 2020
 *      Author: rottten
 */

#ifndef INC_COMM_H_
#define INC_COMM_H_

#include "stm32l0xx.h"
#include "stm32l0xx_ll_usart.h"
#include "BQ769x0.h"

void commInit(USART_TypeDef *USARTx, condensed_afe_data * afeData, afe_config *afeConfig);
void commAct(void);

#endif /* INC_COMM_H_ */
