#ifndef __TIM_H
#define __TIM_H
#include "stm32f10x.h"

void TIM2_Config(void );
void TIM3_Config(u16 arr);
void PWM_SetFre(u32 fre);
void TIM3_PWM_Init(u16 arr,u16 psc);
#endif
