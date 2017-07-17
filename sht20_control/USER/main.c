#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"
#include "SHT2x.h"

nt16 sT;
float temperatureC;
char temperatureOutstr[21];
nt16 sRH;
float humidityRH;
char humidityOutstr[21];
u8 error = 0;
u8 userRegister;
u8 endOfBattery;
u8 serialNumber_SHT2x[8];

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
    initial_lcd();
    clear_screen(0x00);    //clear all dots
    I2C_INIT();		 //IIC初始化
// 		AT24CXX_Init();
//     USART1_Config();
//     LED_GPIO_Config();
//     KEY_GPIO_Config();
//     TIM2_Config();
//     TIM3_Config();
    error = 0;
    error |= SHT2x_SoftReset();
    error |= SHT2x_GetSeriaNumber(serialNumber_SHT2x);
    error |= SHT2x_ReadUserRegister(&userRegister);
    userRegister = (userRegister &~SHT2X_RES_MASK)|(SHT2x_RES_12_14BIT);
    error |= SHT2x_WriteUserRegister(&userRegister);  
	delay_ms(100);
    while(1){
        error = 0;         
        error |= SHT2x_MeasurePoll(HUMIDITY,&sRH);
        error |= SHT2x_MeasurePoll(TEMP,&sT);
        temperatureC = SHT2x_CalcTemperatureC(sT.u16);
        humidityRH = SHT2x_CalcRH(sRH.u16);
        error |= SHT2x_ReadUserRegister(&userRegister);
        if((userRegister & SHT2X_EOB_MASK) == SHT2X_EOB_ON){
            endOfBattery = true;
        }else{
            endOfBattery = false;
        }
        sprintf(humidityOutstr,"RH:%6.2f %%",humidityRH);
        sprintf(temperatureOutstr," T:%6.2f %C",temperatureC);
        LCD_P8x16Str(0,2,(u8 *)humidityOutstr);
        LCD_P8x16Str(0,4,(u8 *)temperatureOutstr);
        if(error != 0){
            LCD_P8x16Str(0,0,"Error occurred");
            LCD_P8x16Str(0,2,"RH: --.-- %%"); 
            LCD_P8x16Str(0,4," T: --.-- %C");             
        }else if (endOfBattery){
            LCD_P8x16Str(0,0,"Low Battery   ");
        }else{
            LCD_P8x16Str(0,0,"              ");
        }
        delay_ms(1000);
    }       
}




