#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"
u32 pwm_test = 0;
u8 pwm_send_complete;
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
		KEY_GPIO_Config();
    Motor_Init(0,0,0);
		delay_ms(100);   
    TIM2_TIM3_PWM(1000,300);
    while(1){
      if(pwm_send_complete == 1){
          if(pwm_test < 3){
            TIM2_TIM3_PWM(400,300);  
          }else if((3 <= pwm_test)&&( pwm_test< 6)){
            TIM2_TIM3_PWM(400,300);
          }else if((6 <= pwm_test)&&( pwm_test< 10)){
            TIM2_TIM3_PWM(400,300); 
          }else{
            TIM2_TIM3_PWM(400,300); 
            pwm_test = 0;
          }     
        }
      }
		
        
}




