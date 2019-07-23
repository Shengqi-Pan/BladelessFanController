/*
 * led.c
 *
 *  Created on: 2019��7��22��
 *      Author: Rookie
 */

/*
 * led��ʾģ��ʹ��˵��
 * ʹ��ʱ��Ҫ�ȵ���ledInit�����Գ�ʼ��led������˿�
 * �ٸı�number�����е����ݴ��������δӸߵ���
 * ������ledShow����
 */

#include"led.h"

unsigned char number[8] = {1, 2, 3, 4, 5, 6, 7, 8};

void ledInit()
{
	//λѡ�ڳ�ʼ��
	P3SEL &= ~(BIT0 + BIT5 + BIT4);   //��ΪIO��
	P3DIR |= BIT0 + BIT4 + BIT5;   //��Ϊ���

	P11SEL &= ~(BIT0 + BIT1 + BIT2);   //��ΪIO��
	P11DIR |= BIT0 + BIT1 + BIT2;   //��Ϊ���

	P1SEL &= ~(BIT6 + BIT7);   //��ΪIO��
	P1DIR |= BIT6 + BIT7;   //��Ϊ���

	//��ѡ�ڳ�ʼ��
	P8SEL &= 0x00;	//��ΪIO��
	P8DIR |= 0xff;	//��Ϊ���
}

void ledLight(unsigned char index)
{
	switch(index)
	{
		case 0://��һλ�������λ����������ߣ�
			P3OUT &= ~BIT0;//�ø�
			break;
		case 1:
			P3OUT &= ~BIT5;
			break;
		case 2:
			P3OUT &= ~BIT4;
			break;
		case 3:
			P11OUT &= ~BIT0;
			break;
		case 4:
			P11OUT &= ~BIT1;
			break;
		case 5:
			P11OUT &= ~BIT2;
			break;
		case 6:
			P1OUT &= ~BIT6;
			break;
		case 7:
			P1OUT &= ~BIT7;
			break;
		default:
			break;
	}
}

void ledExtinguishAll()
{
	P3OUT |= BIT0 + BIT5 + BIT4;   //���1
	P11OUT |= BIT0 + BIT1 + BIT2;   //���1
	P1OUT |= BIT6 + BIT7;   //���1
}

/*
 * ����һ������ʾ������
 * �������벢��I/O��
 */
void ledRefresh(unsigned char index)
{
	static unsigned char decode[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
	//��Ӧ��������
	P8OUT = decode[number[index]];
}

void ledShow()
{
	static unsigned char index = 0;//����ȡ������±�
	int i;
	for(i = 0; i <8; i++)
	{
		//��Ϩ������LED
		ledExtinguishAll();
		//��������
		ledRefresh(index);
		//����ָ����LED
		ledLight(index);
		//�±�˳����λ
		index = (++index % 8);
		__delay_cycles(1000);//�ӳ�0.02ms
	}
	ledExtinguishAll();
}
