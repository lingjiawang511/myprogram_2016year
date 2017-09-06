#ifndef __TIM_H
#define __TIM_H
#include "stm32f10x.h"

void TIM2_Config(void );
void TIM3_Config(void );
void TIM4_Config(void);
void Motor_Init(u16 TIM2per, u16 TIM3per, u16 TIM3Compare1);
void TIM2_TIM3_PWM(u16 Cycle, u16 Pulse_Num);

#endif
