#include <msp430.h> 

/*
 * main.c
 */
#include "pwm.h"          //TA PWM��������ͷ�ļ�
#include "keyboard.h"

unsigned long int dutyTime = 200;
extern unsigned char flag;
extern unsigned char key;

void main()
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    //ClkInit();

    pwmInit('A',1,'P','P');   //����ʱ��TA��ʼ����ΪPWM������
                  //ʱ��Դ=ACLK ; �޷�Ƶ;  ͨ��1��ͨ��2����Ϊ�ߵ�ƽģʽ��
    pwmSetPeriod(50);        //ͨ��1/2��PWM�������ھ���Ϊ50��ʱ������
    pwmSetDuty(1,200);        //1ͨ�� ��Ч200��ʱ������
    pwmSetPermill(2,200);     //2ͨ�� 20.0%

    keyInit();
    while(1)
    {
		switch (keyScan())
		{
		case 1:
			//
			break;
		case 2:
			//
			break;
		case 3:
			dutyTime -= 100;
			pwmSetPermill(2, dutyTime);
			break;
		case 4:
			dutyTime += 100;
			pwmSetPermill(2, dutyTime);
			break;
		default:
			break;
		}
    }
    //LPM0;
}
