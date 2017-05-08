#include"HeadType.h"	

#define FILTER_TIME  150;  //滤波时间=N*2ms
//=============================================================================
//函数名称:EXTIX0_Init
//功能概要:外部中断0初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void  EXTIX0_Init(void )
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:EXTIX3_Init
//功能概要:外部中断3初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void  EXTIX3_Init(void )
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
//	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource3);
			
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:EXTIX4_Init
//功能概要:外部中断4初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void  EXTIX4_Init(void )
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
//	  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource4);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;	//KEY2
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:EXTIX9_5_Init
//功能概要:外部中断9_5初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void  EXTIX9_5_Init(void )
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
#if  CHANNEL_4 == 1
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_8;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6); 
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6|EXTI_Line8;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
#else
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_8|GPIO_Pin_9;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOC, &GPIO_InitStructure);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource5); 
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource6);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource8); 
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource9);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line5|EXTI_Line6|EXTI_Line8|EXTI_Line9;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
#endif
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:EXTIX15_10_Init
//功能概要:外部中断15_10初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void  EXTIX15_10_Init(void )
{
	 	EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		GPIO_InitTypeDef  GPIO_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_14;			 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource10); 
 	  GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
	
  	EXTI_InitStructure.EXTI_Line=EXTI_Line10|EXTI_Line12|EXTI_Line14;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//使能按键KEY2所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级2
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//函数名称:Motor1_pulse_IRQTimer
//功能概要:通道1电机脉冲软件消抖计数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Motor1_pulse_IRQTimer(void)
{
	 static u16 filter_time = 0;
		if(MCU_State == HOST){
				if((Channel.ch1.state == WORKING)&&(Channel.ch1.motor_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch1.motor_irqtime++;
					if(IRQ_TIMEOUT <= Channel.ch1.motor_irqtime){
						if(READ_DEVICE1_SENSOR1 == RESET){
							if(filter_time == 0){
								Channel.ch1.motor_pulse++;
								filter_time = FILTER_TIME;
								 Channel.ch1.send_jam_time = SEND_MEDICINE_JAMTIME ;
							}
						}
						Channel.ch1.motor_irqstate = 0;
						Channel.ch1.motor_irqtime = 0;
					}
					if((Channel.ch1.send_num <= Channel.ch1.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE1_MOTOR_STOP;							
							Channel.ch1.motor_state	= 0;					
						}
				}
				if(filter_time >0){
					filter_time--;
				}
		}else{
			filter_time = 0;
		}
}
//=============================================================================
//函数名称:Motor2_pulse_IRQTimer
//功能概要:通道2电机脉冲软件消抖计数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Motor2_pulse_IRQTimer(void)
{
	static u16 filter_time = 0;
		if(MCU_State == HOST){
				if((Channel.ch2.state == WORKING)&&(Channel.ch2.motor_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch2.motor_irqtime++;
					if(IRQ_TIMEOUT <= Channel.ch2.motor_irqtime){
						if(READ_DEVICE2_SENSOR1 == RESET){
							if(filter_time == 0){
								Channel.ch2.motor_pulse++;
								filter_time = FILTER_TIME;
								 Channel.ch2.send_jam_time = SEND_MEDICINE_JAMTIME ;
							}
						}
						Channel.ch2.motor_irqstate = 0;
						Channel.ch2.motor_irqtime = 0;
					}
					if((Channel.ch2.send_num <= Channel.ch2.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE2_MOTOR_STOP;							
							Channel.ch2.motor_state	= 0;					
						}
				}
				if(filter_time >0){
					filter_time--;
				}
		}else{
			filter_time = 0;
		}
}
//=============================================================================
//函数名称:Motor3_pulse_IRQTimer
//功能概要:通道3电机脉冲软件消抖计数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Motor3_pulse_IRQTimer(void)
{
	static u16 filter_time = 0;
		if(MCU_State == HOST){
				if((Channel.ch3.state == WORKING)&&(Channel.ch3.motor_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch3.motor_irqtime++;
					if(IRQ_TIMEOUT <= Channel.ch3.motor_irqtime){
						if(READ_DEVICE3_SENSOR1 == RESET){
							if(filter_time == 0){
								Channel.ch3.motor_pulse++;
								filter_time = FILTER_TIME;
								 Channel.ch3.send_jam_time = SEND_MEDICINE_JAMTIME ;
							}
						}
						Channel.ch3.motor_irqstate = 0;
						Channel.ch3.motor_irqtime = 0;
					}
					if((Channel.ch3.send_num <= Channel.ch3.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE3_MOTOR_STOP;							
							Channel.ch3.motor_state	= 0;					
						}
				}
				if(filter_time >0){
					filter_time--;
				}
		}else{
			filter_time = 0;
		}
}
//=============================================================================
//函数名称:Motor4_pulse_IRQTimer
//功能概要:通道4电机脉冲软件消抖计数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Motor4_pulse_IRQTimer(void)
{
	static u16 filter_time = 0;
		if(MCU_State == HOST){
				if((Channel.ch4.state == WORKING)&&(Channel.ch4.motor_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch4.motor_irqtime++;
					if(IRQ_TIMEOUT <= Channel.ch4.motor_irqtime){
						if(READ_DEVICE4_SENSOR1 == RESET){
							if(filter_time == 0){
								Channel.ch4.motor_pulse++;
								filter_time = FILTER_TIME;
								Channel.ch4.send_jam_time = SEND_MEDICINE_JAMTIME ;
							}
						}
						Channel.ch4.motor_irqstate = 0;
						Channel.ch4.motor_irqtime = 0;
					}
					if((Channel.ch4.send_num <= Channel.ch4.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE4_MOTOR_STOP;							
							Channel.ch4.motor_state	= 0;					
						}
				}
				if(filter_time >0){
					filter_time--;
				}
		}else{
			filter_time = 0;
		}
}

#if CHANNEL_4 == 0
//=============================================================================
//函数名称:Motor5_pulse_IRQTimer
//功能概要:通道4电机脉冲软件消抖计数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Motor5_pulse_IRQTimer(void)
{
	static u16 filter_time = 0;
		if(MCU_State == HOST){
				if((Channel.ch5.state == WORKING)&&(Channel.ch5.motor_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch5.motor_irqtime++;
					if(IRQ_TIMEOUT <= Channel.ch5.motor_irqtime){
						if(READ_DEVICE5_SENSOR1 == RESET){
							if(filter_time == 0){
								Channel.ch5.motor_pulse++;
								filter_time = FILTER_TIME;
								Channel.ch5.send_jam_time = SEND_MEDICINE_JAMTIME ;
							}
						}
						Channel.ch5.motor_irqstate = 0;
						Channel.ch5.motor_irqtime = 0;
					}
					if((Channel.ch5.send_num <= Channel.ch5.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE5_MOTOR_STOP;							
							Channel.ch5.motor_state	= 0;					
						}
				}
				if(filter_time >0){
					filter_time--;
				}
		}else{
			filter_time = 0;
		}
}

#endif
//=============================================================================
//函数名称:Device1_Send_Actual_IRQTimer
//功能概要:通道1实际发药数计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Device1_Send_Actual_IRQTimer(void)
{
// 	 static u8 count_temp = 0;
		if((Channel.ch1.state == WORKING)&&(Channel.ch1.send_actual_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch1.send_actual_irqtime++;
// 			    if(count_temp==0){
					if(IRQ_TIMEOUT1 <= Channel.ch1.send_actual_irqtime){
						if(READ_DEVICE1_SENSOR3 == RESET){
							Channel.ch1.send_actual++;
// 							  count_temp = 1;
							}
// 					}else if(count_temp == 1){
// 						if(IRQ_TIMEOUT1 <= Channel.ch1.send_actual_irqtime){
// 							if(READ_DEVICE1_SENSOR3 == RESET){
// 							  Channel.ch1.send_actual++;
// 								count_temp = 0;
// 								Channel.ch1.send_actual_irqstate = 0;
// 								Channel.ch1.send_actual_irqtime = 0;
// 							}
// 						}
								Channel.ch1.send_actual_irqstate = 0;
								Channel.ch1.send_actual_irqtime = 0;
					}
		}
}
//=============================================================================
//函数名称:Device2_Send_Actual_IRQTimer
//功能概要:通道2实际发药数计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Device2_Send_Actual_IRQTimer(void)
{
		if((Channel.ch2.state == WORKING)&&(Channel.ch2.send_actual_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch2.send_actual_irqtime++;
					if(IRQ_TIMEOUT1 <= Channel.ch2.send_actual_irqtime){
						if(READ_DEVICE2_SENSOR3 == RESET){
							Channel.ch2.send_actual++;
						}
						Channel.ch2.send_actual_irqstate = 0;
						Channel.ch2.send_actual_irqtime = 0;
					}
		}
}
//=============================================================================
//函数名称:Device3_Send_Actual_IRQTimer
//功能概要:通道3实际发药数计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Device3_Send_Actual_IRQTimer(void)
{
		if((Channel.ch3.state == WORKING)&&(Channel.ch3.send_actual_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch3.send_actual_irqtime++;
					if(IRQ_TIMEOUT1 <= Channel.ch3.send_actual_irqtime){
						if(READ_DEVICE3_SENSOR3 == RESET){
							Channel.ch3.send_actual++;
						}
						Channel.ch3.send_actual_irqstate = 0;
						Channel.ch3.send_actual_irqtime = 0;
					}
		}
}
//=============================================================================
//函数名称:Device4_Send_Actual_IRQTimer
//功能概要:通道4实际发药数计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Device4_Send_Actual_IRQTimer(void)
{
		if((Channel.ch4.state == WORKING)&&(Channel.ch4.send_actual_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch4.send_actual_irqtime++;
					if(IRQ_TIMEOUT1 <= Channel.ch4.send_actual_irqtime){
						if(READ_DEVICE4_SENSOR3 == RESET){
							Channel.ch4.send_actual++;
						}
						Channel.ch4.send_actual_irqstate = 0;
						Channel.ch4.send_actual_irqtime = 0;
					}
		}
}
#if CHANNEL_4 == 0
//=============================================================================
//函数名称:Device5_Send_Actual_IRQTimer
//功能概要:通道4实际发药数计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void 	Device5_Send_Actual_IRQTimer(void)
{
		if((Channel.ch5.state == WORKING)&&(Channel.ch5.send_actual_irqstate == 1)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					Channel.ch5.send_actual_irqtime++;
					if(IRQ_TIMEOUT1 <= Channel.ch5.send_actual_irqtime){
						if(READ_DEVICE5_SENSOR3 == RESET){
							Channel.ch5.send_actual++;
						}
						Channel.ch5.send_actual_irqstate = 0;
						Channel.ch5.send_actual_irqtime = 0;
					}
		}
}

#endif
//=============================================================================
//函数名称:EXTIX_Init
//功能概要:所有外部中断初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTIX_Init(void)
{
		EXTIX0_Init( );
		EXTIX3_Init( );
		EXTIX4_Init( );
		EXTIX9_5_Init( );
		EXTIX15_10_Init( );
  	
}
//=============================================================================
//函数名称:EXTI0_IRQHandler
//功能概要:外部中断0服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI0_IRQHandler(void)
{		
//		static u8 test=0;
		if(EXTI_GetITStatus(EXTI_Line0) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch1.motor_irqstate == 0)&&(Channel.ch1.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					if((Channel.ch1.send_num-1 <= Channel.ch1.motor_pulse)){
						Channel.ch1.motor_pulse++;
					}else{
						Channel.ch1.motor_irqstate = 1;
					}
				}
				if(Channel.ch1.state == WORKING){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真，最后一次不用延时
					if((Channel.ch1.send_num <= Channel.ch1.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE1_MOTOR_STOP;	
							Channel.ch1.motor_state	= 0;	
							Channel.ch1.motor_irqstate = 0;						
						}
					}else if((Channel.ch1.state ==RESERVE)||(Channel.ch1.state == END)){
						DEVICE1_MOTOR_STOP;	
						Channel.ch1.motor_state	= 0;	
				}
			}else{
//				test++;
//				if(test >= 5){
//					test = 0;
//					DEVICE1_MOTOR_STOP;	//从机模式只要转到原点就停止
//					Channel.ch1.motor_state	= 0;
//				}
				DEVICE1_MOTOR_STOP;	//从机模式只要转到原点就停止
				Channel.ch1.motor_state	= 0;
			}
		EXTI_ClearITPendingBit(EXTI_Line0); //清除LINE0上的中断标志位  
		}
}

//=============================================================================
//函数名称:EXTI3_IRQHandler
//功能概要:外部中断3服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch4.motor_irqstate == 0)&&(Channel.ch4.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					if((Channel.ch4.send_num-1 <= Channel.ch4.motor_pulse)){
						Channel.ch4.motor_pulse++;
					}else{
						Channel.ch4.motor_irqstate = 1;
					}
				}
				if(Channel.ch4.state == WORKING){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真，最后一次不用延时
					if((Channel.ch4.send_num <= Channel.ch4.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE4_MOTOR_STOP;	
							Channel.ch4.motor_state	= 0;	
							Channel.ch4.motor_irqstate = 0;						
						}
					}else if((Channel.ch4.state ==RESERVE)||(Channel.ch4.state == END)){
						DEVICE4_MOTOR_STOP;	
						Channel.ch4.motor_state	= 0;	
				}
			}else{
				DEVICE4_MOTOR_STOP;	//从机模式只要转到原点就停止
				Channel.ch4.motor_state	= 0;
			}
		EXTI_ClearITPendingBit(EXTI_Line3); //清除LINE0上的中断标志位  
	} 
}
//=============================================================================
//函数名称:EXTI4_IRQHandler
//功能概要:外部中断4服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI4_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line4) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch4.send_actual_irqstate == 0)&&(Channel.ch4.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
						Channel.ch4.send_actual_irqstate = 1;
						Channel.ch4.send_actual_irqtime = 0;					
				}
			}
		EXTI_ClearITPendingBit(EXTI_Line4); //清除LINE0上的中断标志位  
	}  
}
//=============================================================================
//函数名称:EXTI9_5_IRQHandler
//功能概要:外部中断9-5服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch3.motor_irqstate == 0)&&(Channel.ch3.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					if((Channel.ch3.send_num-1 <= Channel.ch3.motor_pulse)){
						Channel.ch3.motor_pulse++;
					}else{
						Channel.ch3.motor_irqstate = 1;
					}
				}
				if(Channel.ch3.state == WORKING){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真，最后一次不用延时
					if((Channel.ch3.send_num <= Channel.ch3.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE3_MOTOR_STOP;	
							Channel.ch3.motor_state	= 0;	
							Channel.ch3.motor_irqstate = 0;						
						}
					}else if((Channel.ch3.state ==RESERVE)||(Channel.ch3.state == END)){
						DEVICE3_MOTOR_STOP;	
						Channel.ch3.motor_state	= 0;	
				}
			}else{
				DEVICE3_MOTOR_STOP;	//从机模式只要转到原点就停止
				Channel.ch3.motor_state	= 0;
			}
		EXTI_ClearITPendingBit(EXTI_Line6);
	}else if(EXTI_GetITStatus(EXTI_Line8) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch3.send_actual_irqstate == 0)&&(Channel.ch3.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
						Channel.ch3.send_actual_irqstate = 1;
						Channel.ch3.send_actual_irqtime = 0;					
				}
			}
		EXTI_ClearITPendingBit(EXTI_Line8);
	}
	#if CHANNEL_4 ==1
	else{
		EXTI_ClearITPendingBit(EXTI_Line5);
		EXTI_ClearITPendingBit(EXTI_Line7);
		EXTI_ClearITPendingBit(EXTI_Line9);
	}
	#else
	else if(EXTI_GetITStatus(EXTI_Line5) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch5.motor_irqstate == 0)&&(Channel.ch5.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					if((Channel.ch5.send_num-1 <= Channel.ch5.motor_pulse)){
						Channel.ch5.motor_pulse++;
					}else{
						Channel.ch5.motor_irqstate = 1;
					}
				}
				if(Channel.ch5.state == WORKING){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真，最后一次不用延时
					if((Channel.ch5.send_num <= Channel.ch5.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE5_MOTOR_STOP;	
							Channel.ch5.motor_state	= 0;	
							Channel.ch5.motor_irqstate = 0;						
						}
					}else if((Channel.ch5.state ==RESERVE)||(Channel.ch5.state == END)){
						DEVICE5_MOTOR_STOP;	
						Channel.ch5.motor_state	= 0;	
				}
			}else{
				DEVICE5_MOTOR_STOP;	//从机模式只要转到原点就停止
				Channel.ch5.motor_state	= 0;
			}
		EXTI_ClearITPendingBit(EXTI_Line5);
		}else if(EXTI_GetITStatus(EXTI_Line9) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch5.send_actual_irqstate == 0)&&(Channel.ch5.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
						Channel.ch5.send_actual_irqstate = 1;
						Channel.ch5.send_actual_irqtime = 0;					
				}
			}
		EXTI_ClearITPendingBit(EXTI_Line9);
	}else{
		EXTI_ClearITPendingBit(EXTI_Line7);
		}
	#endif

}
//=============================================================================
//函数名称:EXTI15_10_IRQHandler
//功能概要:外部中断15-10服务程序 
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line10) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch1.send_actual_irqstate == 0)&&(Channel.ch1.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
						Channel.ch1.send_actual_irqstate = 1;
						Channel.ch1.send_actual_irqtime = 0;					
				}
			}
		EXTI_ClearITPendingBit(EXTI_Line10);
	}else if(EXTI_GetITStatus(EXTI_Line12) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch2.motor_irqstate == 0)&&(Channel.ch2.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真
					if((Channel.ch2.send_num-1 <= Channel.ch2.motor_pulse)){
						Channel.ch2.motor_pulse++;
					}else{
						Channel.ch2.motor_irqstate = 1;
					}
				}
				if(Channel.ch2.state == WORKING){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真，最后一次不用延时
					if((Channel.ch2.send_num <= Channel.ch2.motor_pulse)){ //电机转过了那么多圈，就应该发那么多药
							DEVICE2_MOTOR_STOP;	
							Channel.ch2.motor_state	= 0;	
							Channel.ch2.motor_irqstate = 0;						
						}
					}else if((Channel.ch2.state ==RESERVE)||(Channel.ch2.state == END)){
						DEVICE2_MOTOR_STOP;	
						Channel.ch2.motor_state	= 0;	
				}
			}else{
				DEVICE2_MOTOR_STOP;	//从机模式只要转到原点就停止
				Channel.ch2.motor_state	= 0;
			}
		EXTI_ClearITPendingBit(EXTI_Line12);
	}else if(EXTI_GetITStatus(EXTI_Line14) != RESET){
		if(MCU_State == HOST){
				if((Channel.ch2.send_actual_irqstate == 0)&&(Channel.ch2.state == WORKING)){//延时方法使用定时器延时，中断进来看状态，8MS后判断状态是否是真					
						Channel.ch2.send_actual_irqstate = 1;	
						Channel.ch2.send_actual_irqtime = 0;
				}
			}
		EXTI_ClearITPendingBit(EXTI_Line14);
	}else{
		EXTI_ClearITPendingBit(EXTI_Line11);
		EXTI_ClearITPendingBit(EXTI_Line13);
		EXTI_ClearITPendingBit(EXTI_Line15);
	}
}
//=============================================================================
//函数名称:Motor_pulse_IRQTimer
//功能概要:电机原点脉冲中断延时检测函数 
//参数名称:无
//函数返回:无
//注意    :必须在2ms定时器中断服务函数中调用
//=============================================================================
void 	Motor_pulse_IRQTimer(void)
{
	Motor1_pulse_IRQTimer();
	Motor2_pulse_IRQTimer();
	Motor3_pulse_IRQTimer();
	Motor4_pulse_IRQTimer();
#if CHANNEL_4 == 0
	Motor5_pulse_IRQTimer();
#endif	

}
//=============================================================================
//函数名称:Device_Send_Actual_IRQTimer
//功能概要:所有通道实际发药数计数脉冲软件延时检测
//参数名称:无
//函数返回:无
//注意    :必须在5ms定时器中断服务函数中调用
//=============================================================================
void 	Device_Send_Actual_IRQTimer(void)
{
	Device1_Send_Actual_IRQTimer();
	Device2_Send_Actual_IRQTimer();
	Device3_Send_Actual_IRQTimer();
	Device4_Send_Actual_IRQTimer();
#if CHANNEL_4 ==0
	Device5_Send_Actual_IRQTimer();
#endif
}






