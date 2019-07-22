/*
 * keyboard.c
 *
 *  Created on: 2019��7��22��
 *      Author: Rookie
 */

#include"keyboard.h"

unsigned char flag = 0;
unsigned char key = 0;

void keyInit()
{
    P2SEL &= ~(BIT4 + BIT5 + BIT6 + BIT7);   //��ΪIO��
	P2DIR &= ~(BIT4 + BIT5 + BIT6 + BIT7);   //��Ϊ����
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
