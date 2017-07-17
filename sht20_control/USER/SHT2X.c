#include "SHT2x.h"
#include "24cxx.h" 

//CRC
const u16 POLYNOMIAL = 0x131;   //P(x) = x^8+x^5+x^4+1=100110001


u8 SHT2x_CheckCrc(u8 data[],u8 nbrOfBytes,u8 checksum)
{
    u8 crc = 0;
    u8 byteCtr;
    u8 bit;
    for(byteCtr = 0;byteCtr < nbrOfBytes;++byteCtr){
        crc ^= (data[byteCtr]);
        for(bit = 8;bit > 0;--bit){
            if(crc&0x80){
                crc = (crc << 1)^POLYNOMIAL;
            }else{
                crc = crc <<1;
            }
        }
    }
    if(crc != checksum ){
        return CHECKSUM_ERROR;
    }else{
        return 0;
    }
}

u8 SHT2x_ReadUserRegister(u8 *pRegisterValue)
{
    u8 checksum;    //variable for checksum byte
    u8 error = 0;   //variable for error code
    
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_W);
    error |= I2C_WriteByte(USER_REG_R);
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_R);
    *pRegisterValue = I2C_ReadByte(NO_ACK);
//     checksum =  I2C_ReadByte(NO_ACK);
//     error = SHT2x_CheckCrc(pRegisterValue,1,checksum );
    I2C_Stop();
    return error;
}

u8 SHT2x_WriteUserRegister(u8 *pRegisterValue)
{
    u8 error = 0;   //variable for error code
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_W);
    error |= I2C_WriteByte(USER_REG_W); 
    error |= I2C_WriteByte(*pRegisterValue);
    I2C_Stop();
    return error;   
}

u8 SHT2x_MeasureHM(etSHT2xMeasureType eSHT2xMeasureType,nt16 *pMeasurand)
{
    u8 checksum;
    u8 data[2];
    u8 error = 0;
    u16 i = 0;
    
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_W);
    switch(eSHT2xMeasureType){
        case HUMIDITY: 
            error |= I2C_WriteByte(TRIG_RH_MEASUREMENT_HM);
            break;
        case TEMP:
            error |= I2C_WriteByte(TRIG_T_MEASUREMENT_HM);
            break;
        default:
            break;
    }
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_R);
    I2C_SCL_IN();
    for(i = 0; i< 1000;i++){
        delay_nms(2);
        if(Read_I2C_SCL != 0){
            break;
        }
    }
    if(Read_I2C_SCL == 0){
        error |= TIME_OUT_ERROR;
        I2C_Stop();
        return error;
    }
    I2C_SCL_OUT();
    pMeasurand->s16.u8H = data[0] = I2C_ReadByte(ACK);
    pMeasurand->s16.u8L = data[1] = I2C_ReadByte(ACK);
    checksum =  I2C_ReadByte(NO_ACK);
    error |= SHT2x_CheckCrc(data,2,checksum);
    I2C_Stop();
    return error;    
}

u8 SHT2x_MeasurePoll(etSHT2xMeasureType eSHT2xMeasureType,nt16 *pMeasurand)
{
    u8 checksum;
    u8 data[2];
    u8 error = 0;
    u16 i = 0;
    
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_W);
    delay_nms(5);
    switch(eSHT2xMeasureType){
        case HUMIDITY: 
            error |= I2C_WriteByte(TRIG_RH_MEASUREMENT_POLL);
            break;
        case TEMP:
            error |= I2C_WriteByte(TRIG_T_MEASUREMENT_POLL);
            break;
        default:
            break;
    }
    I2C_Stop();
    do{
        delay_nms(10);
        I2C_Start();  
        error = I2C_WriteByte(I2C_ADR_R);        
        if(i++ >=20){
            break;
        }
    }while(error == ACK_ERROR);
    if(i > 20){
        error |= TIME_OUT_ERROR ;
        I2C_Stop();
        return error;
    }

    pMeasurand->s16.u8H = data[0] = I2C_ReadByte(ACK);
    pMeasurand->s16.u8L = data[1] = I2C_ReadByte(ACK);
    checksum =  I2C_ReadByte(NO_ACK);
    I2C_Stop();
    error |= SHT2x_CheckCrc(data,2,checksum); 
    return error;    
}

u8 SHT2x_SoftReset(void)
{
    u8 error = 0;
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_W);
    error |= I2C_WriteByte(SOFT_RESET);
    delay_nms(50);  //wait till sensor has restarted
    I2C_Stop();
    return error;
}

float SHT2x_CalcRH(u16 u16sRH)
{
    float humidityRH;
    
    u16sRH &= ~0x0003;  //clear bits[1..0] (status bits)
    //-- calculate relative humidity (%RH) --
    humidityRH = -6.0 + 125.0/65536 *(float)u16sRH;
    return humidityRH;
}

float SHT2x_CalcTemperatureC(u16 u16sT)
{
    float temperatureC;
    
    u16sT &= ~0x0003;
    
    //-- calculate tempraturn[] --
    temperatureC = -46.85 + 175.72/65536 * (float) u16sT;
    return temperatureC;
}

u8 SHT2x_GetSeriaNumber(u8 u8SerialNumber[])
{
    u8 error = 0;
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_W);
    error |= I2C_WriteByte(0xFA);
    error |= I2C_WriteByte(0X0F);
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_R);
    u8SerialNumber[5] = I2C_ReadByte(ACK);
    I2C_ReadByte(ACK);
    u8SerialNumber[4] = I2C_ReadByte(ACK);
    I2C_ReadByte(ACK);
    u8SerialNumber[3] = I2C_ReadByte(ACK);
    I2C_ReadByte(ACK);
    u8SerialNumber[2] = I2C_ReadByte(ACK);
    I2C_ReadByte(NO_ACK);
    I2C_Stop();
    
    I2C_Start();
    error |= I2C_WriteByte(I2C_ADR_W);
    error |= I2C_WriteByte(0xFC);
    error |= I2C_WriteByte(0XC9);
    I2C_Start(); 
    error |= I2C_WriteByte(I2C_ADR_R);
    u8SerialNumber[1] = I2C_ReadByte(ACK);  
    u8SerialNumber[0] = I2C_ReadByte(ACK);
    I2C_ReadByte(ACK);  
    u8SerialNumber[7] = I2C_ReadByte(ACK);  
    u8SerialNumber[6] = I2C_ReadByte(ACK);
    I2C_ReadByte(NO_ACK);     
    I2C_Stop();   
    return error;
}









