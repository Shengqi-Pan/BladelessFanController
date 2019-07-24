/*
 * pid.c
 *
 *  Created on: 2019年7月23日
 *      Author: admin
 */
#include <msp430.h>

/*
 * 输入：设定气压值、实际气压值
 *
 * 增量式递推位置式PID:
 * delta_U(n) = Kp(e(n)-e(n-1)) + Kp*T/Ti*e(n) + Kp*Td/T*(e(n)-2e(n-1)+e(n-2))
 *
 * 输出：PWM波占空比增量
 *
 */


/*
 * PID控制参数初始化
 */


int kp = 120, ti = 10, td = 2;
int pid_A, pid_B, pid_C;

void pid_init(void)
{
	//初始值为Ki = 4000；Ti = 65534；Td = 0
	pid_A= kp * 1+ kp / ti + kp * td; 	//先不要积分环节即Ti=无穷大，Ts=1
	pid_B= - kp * (1 + 2 * td);        	//B=-Kp*(1+2*Td/Ts)
	pid_C= kp * td;             		//C=Kp*Td/Ts

}

int PIDControl(int pressure_set, int pressure_current)
{

	float delta_U = 0, Ua, Ub, Uc;
	float static e0 = 0, e1 = 0, e2 = 0;

	e0 = (float)(pressure_set - pressure_current) / 100;		//设定量与读回量的误差量
	Ua= pid_A* e0;
	Ub= pid_B* e1;
	Uc= pid_C* e2;
	delta_U = Ua+ Ub+ Uc;			//增量u0=A*e0+B*e1+C*e2;
	//PWM_current = PWM_current + delta_U;


	e2 = e1;
	e1 = e0;

	return delta_U;
}


