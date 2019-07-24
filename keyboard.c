/*
 * keyboard.c
 *
 *  Created on: 2019��7��22��
 *      Author: Rookie
 */

#include "keyboard.h"
#include "pwm.h"
#include "pid.h"

extern float e0, e1, e2;



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
		pwmSetPermill(2, 500);
		*pstate = 0;
		break;
	case BIT5:
		pwmSetPermill(2,0);
		e0 = 0;
		e1 = 0;
		e2 = 0;
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
