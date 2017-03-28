#include "Headtype.h"
#include"intrins.h"

//#define STOP_DELAY	200*4		//200*5ms*9=9s,延时多久只需要改这个参数
//=============================================================================
//函数名称:Timer0Init
//功能概要:定时器0初始化函数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void Timer0Init(void)		//5毫秒@12.000MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
  CKCON &=0XF8;       //设置定时器时钟选择
  CKCON |=0X02;       //设置定时器时钟system/48=1.02MHz
	TL0 = TimerLow;		//设置定时初值
	TH0 = TimerHigh;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
  ET0=1;
  EA=1;
}
//=============================================================================
//函数名称:timer0
//功能概要:定时器0中断服务函数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void timer0() interrupt  1 
{
	static u16 stop_delay_time;
	TL0 = TimerLow;		//设置定时初值
	TH0 = TimerHigh;		//设置定时初值
	if(Start_Signal ==1){
		Speed_Step = Start_Motor1(Speed_Step);
	}
	if(Stop_Signal == 1){
		Speed_Step = Stop_Motor1(Speed_Step);
	}
	if(Stop_Delay == 1){
		stop_delay_time++;
		if(stop_delay_time >= STOP_DELAY){
			Stop_Ok = 1;
			Stop_Delay = 0;
			stop_delay_time = 0;
		}
	}
}

