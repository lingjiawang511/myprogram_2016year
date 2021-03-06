#include"HeadType.h"

//=============================================================================
//函数名称:TIM4_Interrupts_Config
//功能概要:TIM4 中断优先级配置
//参数说明:无
//函数返回:无
//=============================================================================
static void TIM2_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}

//=============================================================================
//函数名称:TIM4_Interrupts_Config
//功能概要:TIM4 中断优先级配置
//参数说明:无
//函数返回:无
//=============================================================================
static void TIM4_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}


//=============================================================================
//函数名称:TIM4_Config
//功能概要:TIM4 定时器配置
//参数说明:无
//函数返回:无
//=============================================================================
void TIM4_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
		TIM_DeInit(TIM4);
		TIM_TimeBaseStructure.TIM_Period = 199;    //0.2MS
		TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
		TIM_ClearFlag(TIM4, TIM_FLAG_Update);
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM4, DISABLE );    //初始化不开启定时器
		//TIM_Cmd(TIM4, ENABLE ); 
		TIM4_Interrupts_Config();
}

/****************************
**TIM2的通道1使用单脉冲模式
**TIM3使用门控模式用来输出PWM
**
****************************/
//TIM2per:重装值
//Compare1:比较捕获1的预装载值
void Motor_Init(u16 TIM2per, u16 TIM3per, u16 TIM3Compare1)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//使能定时器2的时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//使能定时器3的时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能复用IO时钟
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_6;//PA0
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStruct);
  
  //TIM2工作在单脉冲下
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//没有时钟分割
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
  TIM_TimeBaseInitStruct.TIM_Prescaler = 7200;//预分频值,每100us计数一次
  TIM_TimeBaseInitStruct.TIM_Period = TIM2per;//重装值
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
  
  TIM_SelectOnePulseMode(TIM2,TIM_OPMode_Single);//设置TIM2在单脉冲模式，且是单一的脉冲，在下一个更新事件停止
  TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);//使能定时器2的通道1预装载寄存器
  TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_OC1Ref);
  
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为无效电平，否则为有效电平
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//OC1输出使能
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//有效电平为高
  TIM_OCInitStruct.TIM_Pulse = 1 ;//比较捕获1的预装载值，单脉冲宽度 = 自动重装值 - 比较捕获寄存器的值。
  TIM_OC1Init(TIM2,&TIM_OCInitStruct);                 //Tpusel = TIM_TimeBaseInitStruct.TIM_Period - TIM_OCInitStruct.TIM_Pulse;
  
  TIM_Cmd(TIM2,DISABLE);//先不使能能TIM2
  TIM2_Interrupts_Config();
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  
  //TIM3工作在从模式的门控模式下的PWM输出模式
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//没有时钟分割
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数模式
  TIM_TimeBaseInitStruct.TIM_Prescaler = 720;//预分频值，10us计数一次
  TIM_TimeBaseInitStruct.TIM_Period = TIM3per;//重装值
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
  
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);//TIM3为门控模式
  TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);//使能TIM3的主从模式
  TIM_SelectInputTrigger(TIM3,TIM_TS_ITR1);//内部触发，从TIM2触发
  
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为无效电平，否则为有效电平
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//OC1输出使能
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//有效电平为高
  TIM_OCInitStruct.TIM_Pulse = TIM3Compare1;//比较捕获1的预装载值
  TIM_OC1Init(TIM3,&TIM_OCInitStruct);
  
  TIM_Cmd(TIM3,ENABLE);//使能TIM3
}

//设置PWM的输出
//Cycle:为周期,单位(us)
//Pulse_Num:为脉冲个数（小于3200）
void TIM2_TIM3_PWM(u16 Cycle, u16 Pulse_Num)
{
  u16 TIM3per = 0;
  u32 Time = 0;
  //改变TIM3的重装值改变脉冲频率这里设置脉冲占空比为50%
  //改变TIM2的预分频器和重装值改变脉冲个数
  TIM_Cmd(TIM2,DISABLE);//先不使能能TIM2  
  Time = Cycle * Pulse_Num;
  Time /= 100;              //预分频为7200,100us计数一次
  TIM3per = Cycle/10;       //预分频为720,10us计数一次
  
  TIM_SetAutoreload(TIM2, Time+1);//设置TIM2的重装值
  TIM_SetAutoreload(TIM3, TIM3per-1);//设置TIM3的重装值
  TIM_SetCompare1(TIM3,TIM3per/2);//设置占空比为50%
  TIM_Cmd(TIM2,ENABLE);//使能TIM2  
}









