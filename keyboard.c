/*
 * keyboard.c
 *
 *  Created on: 2019��7��22��
 *      Author: Rookie
 */

#include"keyboard.h"

unsigned char flag = 0;
unsigned char key = 0;
/************************
 * ������ʱ
************************/
void delay_ms(unsigned int MS)
{
    unsigned char us,usn;
    while(MS!=0)
    {
        usn = 2;
        while(usn!=0)
        {
            us = 0xf5;
            while (us!=0)
            {
                us--;
            };
            usn--;
        }
        MS--;
    }
}

void keyInit()
{
    P2SEL &= ~(BIT4 + BIT5 + BIT6 + BIT7);   //��ΪIO��
	P2DIR &= ~(BIT4 + BIT5 + BIT6 + BIT7);  //��Ϊ����
}

char keyScan()
{
	if ((P2IN & BIT4) == 0)
    {
        flag = 1;
        key = 1;
        __delay_cycles(250000);
        return key;
    }
    else if ((P2IN & BIT5) == 0)
    {
        flag = 1;
        key = 2;
        __delay_cycles(250000);
        return key;
    }
    else if ((P2IN & BIT6) == 0)
    {
        flag = 1;
        key = 3;
        __delay_cycles(250000);
        return key;
    }
    else if ((P2IN & BIT7) == 0)
    {
        flag = 1;
        key = 4;
        __delay_cycles(250000);
        return key;
    }
    return 0;
}
void ledScan()
{

}
