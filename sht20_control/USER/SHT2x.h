#ifndef SHT2X_H
#define SHT2X_H

#include"HeadType.h"


//sensor command
typedef enum{
    TRIG_T_MEASUREMENT_HM      = 0XE3, //command trig.temp meas.hold master
    TRIG_RH_MEASUREMENT_HM     = 0XE5, //command trig humidity meas. hold master
    TRIG_T_MEASUREMENT_POLL    = 0XF3, //command trig tempmeas . no hold master
    TRIG_RH_MEASUREMENT_POLL   = 0XF5, //command trig humidity meas. no hold master
    USER_REG_W                 = 0XE6, //command writing user register
    USER_REG_R                 = 0XE7, //copmmand reading user register
    SOFT_RESET                 = 0XFE, //command soft reset
}etSHT2xCommand;

typedef enum{
    SHT2x_RES_12_14BIT         = 0X00, //RH=12bit,T=14bit
    SHT2X_RES_8_12BIT          = 0X01, //RH=8bit,T=12bit
    SHT2X_RES_10_13BIT         = 0X80, //RH=10bit,T=13bit
    SHT2X_RES_11_11BIT         = 0X81, //RH=11bit,T=11bit
    SHT2X_RES_MASK             = 0X81, //Mask for res. bit (7,0)in user reg.
}etSHT2xResolution;

typedef enum{
    SHT2X_EOB_ON               = 0X40, //end of battery
    SHT2X_EOB_MASK             = 0X40, //Mask for EOB bit(6) in user reg
}etSHT2xEob;

typedef enum{
    SHT2X_HEATER_ON            = 0X04, //heater on
    SHT2X_HEATER_OFF           = 0X00, //heater off
    SHT2X_HEATER_MASK          = 0X04, //Mask for Heater bit(2) in user reg
}etSHT2xHeater;

//measurement signal selection
typedef enum{
    HUMIDITY,
    TEMP,
}etSHT2xMeasureType;

typedef enum{
    I2C_ADR_W                  = 128, //sensor I2C address + write bit
    I2C_ADR_R                  = 129, //sensor I2C address + read bit
}etI2cHeader;

typedef enum{
    ACK_ERROR                  = 0X01,
    TIME_OUT_ERROR             = 0X02,
    CHECKSUM_ERROR             = 0X04,
    UNIT_ERROR                 =0X08,
}etError;


u8 SHT2x_CheckCrc(u8 data[],u8 nbrOfBytes,u8 checksum);
u8 SHT2x_ReadUserRegister(u8 *pRegisterValue);
u8 SHT2x_WriteUserRegister(u8 *pRegisterValue);
u8 SHT2x_MeasurePoll(etSHT2xMeasureType eSHT2xMeasureType,nt16 *pMeasurand);
u8 SHT2x_MeasureHM(etSHT2xMeasureType eSHT2xMeasureType,nt16 *pMeasurand);
u8 SHT2x_SoftReset(void);

float SHT2x_CalcRH(u16 u16sRH);
float SHT2x_CalcTemperatureC(u16 u16sT);
u8 SHT2x_GetSeriaNumber(u8 u8SerialNumber[]);






#endif

