#include "Headtype.h"

u8 Speed_Step;
u8 Start_Signal;
u8 Stop_Signal;
u8 Start_Ok;
u8 Stop_Ok;
u8 Stop_Delay;
//=============================================================================
//函数名称:SYSCLK_Init
//功能概要:系统初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void SYSCLK_Init (void)
{
    unsigned char i;
    PCA0MD &= ~0x40; // WDTE = 0 (clear watchdog timer
    OSCICN = 0x80;                         // enable intosc
    CLKSEL = 0x00;                         // select intosc as sysclk source
// INTOSC configure
    OSCICN = 0x83;
// PLL configure
    CLKMUL = 0x00;                         // Reset Clock Multiplier
    CLKMUL &= ~0x03;                       // select INTOSC / 2 as PLL source
    CLKMUL |= 0x80;                        // Enable 4x Multipler (MULEN = 1)
    for (i = 0; i < 200; i++);             // Delay for at least 5us
    CLKMUL |= 0xC0;                        // Initialize Multiplier
   while (!(CLKMUL & 0x20));              // Poll for Multiply Ready
// SYSCLK configure
    VDM0CN = 0x80;                         // enable VDD monitor
    RSTSRC = 0x06;                         // enable missing clock detector
    // and VDD monitor reset sources
    CLKSEL = 0x02;                         // select PLL as clock source
    XBR1|=0X40;                            //enable SKIP
}
//=============================================================================
//函数名称:IOInit
//功能概要:IO口初始化
//参数名称:无
//函数返回:无
//注意    :无
//=============================================================================
void IOInit(void)
{
    P0MDIN |=0XFF;    //IO口模式
    P0MDOUT |=0xFF;  //推挽输出
    P0SKIP &=0x00;	 //不跳过交叉编译
    P1MDIN |=0XFF;    //IO口模式
    P1MDOUT &=0x00;  //按键输入
    P1SKIP &=0x00;	 //不跳过交叉编译
    P2MDIN |=0XFF;    //IO口模式
    P2MDOUT |=0xFF;  //推挽输出
    P2SKIP &=0x00;	 //不跳过交叉编译	
}
void main(void)
{
	SYSCLK_Init ();
	IOInit();
	Timer0Init();
	Motor_Speed_Control(0);
// 	Control_Power = POWER_ON;
	Control_Power1 = POWER_ON;
	Stop_Signal  = 0;
	Start_Signal = 0;
	Sensor = 1;
	Delay_ms(1000);
	while(1)
	{
		if(Sensor == 0){
			Delay_ms(10);	
			if(Sensor == 0){
				if(Start_Signal == 0){
					Start_Signal = 1;	
					Stop_Signal  = 0;
					Control_Power = POWER_ON; 
					Start_Ok = 0;
					Stop_Ok = 0;
					Stop_Delay = 0;
					LED0 = 0;
					if(Speed_Step>0){
						Speed_Step--; 
					}
				}
			}
		}else{
			if(Start_Ok == 1){
				Stop_Delay = 1;
				Start_Ok = 0;
				Start_Signal = 0;
			}
			if(Stop_Ok == 1){
				Stop_Signal = 1;
				Start_Signal = 0;
				Stop_Ok = 0;
			}
		}
		
	}
}


