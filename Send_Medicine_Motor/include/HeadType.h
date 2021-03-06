#ifndef __HEADTYPE_H_
#define __HEADTYPE_H_

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>	
#include "led.h"
#include "delay.h"
#include "send_medicine_control.h"
#include "exti.h"
#include "usart.h"
#include "TIM.h"
#include "belt.h"



/*************Typedef datatype start*******************/
typedef char int8;
typedef volatile char vint8;
typedef unsigned char uint8;
typedef volatile unsigned char vuint8;
typedef int int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef uint8	uchar,u8,BYTE;		/**< 8-bit value */
typedef uint8 	SOCKET;
typedef uint16	ushort,u16,WORD;	/**< 16-bit value */
typedef uint16	uint;		/**< 16-bit value */
typedef uint32	ulong;		/**< 32-bit value */
/*************Typedef datatype end*******************/

/*************define type start*******************/
#define false      (0)
#define true       (!false)

#ifndef NULL
#define NULL  ((void *)(0))
#endif


#define RxBufMax 512
#define TxBufMax 512
//响应超时时间，即上位机确认二维码正确后扫描枪一直扫描直到得到下一次数据的最长时间
#define ANSWER_SCANTIME	 	 4000	  //4000*5ms
//无响应超时时间，即当下位机发送数据给上位机，而上位机没有响应的最长时间
#define NANSWER_TIME	 1000	  //1000*5ms
#define NANSWER_NUMOUT	 	 3	  //1000*5ms

#define SEND_MEDICINE_TIMEOUT		80    //发药过程中检测到没有药，超时200*5MS后停止
#define IRQ_TIMEOUT							3			//中断软件延时时间
#define IRQ_TIMEOUT1						10			//中断软件延时时间
#define	MOTOR_START_DELAYTIME		40		//每个电机启动延时间隔
#define VERSIONS  1    //版本0是不带后检测传感器计数，使用电机来计数
#define SEND_MEDICINE_JAMTIME   300    //电机堵塞时间
#define MOTOR_PULSE_DELAYTIME   40    //电机启动忽略检测电机脉冲时间

/*************define type end*******************/

/*************union type start*******************/
typedef union{
	long l;
	unsigned long ul;
	int  i;
	unsigned int ui;
	short si[2];
	char  c[4];
	unsigned char uc[4];	
}UL;

typedef union{
	short i;
	unsigned short ui;
	char c[2];
	unsigned char uc[2];
}UI;

/*************union type end*******************/

/*************enum type start*******************/
enum
{
	False=0,True
};
enum{
	READLOW,READHIGH
};
typedef enum{
	SLAVE,
	HOST
}MCU_State_Type;

typedef enum{
	RESERVE,
	READY,
	WORKING,
	WORKEND,
	END
}CH_Work_Enum_Type;
/*************enum type end*******************/

/*************struct type start*******************/

typedef struct{
    u16 tx_index;        //发送当前数据的索引
    u16 rx_index;        //接收到当前数据的索引
    u16 tx_count;        //发送数据总数
    u16 rx_count;        //接收数据总数
    u8 rx_start;
    u8 rx_aframe;       //已经接收到一帧数据
    u8 txbuf[RxBufMax]; //发送数据缓存区
    u8 rxbuf[RxBufMax]; //接收数据缓存区
}Usart_Type;
//主机发送数据协议字节
typedef struct{
	u8  frame_soh;
	u8  frame_x;
	u16 datasize;
	u8  ch1_state;
	u8  ch1_num;
	u8  ch2_state;
	u8  ch2_num;
	u8  ch3_state;
	u8  ch3_num;
	u8  ch4_state;
	u8  ch4_num;
	u8  ch5_state;
	u8  ch5_num;
	u16 crc16_ccitt; 
	u8  frame_end1;
	u8  frame_end2;
}Communation_Send_Type;
//主机接收响应协议字节
typedef struct{
	u8  frame_soh;
	u8  frame_x;
	u16 datasize;
	u8  comm_state;
	u8  bear;
	u16 crc16_ccitt; 
	u8  frame_end1;
	u8  frame_end2;
}Communation_Rec_Type;

typedef union{
	Communation_Send_Type control;
	u8	send_buf[18];	
}COMM_Send_Union_Type;

typedef union{
	Communation_Rec_Type control;
	u8	rec_buf[10];	
}COMM_Rec_Union_Type;

typedef struct{
	u8  answer_state;
	u8 	answer_numout;
	u16 answer_timeout;
	u16 Nanswer_timeout;
}Answer_Type;

typedef struct{
	CH_Work_Enum_Type  state;
	u8 	send_num;			//需要发药数，由PC机发送过来
	u8  motor_pulse;	//电机转过的圈数，使用传感器
	u8  send_actual;	//实际发药数，使用传感器计数
	u8  motor_state;	//电机的工作状态，正在工作时不允许执行状态转换
	u8 	timeoutstart; //电机实际发药数超过PC需要发药数时开启超时变量
	u16  timeout;			//电机实际发药数超时时间
	u8  motor_irqstate;//电机中断软件滤波状态
	u8 motor_irqtime;//电机中断软件滤波时间
	u8 send_actual_irqstate;	//实时计数中断软件滤波状态
	u8 send_actual_irqtime;		//实时计数中断软件滤波时间
	u8 motor_start_state;			//电机启动延时状态
	u16 motor_start_time;			//电机延时启动时间
	u8 err_flag;              //通道错误标志
	u16 err_flash_time;      //通道错误闪烁时间
	u16 send_jam_time;       //发药过程中电机堵塞跳过时间
  u16 motor_pusle_delaytime; //电机启动瞬间忽略电机中断检测时间
}CH_Work_Type;

typedef struct{
	CH_Work_Enum_Type  state;
	u8 	 send_time;
	u16  actual_time;
}Belt_Work_Type;
typedef struct{
	CH_Work_Type ch1;
	CH_Work_Type ch2;
	CH_Work_Type ch3;
	CH_Work_Type ch4;
	CH_Work_Type ch5;
}CH_Work;
/*************struct type end*******************/

/*************extern variable start*******************/
extern char Auto_Frame_Time1;

extern  Usart_Type Usart1_Control_Data;

extern  COMM_Send_Union_Type PC_Host_Rec;
extern  COMM_Rec_Union_Type  PC_Hosr_Send;

extern  COMM_Send_Union_Type MCU_Host_Send;
extern  COMM_Rec_Union_Type  MCU_Host_Rec;

extern  MCU_State_Type MCU_State;
extern  Answer_Type 	 PC_Answer;

extern  CH_Work Channel;
extern	Belt_Work_Type belt;
/*************extern variable end*******************/

/*************function start*******************/
u16 CRC_GetModbus16(u8 *pdata, int len);
u16 CRC_GetCCITT(u8 *pdata, int len);




/*************function end*******************/
#endif


