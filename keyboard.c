/*
 * keyboard.c
 *
 *  Created on: 2019��7��22��
 *      Author: Rookie
 */

#include "keyboard.h"
#include "pwm.h"


void IOInterruptInit()
{
	P2DIR &= ~(BIT4 + BIT5 + BIT6 + BIT7);	//����Ϊ����
	P2REN |= BIT4 + BIT5 + BIT6 + BIT7;	//���õ���
	P2OUT |= BIT4 + BIT5 + BIT6 + BIT7;	//������������
	P2IES |= BIT4 + BIT5 + BIT6 + BIT7;	//������ʽ��Ϊ�½��ش���
	P2IE |= BIT4 + BIT5 + BIT6 + BIT7;	//�ж�ʹ��
	P2IFG &= ~(BIT4 + BIT5 + BIT6 + BIT7);	//����жϱ�־
}

void P2IODect(unsigned int* pstate, unsigned int* pstandardPressure)
{
	unsigned int Push_Key = 0;
	//-----�ų����IO�ĸ��ź�����Ψһ���������жϱ�־λ-----
	Push_Key = P2IFG & (~P2DIR);
	//-----��ʱһ��ʱ�䣬�ܿ���е��������-----
	__delay_cycles(10000);   //������ʱ
	//----�жϰ���״̬�Ƿ�����ʱǰһ��-----
	if((P2IN & Push_Key) == 0)          //����ôΰ���ȷʵ��Ч
	switch (Push_Key)
	{
	case BIT4:
		pwmSetPermill(2,500);
		*pstate = 0;
		break;
	case BIT5:
		pwmSetPermill(2,0);
		*pstate = 1;
		break;
	case 64:
		*pstandardPressure += 10;
		break;
	case BIT7:
		*pstandardPressure -= 10;
		break;
	default:
		break;
	}
}
