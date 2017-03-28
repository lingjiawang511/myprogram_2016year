#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

#include "stm32f10x.h"

#define       Motor_DIR_ON   		GPIO_SetBits(GPIOB, GPIO_Pin_8)
#define       Motor_DIR_OFF 		GPIO_ResetBits(GPIOB, GPIO_Pin_8)
#define       Motor_EN_ON   		GPIO_SetBits(GPIOB, GPIO_Pin_7)
#define       Motor_EN_OFF  		GPIO_ResetBits(GPIOB, GPIO_Pin_7)
#define       Motor_CLK_ON   		GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define       Motor_CLK_OFF  		GPIO_ResetBits(GPIOB, GPIO_Pin_9)

#define 	  Motor_Start()			Motor_EN_ON
#define 	  Motor_Stop()			Motor_EN_OFF
#define 	  Motor_GO_Forward()	Motor_DIR_ON
#define 	  Motor_Go_Back()		Motor_DIR_OFF



void stepmotor_GPIO_Config(void);
void Motor_Soft_Start(u32 startfre,u32 endfre,u8 second,u8 mode);
void Motor_Soft_Stop(u32 currentfre,u8 second,u8 mode);
void Motor_Step_Pules(u32 fre,u32 pules,u8 mode);
#endif




