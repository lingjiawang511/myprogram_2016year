#include"HeadType.h"	
#include "usart.h"
#include "TIM.h"
// #include "SHT2x.h"
#include "SHT3x.h"
// nt16 sT;
// float temperatureC;
char temperatureOutstr[21];
// nt16 sRH;
// float humidityRH;
char humidityOutstr[21];
// u8 error = 0;
// u8 userRegister;
// u8 endOfBattery;
// u8 serialNumber_SHT2x[8];

  etError   error;       // error code
  u32t      serialNumber;// serial number
  regStatus status;      // sensor status
  ft        temperature; // temperature [癈]
  ft        humidity;    // relative humidity [%RH]
  bt        heater;      // heater, false: off, true: on
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
    SHT3X_Init(0x45);
// 		AT24CXX_Init();
//     USART1_Config();
    LED_GPIO_Config();
    delay_ms(500);
//     KEY_GPIO_Config();
//     TIM2_Config();
//     TIM3_Config();
//     error = 0;
//     error |= SHT2x_SoftReset();
//     error |= SHT2x_GetSeriaNumber(serialNumber_SHT2x);
//     error |= SHT2x_ReadUserRegister(&userRegister);
//     userRegister = (userRegister &~SHT2X_RES_MASK)|(SHT2x_RES_12_14BIT);
//     error |= SHT2x_WriteUserRegister(&userRegister);  
      error = SHT3x_ReadSerialNumber(&serialNumber);
      if(error != NO_ERROR){} // do error handling here
      
      // demonstrate a single shot measurement with clock-stretching
      error = SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_CLKSTRETCH, 50);
      if(error != NO_ERROR){} // do error handling here 
      
      // demonstrate a single shot measurement with polling and 50ms timeout
      error = SHT3X_GetTempAndHumi(&temperature, &humidity, REPEATAB_HIGH, MODE_POLLING, 50);
      if(error != NO_ERROR){} // do error handling here 
	delay_ms(100);
    while(1){
//         error = 0;         
//         sprintf(humidityOutstr,"RH:%6.2f %%",humidityRH);
//         sprintf(temperatureOutstr," T:%6.2f %C",temperatureC);
//         LCD_P8x16Str(0,2,(u8 *)humidityOutstr);
//         LCD_P8x16Str(0,4,(u8 *)temperatureOutstr);
//         if(error != 0){
//             LCD_P8x16Str(0,0,"Error occurred");
//             LCD_P8x16Str(0,2,"RH: --.-- %%"); 
//             LCD_P8x16Str(0,4," T: --.-- %C");             
//         }else if (endOfBattery){
//             LCD_P8x16Str(0,0,"Low Battery   ");
//         }else{
//             LCD_P8x16Str(0,0,"              ");
//         }
   error = NO_ERROR;
    
    // loop while no error
    while(error == NO_ERROR)
    {
      // read status register
      error |= SHT3X_ReadStatus(&status.u16);
      if(error != NO_ERROR) break;
      
      // check if the reset bit is set after a reset or power-up
      if(status.bit.ResetDetected)
      {
        //override default temperature and humidity alert limits (red LED)
        error = SHT3X_SetAlertLimits( 70.0f,  50.0f,  // high set:   RH [%], T [癈]
                                      68.0f,  48.0f,  // high clear: RH [%], T [癈]
                                      32.0f,  -2.0f,  // low clear:  RH [%], T [癈]
                                      30.0f,  -4.0f); // low set:    RH [%], T [癈]
		    if(error != NO_ERROR) break;
		
        
        // clear reset and alert flags
        error = SHT3X_ClearAllAlertFlags();
        if(error != NO_ERROR) break;
        
        //start periodic measurement, with high repeatability and 1 measurements per second
        error = SHT3X_StartPeriodicMeasurment(REPEATAB_HIGH, FREQUENCY_1HZ);
        if(error != NO_ERROR) break;
        
        //switch green LED on
      }  
      // read measurment buffer
      error = SHT3X_ReadMeasurementBuffer(&temperature, &humidity);
      if(error == NO_ERROR){
        sprintf(humidityOutstr,"RH:%6.2f %%",humidity);
        sprintf(temperatureOutstr," T:%6.2f %C",temperature);
        LCD_P8x16Str(0,2,(u8 *)humidityOutstr);
        LCD_P8x16Str(0,4,(u8 *)temperatureOutstr);
        if(error != 0){
            LCD_P8x16Str(0,0,"Error occurred");
            LCD_P8x16Str(0,2,"RH: --.-- %%"); 
            LCD_P8x16Str(0,4," T: --.-- %C");             
        }else{
            LCD_P8x16Str(0,0,"              ");
        }
        // flash blue LED to signalise new temperature and humidity values
      }else if (error == ACK_ERROR)
      {
        // there were no new values in the buffer -> ignore this error
        error = NO_ERROR;
      }else break;
      // read heater status
      heater = status.bit.HeaterStatus ? TRUE : FALSE;

      // wait 100ms
      delay_ms(100);
    }
    
    // in case of an error ...
    
    // ... switch green and blue LED off
    
    // ... try first a soft reset ...
    error = SHT3X_SoftReset();
    
    // ... if the soft reset fails, do a hard reset
    if(error != NO_ERROR)
    {
      SHT3X_HardReset();
    }        
    GLED_ON;
    delay_ms(1000);
    GLED_OFF;
    }       
}




