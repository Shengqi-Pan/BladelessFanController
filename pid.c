/*
 * pid.c
 *
 *  Created on: 2019��7��23��
 *      Author: admin
 */
#include <msp430.h>

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


unsigned int kp = 2500, ti = 5, td = 0;//pid[0]ΪKp pid[1]ΪTi pid[2]ΪTd
unsigned int pid_A, pid_B, pid_C;

void pid_init(void)
{
	//��ʼֵΪKi = 4000��Ti = 65534��Td = 0
	pid_A= kp * 1+ kp / ti + kp * td; 	//�Ȳ�Ҫ���ֻ��ڼ�Ti=�����Ts=1
	pid_B= - kp * (1 + 2 * td);        	//B=-Kp*(1+2*Td/Ts)
	pid_C= kp * td;             		//C=Kp*Td/Ts

}

int PIDControl(unsigned int pressure_set, unsigned int pressure_current)
{

	float delta_U = 0, Ua, Ub, Uc;
	float static e0 = 0, e1 = 0, e2 = 0;

	e0 = ((float)pressure_set - (float)pressure_current) / 100;		//�趨����������������
	Ua= pid_A* e0;
	Ub= pid_B* e1;
	Uc= pid_C* e2;
	delta_U = Ua+ Ub+ Uc;			//����u0=A*e0+B*e1+C*e2;
	PWM_current = PWM_current + delta_U;


	e2 = e1;
	e1 = e0;

	return 0;
}


