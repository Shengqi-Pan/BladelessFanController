#include <msp430.h> 

/*
 * main.c
 */
#include "pwm.h"          //TA PWM��������ͷ�ļ�
/*
void ClkInit()                 //ʱ��1MHz
{
  DCOCTL|=CAL_DCO_1MHZ;
  BCSCTL1|=CAL_BC1_1MHZ;
}
*/

void main()
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    //ClkInit();

    pwmInit('A',1,'P','P');   //����ʱ��TA��ʼ����ΪPWM������
                  //ʱ��Դ=ACLK ; �޷�Ƶ;  ͨ��1��ͨ��2����Ϊ�ߵ�ƽģʽ��
    pwmSetPeriod(500);        //ͨ��1/2��PWM�������ھ���Ϊ500��ʱ������
    pwmSetDuty(1,200);        //1ͨ�� ��Ч200��ʱ������
    pwmSetPermill(2,200);     //2ͨ�� 20.0%

    LPM0;
}
