#include "stepmotor.h"
#include"HeadType.h"

Motor_Type  Step_Motor;

//=============================================================================
//函数名称: stepmotor_GPIO_Config
//功能概要:步进电机引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void stepmotor_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	//使能GPIOC的外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//选择要用的GPIO引脚		
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	///设置引脚模式为推免输出模式			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	//设置引脚速度为50MHZ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	//调用库函数，初始化GPIO
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	Motor_DIR_OFF;
	Motor_Stop();
	Step_Motor.frequency = 2000;
}
//=============================================================================
//函数名称:Motor_Soft_Start
//功能概要:步进电机软启动
//参数名称:startfre：软启动开始频率，endfre：软启动最终频率
//		   second:软启动每一步骤运行秒数，mode：执行模式
//函数返回:无
//注意    :将设置的频率当成脉冲数乘以2之后相当于延时的秒数
//		模式为0时相当于直接快速启动，软启动总时间=second*mode
//=============================================================================
void Motor_Soft_Start(u32 startfre,u32 endfre,u8 second,u8 mode)
{	
	u32 fretemp;
	if((startfre >=	endfre)||(second <= 0)){
		mode = 0;
	}
	Step_Motor.run_mode = PULSE_RUN;
	fretemp = endfre - startfre;
	fretemp = fretemp/mode;
	Motor_Start();
	while(mode--){
		PWM_SetFre(startfre);
		Step_Motor.pules_count = (startfre)*2*second;
		while(Step_Motor.pules_count);
		startfre += fretemp;
	};
	PWM_SetFre(endfre);
	Step_Motor.run_mode = AlWAYS_RUN;
}
//=============================================================================
//函数名称:Motor_Soft_Stop
//功能概要:步进电机软停止
//参数名称:currentfre：电机当前运行频率,second：软停止每一步骤所用的秒数,mode：执行模式
//函数返回:无
//注意    :将设置的频率当成脉冲数乘以2之后相当于延时的秒数
//		模式为0时相当于直接快速停止，软停止总时间=second*mode
//=============================================================================
void Motor_Soft_Stop(u32 currentfre,u8 second,u8 mode)
{
	u32 fretemp,fre;
	Step_Motor.run_mode = PULSE_RUN;
	fretemp = currentfre/mode;
	fre =  currentfre;
	while(mode--){
		PWM_SetFre(fre);
		Step_Motor.pules_count = fre*2*second;
		while(Step_Motor.pules_count);
		fre -= fretemp;
	}
	Motor_Stop();
}
//=============================================================================
//函数名称:Motor_Step_Pules
//功能概要:步进电机行走固定的脉冲数
//参数名称:fre：输入，运行频率,pules：输入，运行脉冲数,mode：输入，执行模式
//函数返回:无
//注意    :	mode大于0时使用软启动停止方式运行响应的脉冲
//=============================================================================
void Motor_Step_Pules(u32 fre,u32 pules,u8 mode)
{
	u32 fretemp,pulestemp;
	Step_Motor.run_mode = PULSE_RUN;
	Motor_Start();
	if(mode == 1){
		fretemp = fre/2;
		pulestemp = pules/3;
		PWM_SetFre(fretemp);
		Step_Motor.pules_count = pulestemp;
		while(Step_Motor.pules_count);
		PWM_SetFre(fre);
		Step_Motor.pules_count = pules - pulestemp*2;
		while(Step_Motor.pules_count);	
		PWM_SetFre(fretemp);
		Step_Motor.pules_count = pulestemp;
		while(Step_Motor.pules_count);
	}else{
		PWM_SetFre(fre);
		Step_Motor.pules_count = pules;
		while(Step_Motor.pules_count);
	}
	Motor_Stop();		
}
