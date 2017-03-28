#ifndef __DELAY_H_
#define __DELAY_H_

#include"c8051F350.h"

typedef unsigned char    u8;
typedef unsigned int     u16;
typedef unsigned long    u32;
typedef char             int_8;
typedef int              int_16;
typedef long             int_32;

#define     Led_Init()   {P1MDOUT&=0xFC; P1SKIP&=0XFC;}
#define     Led1_ON      P1 &=0XFE;
#define     Led1_OFF     P1 |=0X01;
#define     Led2_ON      P1 &=0XFD;
#define     Led2_OFF     P1 |=0X02;

void Delay_500ns(u16 delay);
void Delay_ms(u16 delay);


#endif