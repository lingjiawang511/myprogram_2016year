#ifndef __HEADTYPE_H_
#define __HEADTYPE_H_

#include "stm32f4xx.h" 
#include <stdio.h>
#include <string.h>	
#include "led.h"
#include "delay.h"
//#include "roll_pater_control.h"
//#include "exti.h"
//#include "usart.h"
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
/*�Զ���֡��ʱ��ʱʱ��*/
#define AUTO_FRAME_TIMEOUT1  30  //10*2ms
#define AUTO_FRAME_TIMEOUT2  30  //10*2ms
/*�Զ���֡��ʱ��ʱʱ��*/
//��Ӧ��ʱʱ�䣬����λ��ȷ�϶�ά����ȷ��ɨ��ǹһֱɨ��ֱ���õ���һ�����ݵ��ʱ��
#define ANSWER_SCANTIME	 	 4000	  //4000*5ms
//����Ӧ��ʱʱ�䣬������λ���������ݸ���λ��������λ��û����Ӧ���ʱ��
#define NANSWER_TIME	 1000	  //1000*5ms
#define NANSWER_NUMOUT	 	 3	  //1000*5ms

#define SEND_MEDICINE_TIMEOUT		200    //��ҩ�����м�⵽û��ҩ����ʱ200*5MS��ֹͣ
#define IRQ_TIMEOUT							4			//�ж������ʱʱ��
#define	MOTOR_START_DELAYTIME		40		//ÿ�����������ʱ���

#define   SOFTWARE_VERSIONS_H     0X0001
#define   SOFTWARE_VERSIONS_M     0X0000
#define   SOFTWARE_VERSIONS_L     0X0000
#define   HARDWARE_VERSIONS_H     0X0001
#define   HARDWARE_VERSIONS_M     0X0000
#define   HARDWARE_VERSIONS_L     0X0000

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
	READLOW = 0,READHIGH
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
	  USART_TypeDef* huart;
    u16 tx_index;        //���͵�ǰ���ݵ�����
    u16 rx_index;        //���յ���ǰ���ݵ�����
    u16 tx_count;        //������������
    u16 rx_count;        //������������
    u8 rx_start;
    u8 rx_aframe;       //�Ѿ����յ�һ֡����
    u8 txbuf[RxBufMax]; //�������ݻ�����
    u8 rxbuf[RxBufMax]; //�������ݻ�����
}Usart_Type;
//������������Э���ֽ�
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
	u8  belt_state;
	u8  belt_time;
	u16 crc16_ccitt; 
	u8  frame_end1;
	u8  frame_end2;
}Communation_Send_Type;


typedef union{
	Communation_Send_Type control;
	u8	send_buf[18];	
}COMM_Send_Union_Type;


typedef struct{
	u8  answer_state;
	u8 	answer_numout;
	u16 answer_timeout;
	u16 Nanswer_timeout;
}Answer_Type;

typedef struct{
	CH_Work_Enum_Type  state;
	u8 	send_num;			//��Ҫ��ҩ������PC�����͹���
	u8  motor_pulse;	//���ת����Ȧ����ʹ�ô�����
	u8  send_actual;	//ʵ�ʷ�ҩ����ʹ�ô���������
	u8  motor_state;	//����Ĺ���״̬�����ڹ���ʱ������ִ��״̬ת��
	u8 	timeoutstart; //���ʵ�ʷ�ҩ������PC��Ҫ��ҩ��ʱ������ʱ����
	u16  timeout;			//���ʵ�ʷ�ҩ����ʱʱ��
	u8  motor_irqstate;//����ж�����˲�״̬
	u8 motor_irqtime;//����ж�����˲�ʱ��
	u8 send_actual_irqstate;	//ʵʱ�����ж�����˲�״̬
	u8 send_actual_irqtime;		//ʵʱ�����ж�����˲�ʱ��
	u8 motor_start_state;			//���������ʱ״̬
	u16 motor_start_time;			//�����ʱ����ʱ��
}CH_Work_Type;

typedef struct{
	CH_Work_Enum_Type  state;
	u8 	 send_time;
	u16  actual_time;
	u8	 speed_step;
	u8   start_signal;
	u8   stop_signal;
	u8   start_ok;
	u8   stop_ok;
	u8   stop_delay_state;
	u8   belt_actual_state;
  u8   comm_ctr_start;
	u8   comm_ctr_stop;
	u8 	 comm_ctr_run_dir;
	u16  comm_ctr_run_speed;
	u16  comm_ctr_run_time;
}Belt_Work_Type;
typedef struct{
	CH_Work_Type ch1;
	CH_Work_Type ch2;
	CH_Work_Type ch3;
	CH_Work_Type ch4;
}CH_Work;
typedef struct {
    u8  frame_start1;
    u8  frame_start2;
    u8  datasizeH;
    u8  datasizeL;
    u8  funcodeH;
    u8  funcodeL;
    u8  comm_num;
    u8  recbuf[240];
    u8  checksum;
    u8  frame_end1;
    u8  frame_end2;
} Communation_Rec_Type;
typedef struct {
    u8  addr;
    u8  command;
    u8  ID_H;
    u8  ID_L;
    u8  function_H;
    u8  function_L;
    u16 crc16_mb;
    u8  recbuf[242];
} Modbus_COMM_Rec_Type;
typedef union {
    Communation_Rec_Type control;
    Modbus_COMM_Rec_Type mb_ctr;
    u8  rectemplate_buf[250];
} COMM_RecControl_Union_Type;
/*************struct type end*******************/

/*************extern variable start*******************/
extern char Auto_Frame_Time1;
extern char Auto_Frame_Time2;
extern  Usart_Type Usart1_Control_Data;
extern  Usart_Type Usart2_Control_Data;
extern  COMM_Send_Union_Type PC_Host_Rec;
extern  COMM_Send_Union_Type MCU_Host_Send;
extern  COMM_RecControl_Union_Type   MCU_Slave_RecC;

extern  MCU_State_Type MCU_State;
extern  Answer_Type 	 PC_Answer;

extern  CH_Work Channel;
extern	Belt_Work_Type belt11;
extern	Belt_Work_Type belt12;
extern  u8 Key_ScanNum;
/*************extern variable end*******************/

/*************function start*******************/
u16 CRC_GetModbus16(u8 *pdata, int len);
u16 CRC_GetCCITT(u8 *pdata, int len);
u8 Key_Scan(void);
void KEY_GPIO_Config(void);
u16 switch_init_time(void);


/*************function end*******************/
#endif


