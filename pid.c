/*
 * pid.c
 *
 *  Created on: 2019��7��23��
 *      Author: admin
 */
#include <msp430.h>
#include "pwm.h"
/*
 * ���룺�趨��ѹֵ��ʵ����ѹֵ
 *
 * ����ʽ����λ��ʽPID:
 * delta_U(n) = Kp(e(n)-e(n-1)) + Kp*T/Ti*e(n) + Kp*Td/T*(e(n)-2e(n-1)+e(n-2))
 *
 * �����PWM��ռ�ձ�����
 *
 */


/*
 * PID���Ʋ�����ʼ��
 */


//int kp = 80, ti = 20, td = 0;
//int pid_A, pid_B, pid_C;

float kp = 300, ki = 100, kd = 300;
float pid_A, pid_B, pid_C;
float e0 = 0, e1 = 0, e2 = 0;

void pid_init(void)
{
//	//��ʼֵΪKi = 4000��Ti = 65534��Td = 0
//	pid_A= kp * 1+ kp / ti + kp * td; 	//�Ȳ�Ҫ���ֻ��ڼ�Ti=�����Ts=1
//	pid_B= - kp * (1 + 2 * td);        	//B=-Kp*(1+2*Td/Ts)
//	pid_C= kp * td;             		//C=Kp*Td/Ts

	pid_A= kp + ki + kd;
	pid_B= - kp - 2 * kd;
	pid_C= kd;

}



int PIDControl(int pressure_set, int pressure_current)
{

	float delta_U = 0, Ua, Ub, Uc;

	e0 = (float)(pressure_set - pressure_current) / 100;		//�趨����������������

	Ua= pid_A* e0;
	Ub= pid_B* e1;
	Uc= pid_C* e2;

	delta_U = Ua+ Ub+ Uc;			//����u0=A*e0+B*e1+C*e2;



	e2 = e1;
	e1 = e0;

	return delta_U;
}

/*
 * ����pwmռ�ձ�
 *
 */
void pwmUpdate(int *pdutyTime, unsigned int standardPressure, unsigned int currentPressure)
{
	*pdutyTime = *pdutyTime + PIDControl(standardPressure, currentPressure);
	if (*pdutyTime > 900) *pdutyTime = 900;
	else if (*pdutyTime < 0) *pdutyTime = 0;
	// ����pwmռ�ձ�
	pwmSetPermill(2, *pdutyTime);
}


