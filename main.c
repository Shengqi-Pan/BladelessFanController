#include <msp430.h> 

#include "pwm.h"          //TA PWM��������ͷ�ļ�
#include "keyboard.h"	  //����ɨ��ͷ�ļ�
#include "led.h"		  //ledɨ��ͷ�ļ�
#include "adc.h"		  //adc��ȡͷ�ļ�
#include "pid.h"

/*
 * main.c
 */
//ˢ��Ƶ��
const int REFRESHFREQ = 100;
//ռ�ձ�(�͵�ƽռ�ȣ����Ϊ1000)
unsigned int dutyTime = 500;
//�趨����ѹֵ
unsigned int presentPressure = 0, standardPressure = 250;
//���flag�ƺ�Ŀǰû��
extern unsigned char flag;
//��⵽�İ���ֵ
extern unsigned char key;
//led��Ҫ��ʾ������
extern unsigned char number[8];

/*
 * ���ݶ�Ӧ�İ���ȥִ����Ӧ����
 * ������Ҫ�õ�pwmSetPermill�ӿ�
 * ����д����������
 */
void keyEvent()
{
	switch (keyScan())
	{
	case 1:
		pwmSetPermill(2,500);
		break;
	case 2:
		pwmSetPermill(2,0);
		break;
	case 3:
		standardPressure += 10;
		// pwmSetPermill(2, dutyTime);
		break;
	case 4:
		standardPressure -= 10;
		// pwmSetPermill(2, dutyTime);
		break;
	default:
		break;
	}
}

/*
 * ���ݵ�ǰ�趨����ѹֵ��ADC�������ѹֵ
 * ��ˢ��number�����д���ʾ������
 * ������Ҫ�õ�adc�ӿ�
 * ����д����������
 */
void ledUpdate()
{
	unsigned int tmp, i;
	//�ȸ����趨��ѹֵ
	tmp = standardPressure;
	for(i = 0; i <= 3; i++)
	{
		number[3 - i] = tmp % 10;
		tmp = tmp / 10;
	}
	//�ٸ���ʵ����ѹֵ
	tmp = ADS7950GetPressure();
	for(i = 0; i <= 3; i++)
	{
		number[7 - i] = tmp % 10;
		tmp = tmp / 10;
	}
}

/*
 * ����pwmռ�ձ�
 * ������Ҫ�õ�pid�Ľӿ�
 * ����д����������
 */
void pwmUpdate()
{
	dutyTime = dutyTime + PIDControl(standardPressure, ADS7950GetPressure());
	// ����pwmռ�ձ�
	pwmSetPermill(2, dutyTime);
}


void main()
{
    // Stop watchdog timer to prevent time out reset
    WDTCTL = WDTPW + WDTHOLD;
    //ClkInit();

    pwmInit('A',1,'P','P');   //����ʱ��TA��ʼ����ΪPWM������; ʱ��Դ=ACLK; �޷�Ƶ; ͨ��1��ͨ��2����Ϊ�ߵ�ƽģʽ��
    pwmSetPeriod(50);        //ͨ��1/2��PWM�������ھ���Ϊ50��ʱ������

    //pwmSetDuty(1,200);        //1ͨ�� ��Ч200��ʱ������
    //pwmSetPermill(2,200);     //2ͨ�� 20.0%

    keyInit();
    ledInit();
    int i = 0;//���ڿ���ˢ��Ƶ��

    while(1)
    {
    	//���ݰ���ִ����Ӧ����
    	keyEvent();
    	//���ݵ�ǰ�趨����ѹֵ��ADC�������ѹֵ��ˢ��number�����д���ʾ������
    	if(i == 0)ledUpdate();
    	//led��̬ɨ��
		ledShow();
		//PID����
		pwmUpdate();
		//����ˢ��Ƶ�ʿ��Ʊ���i
		i = ++i % REFRESHFREQ;
    }

    //LPM0;
}
