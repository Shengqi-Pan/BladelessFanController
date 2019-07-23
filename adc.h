/*
 * adc.h
 *
 *  Created on: 2019��7��21��
 *      Author: Rookie
 *      ADת�����롤
 */

#ifndef ADC_H_
#define ADC_H_

#include <msp430f5438A.h>
void ADS7950_PORT_Init(void);
unsigned int ADS7950_ReadResultAndSetNextSample(unsigned int uiSendData);
unsigned int ADS7950GetPressure(void);

#endif /* ADC_H_ */
