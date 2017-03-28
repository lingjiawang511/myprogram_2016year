#include "Headtype.h"
#include"intrins.h"
//=============================================================================
//函数名称:Delay_500ns
//功能概要:软件延时微秒函数
//参数名称:delay：延时毫秒数
//函数返回:无
//注意    :无
//=============================================================================
void Delay_500ns(u16 delay)
{
       while(delay--)    //49Mhz,1Tmodule
        {
         _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
         _nop_(); _nop_();
            
        }
}
//=============================================================================
//函数名称:Delay_ms
//功能概要:软件延时毫秒函数
//参数名称:delay：延时毫秒数
//函数返回:无
//注意    :无
//=============================================================================
void Delay_ms(u16 delay)
{
    while(delay--)
      Delay_500ns(2000);
}
//=============================================================================
//函数名称:Motor_Speed_Control
//功能概要:电机速度控制函数
//参数名称:speed：电机输入速度
//函数返回:无
//注意    :无
//=============================================================================
void Motor_Speed_Control(u8 speed)
{
	if(speed == 0){
		Motor_Speed(0,0,0);	
	}else if(speed == 1){
		Motor_Speed(0,0,1);
	}else if(speed == 2){
		Motor_Speed(0,1,0);
	}else if(speed == 3){
		Motor_Speed(0,1,1);
	}else if(speed == 4){
		Motor_Speed(1,0,0);
	}else if(speed == 5){
		Motor_Speed(1,0,1);
	}else if(speed == 6){
		Motor_Speed(1,1,0);
	}else if(speed == 7){
		Motor_Speed(1,1,1);
	}
}

//=============================================================================
//函数名称:Start_Motor1
//功能概要:电机软启动函数
//参数名称:step：电机速度也是电机运行状态步数
//函数返回:电机执行到哪一步的速度
//注意    :需要在定时器中断函数调用
//=============================================================================
u8 Start_Motor1(u8 step)
{
	static u16 start_time = 0;
	switch(step){
	case 0x00:Motor_Speed_Control(step);step++; break;
	case 0x01:Motor_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;
	case 0x02:Motor_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x03:Motor_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;
	case 0x04:Motor_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x05:Motor_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT){step++;start_time = 0;} break;					
	case 0x06:Motor_Speed_Control(step);start_time++;
						if(start_time >= START_TIMEOUT/4){step++;start_time = 0;} break;						
	case 0x07:Motor_Speed_Control(step-1);start_time++;
						if(start_time >= START_TIMEOUT/4)
							{step++;start_time = 0;Start_Ok = 1;} break;						
	default:start_time = 0; break;
	}
	return step;
}
//=============================================================================
//函数名称:Stop_Motor1
//功能概要:电机软停止函数
//参数名称:step：电机速度也是电机运行状态步数
//函数返回:电机执行到哪一步的速度
//注意    :需要在定时器中断函数调用
//=============================================================================
u8 Stop_Motor1(u8 step)
{
	static u16 stop_time = 0;
	switch(step){
	case 0x01:Motor_Speed_Control(step-1);step--;stop_time = 0;
						LED0 = 1;Control_Power = POWER_OFF;break;
	case 0x02:Motor_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/4){step--;stop_time = 0;} break;	
	case 0x03:Motor_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/4){step--;stop_time = 0;} break;	
	case 0x04:Motor_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x05:Motor_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x06:Motor_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x07:Motor_Speed_Control(step-1);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	case 0x08:Motor_Speed_Control(step-2);stop_time++;
						if(stop_time >= STOP_TIMEOUT/2){step--;stop_time = 0;} break;	
	default:Motor_Speed_Control(0);stop_time = 0;Control_Power = POWER_OFF; break;
	}
		return step;
}