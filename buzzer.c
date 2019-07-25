/*
 * buzzer.c
 *
 *  Created on: 2019��7��25��
 *      Author: Rookie
 */

#include "buzzer.h"

/*
 * ��ʼ��
 */
void buzzerInit()
{
	P9SEL &= ~BIT6;   //��ΪIO��
	P9DIR |= BIT6;   //��Ϊ���
}

void beep()
{
//	long int i = 100000;
	P9OUT |= BIT6;
//	while(i--);
	__delay_cycles(500000);//�ӳ�10ms
	P9OUT &= ~BIT6;
}
