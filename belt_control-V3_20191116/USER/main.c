#include"HeadType.h"
#include "usart.h"
#include "TIM.h"

void test_mode_init_belt(void);
void delay_ms1(u16 ms)
{
    u16  i;
    u32  j;
    for (i = ms; i > 0; i--) {
        for (j = 5000; j > 0; j--)
            ;
    }
}

//配置时钟在target宏定义
int main(void)
{
    static u8 testmode = 0;
    delay_init(168);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
    Belt11_Config();
    Belt12_Config();
    LED_GPIO_Config();
    KEY_GPIO_Config();
    USART1_Config();
    USART2_Config();
    belt11.actual_time = switch_init_time();
    belt12.actual_time = switch_init_time();
    TIM2_Config();
    TIM3_Config();
    delay_ms(100);
    while (1) {
        if (Key_ScanNum == 0x11) {
            Belt11_Speed(0, 1, 1);
            Belt12_Speed(0, 1, 1);
            test_mode_init_belt();
            Key_ScanNum = 0;
            testmode = 1;
        } else if (Key_ScanNum == 0x01) {
            Belt11_Speed(0, 0, 0);
            Belt12_Speed(0, 0, 0);
            Key_ScanNum = 0;
            testmode = 0;
            Usart2_Control_Data.rx_count = 0;
            Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
            Usart2_Control_Data.rx_aframe = 0;
        }else {
            Key_ScanNum = 0;
        }
        if (testmode == 0) {
            Communication_Process();
            Belt11_Control();
            Belt12_Control();
        }
    }
}

void test_mode_init_belt(void)
{
    belt11.speed_step = 0;
    belt11.start_ok = 0;
    belt11.start_signal = 0;
    belt11.stop_signal  = 0;
    belt11.stop_ok = 0;
    belt11.stop_delay_state = 0;

    belt12.speed_step = 0;
    belt12.start_ok = 0;
    belt12.start_signal = 0;
    belt12.stop_signal  = 0;
    belt12.stop_ok = 0;
    belt12.stop_delay_state = 0;
}


