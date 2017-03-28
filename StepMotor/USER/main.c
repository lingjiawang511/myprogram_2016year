#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"


void delay_ms1(u16 ms)
{
	u16  i;
	u32  j;
	for(i=ms;i>0;i--)
	{
		for(j=5000;j>0;j--)
		;
	}
}
//配置时钟在target宏定义
int main(void)
{	
 	delay_init();
	LED_GPIO_Config();
	BEEP_GPIO_Config();
	stepmotor_GPIO_Config();
    USART1_Config();
    USART2_Config();
    TIM2_Config();
    TIM3_Config(9);
    printf("STM32 code scanner0\r\n");
    USART2_Puts("HELLO");
//	Motor_Soft_Start(200,Step_Motor.frequency,3,10);
	Motor_Soft_Start(50,Step_Motor.frequency,50,20);
	delay_ms(1000);delay_ms(1000);delay_ms(1000);
	delay_ms(1000);delay_ms(1000);delay_ms(1000);
	Motor_Soft_Stop(Step_Motor.frequency,10,5);
	delay_ms(1000);delay_ms(1000);delay_ms(1000);
	delay_ms(1000);delay_ms(1000);delay_ms(1000);
	Motor_Step_Pules(2000,10000,1);
    while(1){

    }     
}




