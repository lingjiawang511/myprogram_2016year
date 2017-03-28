#ifndef __HEADTYPE_H_
#define __HEADTYPE_H_

#include "c8051f410.h"
typedef unsigned char    u8;
typedef unsigned int     u16;
typedef unsigned long    u32;
typedef char             int_8;
typedef int              int_16;
typedef long             int_32;

#define TimerHigh (65500-5000)/256
#define TimerLow  (65500-5000)%256
#define Motor_Speed(x3,x2,x1)	do{	Speed_1 = x1;Speed_2 = x2;Speed_3 = x3;}while(0)
#define POWER_ON	0
#define POWER_OFF 1

/**现场人员只允许修改这三个参数,时间只是个大概**/
#define START_TIMEOUT		80			//软启动时间，80*5ms*2 =0.8S,修改必须在60到120之间
#define STOP_TIMEOUT		80			//软停止时间, 80*5ms*2 =0.8S
#define STOP_DELAY			200*2		//200*2*5ms=2s,延时多久只需要改这个参数
/**现场人员只允许修改这三个参数,时间只是个大概**/

sbit P00 = P0^0;
sbit P01 = P0^1;
sbit P02 = P0^2;
sbit P03 = P0^3;
sbit P04 = P0^4;
sbit P05 = P0^5;
sbit P06 = P0^6;
sbit P07 = P0^7;

sbit P10 = P1^0;
sbit P11 = P1^1;
sbit LED0 = P1^2;
sbit P13 = P1^3;
sbit P14 = P1^4;
sbit P15 = P1^5;
sbit P16 = P1^6;
sbit Sensor= P1^7;

sbit Enable = P2^0;
sbit Speed_1 = P2^1;
sbit Speed_2 = P2^2;
sbit Speed_3 = P2^3;
sbit Control_Power = P2^4;
sbit Control_Power1 = P2^5;
sbit P26 = P2^6;
sbit P27 = P2^7;



extern u8 Speed_Step;
extern u8 Start_Signal;
extern u8 Stop_Signal;
extern u8 Start_Ok;
extern u8 Stop_Ok;
extern u8 Stop_Delay;
void Delay_500ns(u16 delay);
void Delay_ms(u16 delay);
void Motor_Speed_Control(u8 speed);
u8 Start_Motor(u8 step);
u8 Stop_Motor(u8 step);

u8 Start_Motor1(u8 step);
u8 Stop_Motor1(u8 step);

void Timer0Init(void);		//5毫秒@12.000MHz

#endif