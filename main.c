#include <msp430.h> 

#include "pwm.h"          //TA PWM��������ͷ�ļ�
#include "keyboard.h"	  //����ɨ��ͷ�ļ�
#include "led.h"

/*
 * main.c
 */

unsigned long int dutyTime = 200;
extern unsigned char flag;
extern unsigned char key;
extern unsigned char number[8];

void main()
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    //ClkInit();

    pwmInit('A',1,'P','P');   //����ʱ��TA��ʼ����ΪPWM������
                  //ʱ��Դ=ACLK ; �޷�Ƶ;  ͨ��1��ͨ��2����Ϊ�ߵ�ƽģʽ��
    pwmSetPeriod(50);        //ͨ��1/2��PWM�������ھ���Ϊ50��ʱ������
    //pwmSetDuty(1,200);        //1ͨ�� ��Ч200��ʱ������
    //pwmSetPermill(2,200);     //2ͨ�� 20.0%

    keyInit();
    while(1)
    {
		switch (keyScan())
		{
		case 1:
			pwmSetPermill(2,500);
			break;
		case 2:
			pwmSetPermill(2,1000);
			break;
		case 3:
			dutyTime -= 10;
			pwmSetPermill(2, dutyTime);
			break;
		case 4:
			dutyTime += 10;
			pwmSetPermill(2, dutyTime);
			break;
		default:
			break;
		}
    }

    //LPM0;
}
