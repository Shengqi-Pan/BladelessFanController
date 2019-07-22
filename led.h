/*
 * led.h
 *
 *  Created on: 2019��7��22��
 *      Author: Rookie
 */

#ifndef LED_H_
#define LED_H_

#include <msp430.h>

//��ʼ��
void ledInit();
//����index�±��LED
void ledLight(unsigned char index);
//Ϩ������LED
void ledExtinguishAll();
//����LED��ʾ������Ϊ��ǰ�±������
void ledUpdate(unsigned char index);
void ledShow();

#endif /* LED_H_ */
