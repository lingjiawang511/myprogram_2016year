#include "TIM.h"

//=============================================================================
//函数名称:TIM2_Interrupts_Config
//功能概要:TIM2 中断优先级配置
//参数说明:无
//函数返回:无
//=============================================================================
static void TIM2_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:TIM3_Interrupts_Config
//功能概要:TIM3 中断优先级配置
//参数说明:无
//函数返回:无
//=============================================================================
static void TIM3_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}

//=============================================================================
//函数名称:TIM2_Config
//功能概要:TIM2 定时器配置
//参数说明:无
//函数返回:无
//=============================================================================
void TIM2_Config(void )
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period =4999; //5	MS;		 		
	TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);				  
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; 
    
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);						
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM2, ENABLE);	
    TIM2_Interrupts_Config();
}
//=============================================================================
//函数名称:TIM3_Config
//功能概要:TIM3 定时器配置
//参数说明:无
//函数返回:无
//=============================================================================
void TIM3_Config(u16 arr)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period =arr; //999;    //2MS
	TIM_TimeBaseStructure.TIM_Prescaler = (72/2 - 1);
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE );    //初始化不开启定时器
    
    TIM3_Interrupts_Config();
}

//=============================================================================
//函数名称:PWM_SetFre
//功能概要:PWM设置频率
//参数说明:无
//函数返回:无
//注意：PWM在定时器改变IO口模拟，两次进入中断时一个周期，所以分频系数设为36
//      相当于定时器工作在1MHZ频率，方便计算。限制范围50HZ~200KHZ
//=============================================================================
void PWM_SetFre(u32 fre)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;   

	if(fre <= 50){
		fre = 50;
	}else if(fre >= 200000){
		fre = 200000;
	}
	fre = (1000000/fre)-1;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period =fre;
	TIM_TimeBaseStructure.TIM_Prescaler = (72/2 - 1);//36分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE );    

}
//TIM3 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  //使能GPIO外设和AFIO复用功能模块时钟
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //Timer3部分重映射  TIM3_CH2->PB5    
 
   //设置该引脚为复用输出功能,输出TIM3 CH2的PWM脉冲波形	GPIOB.5
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; //TIM_CH2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR2上的预装载寄存器
 
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE );    //使能TIM3
    
    TIM3_Interrupts_Config();

}


