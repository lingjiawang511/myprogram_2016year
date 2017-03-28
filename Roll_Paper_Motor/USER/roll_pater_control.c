#include"HeadType.h"	

//=============================================================================
//函数名称:Send_Medicine1_Config
//功能概要:发药口1相关引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Send_Medicine1_Config(void)
{
		//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//电机控制IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE1_MOTOR_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE1_MOTOR_PORT, &GPIO_InitStructure);
	//灯控制IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE1_LIGHT_IO;			 
	GPIO_Init(DEVICE1_LIGHT_PORT, &GPIO_InitStructure);
	//传感器1输入IO口
// 	GPIO_InitStructure.GPIO_Pin = DEVICE1_SENSOR1_IO;			 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DEVICE1_SENSOR1_PORT, &GPIO_InitStructure);
	//传感器2输入IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE1_SENSOR2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE1_SENSOR2_PORT, &GPIO_InitStructure);
	//传感器3输入IO口
 	GPIO_InitStructure.GPIO_Pin = DEVICE1_SENSOR3_IO;			 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(DEVICE1_SENSOR3_PORT, &GPIO_InitStructure);
	//按键输入IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE1_KEY_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE1_KEY_PORT, &GPIO_InitStructure);
	
}
#if 0
//=============================================================================
//函数名称:Send_Medicine2_Config
//功能概要:发药口2相关引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Send_Medicine2_Config(void )
{
		//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//电机控制IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE2_MOTOR_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE2_MOTOR_PORT, &GPIO_InitStructure);
	//灯控制IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE2_LIGHT_IO;			 
	GPIO_Init(DEVICE2_LIGHT_PORT, &GPIO_InitStructure);
	//传感器1输入IO口
// 	GPIO_InitStructure.GPIO_Pin = DEVICE2_SENSOR1_IO;			 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DEVICE2_SENSOR1_PORT, &GPIO_InitStructure);
	//传感器2输入IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE2_SENSOR2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE2_SENSOR2_PORT, &GPIO_InitStructure);
	//传感器3输入IO口
// 	GPIO_InitStructure.GPIO_Pin = DEVICE2_SENSOR3_IO;			 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DEVICE2_SENSOR3_PORT, &GPIO_InitStructure);
	//按键输入IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE2_KEY_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE2_KEY_PORT, &GPIO_InitStructure);
}

//=============================================================================
//函数名称:Send_Medicine3_Config
//功能概要:发药口3相关引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Send_Medicine3_Config(void)
{
		//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//电机控制IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE3_MOTOR_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE3_MOTOR_PORT, &GPIO_InitStructure);
	//灯控制IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE3_LIGHT_IO;			 
	GPIO_Init(DEVICE3_LIGHT_PORT, &GPIO_InitStructure);
	//传感器1输入IO口
// 	GPIO_InitStructure.GPIO_Pin = DEVICE3_SENSOR1_IO;			 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DEVICE3_SENSOR1_PORT, &GPIO_InitStructure);
	//传感器2输入IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE3_SENSOR2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE3_SENSOR2_PORT, &GPIO_InitStructure);
	//传感器3输入IO口
// 	GPIO_InitStructure.GPIO_Pin = DEVICE3_SENSOR3_IO;			 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DEVICE3_SENSOR3_PORT, &GPIO_InitStructure);
	//按键输入IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE3_KEY_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE3_KEY_PORT, &GPIO_InitStructure);
}
//=============================================================================
//函数名称:Send_Medicine4_Config
//功能概要:发药口4相关引脚配置
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Send_Medicine4_Config(void)
{
		//定义一个GPIO_InitTypeDef 类型的结构体，名字叫GPIO_InitStructure 
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	//电机控制IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE4_MOTOR_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE4_MOTOR_PORT, &GPIO_InitStructure);
	//灯控制IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE4_LIGHT_IO;			 
	GPIO_Init(DEVICE4_LIGHT_PORT, &GPIO_InitStructure);
	//传感器1输入IO口
// 	GPIO_InitStructure.GPIO_Pin = DEVICE4_SENSOR1_IO;			 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DEVICE4_SENSOR1_PORT, &GPIO_InitStructure);
	//传感器2输入IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE4_SENSOR2_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE4_SENSOR2_PORT, &GPIO_InitStructure);
	//传感器3输入IO口
// 	GPIO_InitStructure.GPIO_Pin = DEVICE4_SENSOR3_IO;			 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(DEVICE4_SENSOR3_PORT, &GPIO_InitStructure);
	//按键输入IO口
	GPIO_InitStructure.GPIO_Pin = DEVICE4_KEY_IO;			 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(DEVICE4_KEY_PORT, &GPIO_InitStructure);
}
#endif
//=============================================================================
//函数名称:CH_Param_Init
//功能概要:每个通道相关参数的初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void CH_Param_Init(void)
{
	Channel.ch1.state = RESERVE;
	Channel.ch2.state = RESERVE;
	Channel.ch3.state = RESERVE;
	Channel.ch4.state = RESERVE;
}
//=============================================================================
//函数名称:Param_Init
//功能概要:初始化变量和参数
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Param_Init(void)
{
	MCU_State = SLAVE;
	PC_Answer.Nanswer_timeout = NANSWER_TIME;
	PC_Answer.answer_numout = NANSWER_NUMOUT;
	PC_Answer.answer_state =0;	
	Usart1_Control_Data.rx_aframe = 0;
	Channel.ch1.motor_state = 0;
	Channel.ch2.motor_state = 0;
	Channel.ch3.motor_state = 0;
	Channel.ch4.motor_state = 0;
	Channel.ch1.timeoutstart = 0;
	Channel.ch2.timeoutstart = 0;
	Channel.ch3.timeoutstart = 0;
	Channel.ch4.timeoutstart = 0;
	Channel.ch1.timeout = 0;
	Channel.ch2.timeout = 0;
	Channel.ch3.timeout = 0;
	Channel.ch4.timeout = 0;
	CH_Param_Init();
}

//=============================================================================
//函数名称:Send_Medicine_Config
//功能概要:初始化所有通道
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void Roll_Pater_Config(void)
{
	Send_Medicine1_Config();
	#if 0
	Send_Medicine2_Config();
	Send_Medicine3_Config();
	Send_Medicine4_Config();
	#endif
	Param_Init();
}
//=============================================================================
//函数名称:Roll_Pater_Motor_Run
//功能概要:所有通道的电机中断启动
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Roll_Pater_Motor_Run(void)
{
	#if 0
	if(Channel.ch1.motor_start_state == 1){
		if(Channel.ch1.send_actual >= 1){
//				DEVICE1_MOTOR_RUN;
				Channel.ch1.motor_state = 1;
				Channel.ch1.send_actual = 0;
		}
	}else{
			  Channel.ch1.send_actual = 0;
	}
	if(Channel.ch2.motor_start_state == 1){
		if(Channel.ch2.send_actual >= 1){
//				DEVICE2_MOTOR_RUN;
				Channel.ch2.motor_state = 1;
				Channel.ch2.send_actual = 0;
		}
	}else{
				Channel.ch2.send_actual = 0;
	}
	if(Channel.ch3.motor_start_state == 1){
		if(Channel.ch3.send_actual >= 1){
//				DEVICE3_MOTOR_RUN;
				Channel.ch3.motor_state = 1;
				Channel.ch3.send_actual = 0;
		}
	}else{
			 Channel.ch3.send_actual = 0;
	}
	if(Channel.ch4.motor_start_state == 1){
		if(Channel.ch4.send_actual >= 1){
//				DEVICE4_MOTOR_RUN;
				Channel.ch4.motor_state = 1;
				Channel.ch4.send_actual = 0;
		}
	}else{
				Channel.ch4.send_actual = 0;
	}
	/********查询方式启动电机*********/
	if((READ_DEVICE1_SENSOR2 == READLOW)||(READ_DEVICE2_SENSOR2 == READLOW)\
			||(READ_DEVICE3_SENSOR2 == READLOW)||(READ_DEVICE4_SENSOR2 == READLOW)){	//传感器有信号时为低电平
			delay_ms(5);
			if((READ_DEVICE1_SENSOR2 == READLOW)||(READ_DEVICE2_SENSOR2 == READLOW)\
				||(READ_DEVICE3_SENSOR2 == READLOW)||(READ_DEVICE4_SENSOR2 == READLOW)){	//传感器有信号时为低电平
			  if(Channel.ch1.motor_start_state == 1){
					if(READ_DEVICE1_SENSOR2 == READLOW){
//							DEVICE1_MOTOR_RUN;
							Channel.ch1.motor_state = 1;
					}
				}
				if(Channel.ch2.motor_start_state == 1){
					if(READ_DEVICE2_SENSOR2 == READLOW){
//							DEVICE2_MOTOR_RUN;
							Channel.ch2.motor_state = 1;
					}
				}
				if(Channel.ch3.motor_start_state == 1){
					if(READ_DEVICE3_SENSOR2 == READLOW){
//							DEVICE3_MOTOR_RUN;
							Channel.ch3.motor_state = 1;
					}
				}
				if(Channel.ch4.motor_start_state == 1){
					if(READ_DEVICE4_SENSOR2 == READLOW){
//							DEVICE4_MOTOR_RUN;
							Channel.ch4.motor_state = 1;
					}
				}
		}
	}	
#endif
		
	if(Channel.ch1.motor_start_state == 1){
			if(READ_DEVICE1_SENSOR2 == READLOW){	//PNP传感器
				delay_ms(5);
				if(READ_DEVICE1_SENSOR2 == READLOW){
//							DEVICE1_MOTOR_RUN;
						//	delay_ms(1000);
					
							Channel.ch1.motor_state = 1;
					}else{
							Channel.ch1.motor_state = 0;
					}
				}else{
						Channel.ch1.motor_state = 0;
				}
			}else{
					Channel.ch1.motor_state = 0;
			}		
#if 0	
	if(Channel.ch1.motor_start_state == 1){	//NPN传感器
			if(READ_DEVICE1_SENSOR3 == READLOW){
				delay_ms(5);
				if(READ_DEVICE1_SENSOR3 == READLOW){
//							DEVICE1_MOTOR_RUN;
						//	delay_ms(1000);
					
							Channel.ch1.motor_state = 1;
					}else{
							Channel.ch1.motor_state = 0;
					}
				}else{
						Channel.ch1.motor_state = 0;
				}
			}
#endif
#if 0		
		/********查询方式启动电机*********/
	if((READ_DEVICE1_SENSOR3 == READLOW)||(READ_DEVICE2_SENSOR3 == READLOW)\
			||(READ_DEVICE3_SENSOR3 == READLOW)||(READ_DEVICE4_SENSOR3 == READLOW)){	//传感器有信号时为低电平
			delay_ms(2);
			if((READ_DEVICE1_SENSOR3 == READLOW)||(READ_DEVICE2_SENSOR3 == READLOW)\
				||(READ_DEVICE3_SENSOR3 == READLOW)||(READ_DEVICE4_SENSOR3 == READLOW)){	//传感器有信号时为低电平
			  if(Channel.ch1.motor_start_state == 1){
					if(READ_DEVICE1_SENSOR3 == READLOW){
//							DEVICE1_MOTOR_RUN;
							Channel.ch1.motor_state = 1;
					}
				}
				if(Channel.ch2.motor_start_state == 1){
					if(READ_DEVICE2_SENSOR3 == READLOW){
//							DEVICE2_MOTOR_RUN;
							Channel.ch2.motor_state = 1;
					}
				}
				if(Channel.ch3.motor_start_state == 1){
					if(READ_DEVICE3_SENSOR3 == READLOW){
//							DEVICE3_MOTOR_RUN;
							Channel.ch3.motor_state = 1;
					}
				}
				if(Channel.ch4.motor_start_state == 1){
					if(READ_DEVICE4_SENSOR3 == READLOW){
//							DEVICE4_MOTOR_RUN;
							Channel.ch4.motor_state = 1;
					}
				}
		}
	}
	#endif
}
#if 0
//=============================================================================
//函数名称:Roll_Pater_Motor_Stop
//功能概要:所有通道的电机查询停止
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
static void Roll_Pater_Motor_Stop(void)
{
		/********查询方式停止电机*********/
	if((READ_DEVICE1_SENSOR1 == READLOW)||(READ_DEVICE2_SENSOR1 == READLOW)\
			||(READ_DEVICE3_SENSOR1 == READLOW)||(READ_DEVICE4_SENSOR1 == READLOW)){	//传感器有信号时为低电平
			delay_ms(5);
			if((READ_DEVICE1_SENSOR1 == READLOW)||(READ_DEVICE2_SENSOR1 == READLOW)\
				||(READ_DEVICE3_SENSOR1 == READLOW)||(READ_DEVICE4_SENSOR1 == READLOW)){	
			if(READ_DEVICE1_SENSOR1 == READLOW){
//				DEVICE1_MOTOR_SOFT_STOP;	//从机模式只要转到原点就停止
				if(Channel.ch1.motor_state == 1){
					Channel.ch1.motor_state	= 0;
				}
			}
			if(READ_DEVICE2_SENSOR1 == READLOW){
//				DEVICE2_MOTOR_SOFT_STOP;	//从机模式只要转到原点就停止
				Channel.ch2.motor_state	= 0;
			}
			if(READ_DEVICE3_SENSOR1 == READLOW){
//				DEVICE3_MOTOR_SOFT_STOP;	//从机模式只要转到原点就停止
				Channel.ch3.motor_state	= 0;
			}
			if(READ_DEVICE4_SENSOR1 == READLOW){
//				DEVICE4_MOTOR_SOFT_STOP;	//从机模式只要转到原点就停止
				Channel.ch4.motor_state	= 0;
			}
		}
	}
}
#endif
//=============================================================================
//函数名称:Roll_Pater_Motor_Control
//功能概要:所有通道的电机控制
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================

void Roll_Pater_Motor_Control(void)
{ 
		Roll_Pater_Motor_Run();
//		Roll_Pater_Motor_Stop();
	
		if(Channel.ch1.motor_state == 1){		//传感器有信号就转，没有信号就停，使用电机惯性过冲卷纸
			DEVICE1_MOTOR_RUN;
			Channel.ch1.motor_run_state = 1;
		}else{
			if(Channel.ch1.motor_run_state == 1){
					DEVICE1_MOTOR_SOFT_STOP;
					Channel.ch1.motor_run_state	= 0;
				}
		}
		#if 0
		if(Channel.ch2.motor_state == 1){
			DEVICE2_MOTOR_RUN;
			Channel.ch2.motor_run_state = 1;
		}else{
			if(Channel.ch2.motor_run_state == 1){
					DEVICE2_MOTOR_SOFT_STOP;
					Channel.ch2.motor_run_state	= 0;
				}
		}
		if(Channel.ch3.motor_state == 1){
			DEVICE3_MOTOR_RUN;
			Channel.ch3.motor_run_state = 1;
		}else{
			if(Channel.ch3.motor_run_state == 1){
					DEVICE3_MOTOR_SOFT_STOP;
					Channel.ch3.motor_run_state	= 0;
				}
		}
		if(Channel.ch4.motor_state == 1){
			DEVICE4_MOTOR_RUN;
			Channel.ch4.motor_run_state = 1;
		}else{
			if(Channel.ch4.motor_run_state == 1){
					DEVICE4_MOTOR_SOFT_STOP;
					Channel.ch4.motor_run_state	= 0;
				}
		}
		#endif
}

//=============================================================================
//函数名称:CH_Key_Control
//功能概要:所有通道的按键检测
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void CH_Key_Control(void)
{
#if 0
		if(Key_ScanNum != 0x00){
				 if(0x01== (Key_ScanNum&0x01)){
					 if(Channel.ch1.motor_start_state == 0){
							Channel.ch1.motor_start_state = 1;
					 }else{
						  DEVICE1_MOTOR_SOFT_STOP;
						  Channel.ch1.motor_state = 0;
							Channel.ch1.motor_run_state	= 0;						 
							Channel.ch1.motor_start_state = 0;
							Channel.ch1.send_actual = 0;
					}
					Key_ScanNum	&=0xfe;
				}
				 if(0x02== (Key_ScanNum&0x02)){
					 if(Channel.ch2.motor_start_state == 0){
							Channel.ch2.motor_start_state = 1;
					 }else{
						  DEVICE2_MOTOR_SOFT_STOP;
						  Channel.ch2.motor_state = 0;
							Channel.ch2.motor_run_state	= 0;
							Channel.ch2.motor_start_state = 0;
						  Channel.ch2.send_actual = 0;
					}	
					Key_ScanNum	&=0xfd;					
				}
				 if(0x04== (Key_ScanNum&0x04)){
					 if(Channel.ch3.motor_start_state == 0){
							Channel.ch3.motor_start_state = 1;
					 }else{
						  DEVICE3_MOTOR_SOFT_STOP;
						  Channel.ch3.motor_state = 0;
						  Channel.ch3.motor_run_state	= 0;
							Channel.ch3.motor_start_state = 0;
						  Channel.ch3.send_actual = 0;
					}	
					Key_ScanNum	&=0xfb;					
				}
					if(0x08== (Key_ScanNum&0x08)){
					 if(Channel.ch4.motor_start_state == 0){
							Channel.ch4.motor_start_state = 1;
					 }else{
						  DEVICE4_MOTOR_SOFT_STOP;
						  Channel.ch4.motor_state = 0;
						  Channel.ch4.motor_run_state	= 0;
							Channel.ch4.motor_start_state = 0;
						  Channel.ch4.send_actual = 0;
					}	
					Key_ScanNum	&=0xf7;					
				}
				Key_ScanNum	&=0x0f;	
			}
#else
			if((READ_DEVICE1_KEY == READLOW)&&(READ_DEVICE1_SENSOR3 == READHIGH)){
				 delay_ms(5);
					if((
						READ_DEVICE1_KEY == READLOW)&&(READ_DEVICE1_SENSOR3 == READHIGH)){
						if(Channel.ch1.motor_start_state == 0){
								Channel.ch1.motor_start_state = 1;
						 }
				}else{
								DEVICE1_MOTOR_SOFT_STOP;
								Channel.ch1.motor_state = 0;					 
								Channel.ch1.motor_start_state = 0;
								Channel.ch1.send_actual = 0;
						}
			}else{
								DEVICE1_MOTOR_SOFT_STOP;
								Channel.ch1.motor_state = 0;						 
								Channel.ch1.motor_start_state = 0;
								Channel.ch1.send_actual = 0;
				}
#endif 

}
//=============================================================================
//函数名称:CH_Light_Control
//功能概要:所有通道灯的控制
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void CH_Light_Control(void )
{
	if(Channel.ch1.motor_start_state == 1 ){
			DEVICE1_LIGHT_ON;
	}else{
			DEVICE1_LIGHT_OFF;
	}
	#if 0
	if(Channel.ch2.motor_start_state == 1 ){
			DEVICE2_LIGHT_ON;
	}else{
			DEVICE2_LIGHT_OFF;
	}
	if(Channel.ch3.motor_start_state == 1 ){
			DEVICE3_LIGHT_ON;
	}else{
			DEVICE3_LIGHT_OFF;
	}
	if(Channel.ch4.motor_start_state == 1 ){
			DEVICE4_LIGHT_ON;
	}else{
			DEVICE4_LIGHT_OFF;
	}	
	#endif
}




