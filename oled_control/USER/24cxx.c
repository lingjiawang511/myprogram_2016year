#include "24cxx.h" 
#include"HeadType.h"	
// #include "delay.h"
// #include "sys.h"

void delay_nus(u32 nus)
{		
    int i;
	while(nus--){
		for(i =0 ;i<2;i++);
	} 
}
void delay_nms(u32 nms)
{
   while(nms--){
    delay_nus(1000);
    } 
}
/****************************************************************************
* Function Name  : IIC_Config
* Description    : 初始化GPIO.
* Input          : None
* Output         : None
* Return         : None
****************************************************************************/
void I2C_INIT()
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
//     RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
//     PWR_WakeUpPinCmd(DISABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟
   // GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
	GPIO_InitStructure.GPIO_Pin=I2C_SCL|I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);

	I2C_SCL_H;
	I2C_SDA_H;
}

/*******************************************************************************
* 函 数 名         : I2C_SDA_OUT
* 函数功能		   : SDA输出配置	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void I2C_SDA_OUT()
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

/*******************************************************************************
* 函 数 名         : I2C_SDA_IN
* 函数功能		   : SDA输入配置	   
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

//产生起始信号
void I2C_Start(void)
{
    I2C_SDA_OUT();
	
	I2C_SDA_H;
	I2C_SCL_H;
	delay_nus(5);
	I2C_SDA_L;
	delay_nus(6);
	I2C_SCL_L;
}

//产生停止信号
void I2C_Stop(void)
{
   I2C_SDA_OUT();

   I2C_SCL_L;
   I2C_SDA_L;
   I2C_SCL_H;
   delay_nus(6);
   I2C_SDA_H;
   delay_nus(6);
}

//主机产生应答信号ACK
void I2C_Ack(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_L;
   delay_nus(2);
   I2C_SCL_H;
   delay_nus(5);
   I2C_SCL_L;
}

//主机不产生应答信号NACK
void I2C_NAck(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_H;
   delay_nus(2);
   I2C_SCL_H;
   delay_nus(5);
   I2C_SCL_L;
}
//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
u8 I2C_Wait_Ack(void)
{
	u8 tempTime=0;

	I2C_SDA_IN();

	I2C_SDA_H;
	delay_nus(1);
	I2C_SCL_H;
	delay_nus(1);

	while(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			I2C_Stop();
			return 1;
		}	 
	}

	I2C_SCL_L;
	return 0;
}
//I2C 发送一个字节
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;

	I2C_SDA_OUT();
	I2C_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delay_nus(2); //发送数据
		I2C_SCL_L;
		delay_nus(2);
	}
}

//I2C 读取一个字节

u8 I2C_Read_Byte(u8 ack)
{
   u8 i=0,receive=0;

   I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		I2C_SCL_L;
		delay_nus(2);
		I2C_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
		   receive++;
		delay_nus(1);	
   }

   	if(ack==0)
	   	I2C_NAck();
	else
		I2C_Ack();

	return receive;
}

//初始化IIC接口
void AT24CXX_Init(void)
{
	  u8 addrtemp1,addrtemp2;
    I2C_INIT();		 //IIC初始化
    delay_nms(4);
		if(0 == AT24CXX_Check()){
				addrtemp1 = AT24CXX_ReadOneByte(0x00);
			  addrtemp2 = AT24CXX_ReadOneByte(0x01);
			  if((addrtemp1 == addrtemp2)&&(addrtemp1 < 128)){
					slaveaddr = addrtemp1;
					clear_screen(0xFF);
					AdrrOK_Flag = 1;
				}else{
					display_GB2312_string(0,8,"请设置设备地址");
					display_GB2312_string(2,16,"当前地址:0");
					display_GB2312_string(4,8,"该地址设备异常");
					display_GB2312_string(6,16,"1<=地址<=128");
					slaveaddr = 0;
					delay_ms(1500);
					delay_ms(1500);
					
					delay_ms(1500);
				}
		}else{
					display_GB2312_string(0,8,"请设置设备地址");
					display_GB2312_string(2,16,"当前地址:0");
					display_GB2312_string(4,8,"该地址设备异常");
					display_GB2312_string(6,16,"1<=地址<=128");
					slaveaddr = 0;
					delay_ms(1500);
					delay_ms(1500);
					delay_ms(1500);
		}
}

/*******************************************************************************
* 函 数 名         : AT24Cxx_ReadOneByte
* 函数功能		   : 24c02读一个字节地址  数据	   
* 输    入         : addr
* 输    出         : 返回值temp
*******************************************************************************/
u8 AT24CXX_ReadOneByte(u16 addr)
{
	u8 temp=0;

	I2C_Start();
	
	if(EE_TYPE>AT24C16)
	{
		I2C_Send_Byte(0xA0);
		I2C_Wait_Ack();
		I2C_Send_Byte(addr>>8);	//发送数据地址高位
	}
	else
	{
	   I2C_Send_Byte(0xA0+((addr/256)<<1));//器件地址+数据地址
	}

	I2C_Wait_Ack();
	I2C_Send_Byte(addr%256);//双字节是数据地址低位		
							//单字节是数据地址低位
	I2C_Wait_Ack();

	I2C_Start();
	I2C_Send_Byte(0xA1);
	I2C_Wait_Ack();

	temp=I2C_Read_Byte(0); //  0   代表 NACK
	I2C_NAck();
	I2C_Stop();
	
	return temp;	
}



/*******************************************************************************
* 函 数 名         : AT24Cxx_WriteOneByte
* 函数功能		   : 24c02写一个字节地址  数据	   
* 输    入         : addr  dt
* 输    出         : 无
*******************************************************************************/
void AT24CXX_WriteOneByte(u16 addr,u8 dt)
{
	I2C_Start();

	if(EE_TYPE>AT24C16)
	{
		I2C_Send_Byte(0xA0);
		I2C_Wait_Ack();
		I2C_Send_Byte(addr>>8);	//发送数据地址高位
	}
	else
	{
	   I2C_Send_Byte(0xA0+((addr/256)<<1));//器件地址+数据地址
	}

	I2C_Wait_Ack();
	I2C_Send_Byte(addr%256);//双字节是数据地址低位		
							//单字节是数据地址低位
	I2C_Wait_Ack();

	I2C_Send_Byte(dt);
	I2C_Wait_Ack();
	I2C_Stop();

	delay_nms(10);
}

/*******************************************************************************
* 函 数 名         : AT24CXX_WriteLenByte
* 函数功能		   : 24c02根据数据长度写数据	   
* 输    入         : u16 WriteAddr :开始写入的地址,u32 DataToWrite:写入的数据，u8 Len:要写入数据的长度2,4
* 输    出         : 无
*******************************************************************************/
void AT24CXX_WriteLenByte(u16 WriteAddr,u32 DataToWrite,u8 Len)
{  	
	u8 t;
	for(t=0;t<Len;t++)
	{
		AT24CXX_WriteOneByte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

/*******************************************************************************
* 函 数 名         : AT24CXX_ReadLenByte
* 函数功能		   : 在AT24CXX里面的指定地址开始读出长度为Len的数据	   
* 输    入         : u16 ReadAddr :开始读出的地址,u8 Len:要读出数据的长度2,4
* 输    出         : 数据
*******************************************************************************/
u32 AT24CXX_ReadLenByte(u16 ReadAddr,u8 Len)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<Len;t++)
	{
		temp<<=8;
		temp+=AT24CXX_ReadOneByte(ReadAddr+Len-t-1); 	 				   
	}
	return temp;												    
}
//检查AT24CXX是否正常
//这里用了24XX的最后一个地址(255)来存储标志字.
//如果用其他24C系列,这个地址要修改
//返回1:检测失败
//返回0:检测成功
/*******************************************************************************
* 函 数 名         : AT24CXX_Check
* 函数功能		   : 检查AT24CXX是否正常	   
* 输    入         : 无
* 输    出         : 返回1:检测失败,返回0:检测成功
*******************************************************************************/
u8 AT24CXX_Check(void)
{
	u8 temp;
    
	temp=AT24CXX_ReadOneByte(255);//避免每次开机都写AT24CXX			   
	if(temp==0X55){
		return 0;
	}else//排除第一次初始化的情况
	{
		AT24CXX_WriteOneByte(255,0X55);
	  temp=AT24CXX_ReadOneByte(255);	  
		if(temp==0X55)return 0;
	}
	return 1;											  
}


/*******************************************************************************
* 函 数 名         : AT24CXX_Read
* 函数功能		   : 在AT24CXX里面的指定地址开始读出指定个数的数据	   
* 输    入         : u16 ReadAddr :开始读出的地址,u8 *pBuffer:数据数组首地址，u8 NumToRead:要读出数据的个数
* 输    出         : 数据
*******************************************************************************/
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	while(NumToRead)
	{
		*pBuffer++=AT24CXX_ReadOneByte(ReadAddr++);	
		NumToRead--;
	}
}  

/*******************************************************************************
* 函 数 名         : AT24CXX_Write
* 函数功能		   : 在AT24CXX里面的指定地址开始读出长度为Len的数据	   
* 输    入         : u16 WriteAddr :开始写入的地址 对24c02为0~255,u8 *pBuffer:数据数组首地址，u8 NumToWrite:要写入数据的个数
* 输    出         : 数据
*******************************************************************************/
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_WriteOneByte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
