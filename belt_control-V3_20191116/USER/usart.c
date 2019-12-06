#include"HeadType.h"
#include "flash_if.h"

/*����1�ܽ���ӳ��*/
#define USART1REMAP 0


Usart_Type Usart1_Control_Data;
Usart_Type Usart2_Control_Data;
Answer_Type      PC_Answer;
char Auto_Frame_Time1;
char Auto_Frame_Time2;
COMM_RecControl_Union_Type   MCU_Slave_RecC;

Belt_Work_Type belt;                            //Ƥ�����Ʊ���

//=============================================================================
//��������:Init_USART1
//���ܸ�Ҫ:USART1 ��ʼ��������ز���
//����˵��:��
//��������:��
//=============================================================================
static void Init_USART1(void)
{
    Usart1_Control_Data.tx_index = 0;
    Usart1_Control_Data.rx_index = 0;
    Usart1_Control_Data.tx_count = 0;
    Usart1_Control_Data.rx_count = 0;
    Usart1_Control_Data.rx_start = 0;
    Usart1_Control_Data.rx_aframe = 0;
    Usart1_Control_Data.huart = USART1;
}
static void Init_USART2(void)
{
    Usart2_Control_Data.tx_index = 0;
    Usart2_Control_Data.rx_index = 0;
    Usart2_Control_Data.tx_count = 0;
    Usart2_Control_Data.rx_count = 0;
    Usart2_Control_Data.rx_start = 0;
    Usart2_Control_Data.rx_aframe = 0;
    Usart2_Control_Data.huart = USART2;
}
//=============================================================================
//��������:USART1_Interrupts_Config
//���ܸ�Ҫ:USART1 �ж����ȼ�����
//����˵��:��
//��������:��
//=============================================================================
static void USART1_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//��������:USART2_Interrupts_Config
//���ܸ�Ҫ:USART2 �ж����ȼ�����
//����˵��:��
//��������:��
//=============================================================================
static void USART2_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
//=============================================================================
//��������:USART1_Config
//���ܸ�Ҫ:USART1 ��ʼ������,����ģʽ���á�57600 8-N-1
//����˵��:��
//��������:��
//=============================================================================
#if USART1REMAP  //���USART1ʹ����ӳ��

void USART1_Config(void )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;  //���崮�ڳ�ʼ���ṹ��

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    /*  USART1_TX -> PB6 */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;        //ѡ�д���Ĭ������ܽ�
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //��������������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//����ܽ�9��ģʽ
    GPIO_Init(GPIOB, &GPIO_InitStructure);           //���ú������ѽṹ�����������г�ʼ��

    /*  USART1_RX ->  PB7*/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 19200; //������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    //ֹͣλ1λ
    USART_InitStructure.USART_Parity = USART_Parity_No;       //У��λ ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;       //ʹ�ܽ��պͷ�������

    USART_Init(USART1, &USART_InitStructure); //�����ϸ���ֵ�Ľṹ�����⺯��USART_Init���г�ʼ��
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    /* Enable the EXTI Interrupt */
    USART_Cmd(USART1, ENABLE);//����USART1��ע��������RCC_APB2PeriphClockCmd()���õ�����
    USART1_Interrupts_Config();
    Init_USART1();
}
#else
void USART1_Config(void)
{
    //gpio��usart��ʼ���ṹ�嶨��
    //��gpio����ʱ����������ʱ������Ҫ��ʼ��ͬʱgpio��ppp���裬��������ʹ�ܺͿ���ʱ��
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    //����gpio������ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //ʹ��USART1ʱ��
    //����1��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //GPIOA9����ΪUSART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //GPIOA10����ΪUSART1

    //USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9��PA10

    //USART��ʼ��
    USART_InitStructure.USART_BaudRate = 115200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART1, &USART_InitStructure);
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    /* Enable the EXTI Interrupt */
    USART_Cmd(USART1, ENABLE);//����USART1��ע��������RCC_APB2PeriphClockCmd()���õ�����

    USART1_Interrupts_Config();
    Init_USART1();
}

#endif
//=============================================================================
//��������:USART2_Config
//���ܸ�Ҫ:USART2 ��ʼ������,����ģʽ���á�57600 8-N-1
//����˵��:��
//��������:��
//=============================================================================
void USART2_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* Enable the USART2 Pins Software Remapping */
    RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    //����1��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIOA9����ΪUSART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIOA10����ΪUSART1

    //USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9��GPIOA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9��PA10

    USART_InitStructure.USART_BaudRate = 19200;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    USART_Init(USART2, &USART_InitStructure);
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART2, USART_IT_TC, ENABLE);
    USART_ClearFlag(USART2, USART_FLAG_TC);
    /* Enable USART2 */
    USART_Cmd(USART2, ENABLE);
    USART2_Interrupts_Config();
    Init_USART2();

}

//=============================================================================
//��������:fputc
//���ܸ�Ҫ:�ض���c�⺯��printf��USART
//����˵��:��
//��������:��
//ע��   :��printf����,��Ҫ��ѡUse Microlib
//=============================================================================

int fputc(int ch, FILE *f)
{
//��Printf���ݷ�������
    USART_SendData(USART1, (unsigned char) ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return (ch);
}
//=============================================================================
//��������:USART1_Putc
//���ܸ�Ҫ:��USART1_Putc�������ݴ�ӡ������
//����˵��:��
//��������:��
//ע��   :��
//=============================================================================
void USART1_Putc(unsigned char c)
{
    USART_SendData(USART1, c);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}

//=============================================================================
//��������:USART1_Putc
//���ܸ�Ҫ:��USART1_Putc�������ݴ�ӡ������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
void USART1_Puts(char * str)
{
    while (*str) {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}
//=============================================================================
//��������:USART1_Putc
//���ܸ�Ҫ:��USART1_Putc�������ݴ�ӡ������
//����˵��:��
//��������:��
//ע��   :��
//=============================================================================
void USART2_Putc(unsigned char c)
{
    USART_SendData(USART2, c);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );
}

//=============================================================================
//��������:USART1_Putc
//���ܸ�Ҫ:��USART1_Putc�������ݴ�ӡ������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
void USART2_Puts(char * str)
{
    while (*str) {
        USART_SendData(USART2, *str++);
        while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
    }
}
u8 Get_Add_Check(u8* databuf, u16 datalenth)
{
    u16 i;
    u16 add_checksum = 0;

    for (i = 0; i < datalenth; i++) {
        add_checksum += databuf[i];
    }

    return (u8)add_checksum;
}
//=============================================================================
//��������:USART1_Do_Tx
//���ܸ�Ҫ:������һ�����ݷ��ͳ�ȥ��ͨ���жϷ���
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
void USART1_Do_Tx(void )
{
    if (Usart1_Control_Data.tx_index < Usart1_Control_Data.tx_count) {
        USART_SendData(USART1, Usart1_Control_Data.txbuf[Usart1_Control_Data.tx_index]);
        Usart1_Control_Data.tx_index++;
    } else {
        Usart1_Control_Data.tx_count = 0;
        Usart1_Control_Data.tx_index = 0;
    }
}

//=============================================================================
//��������:USART1_Do_Rx
//���ܸ�Ҫ:������һ���յ�����
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
void USART1_Do_Rx(u8 rxdata)
{
    if (0 == Usart1_Control_Data.rx_aframe) {
        if (0 == Usart1_Control_Data.rx_index) { //���յ�һ֡�ĵ�һ�����ݿ�����ʱ��3��ʱ���Զ���֡����
            Usart1_Control_Data.rx_start = 1;
            Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
        } else {
            if (Auto_Frame_Time1 <= 0) { //ʱ�䳬ʱ�Զ���֡
                Usart1_Control_Data.rx_aframe = 1;
                Usart1_Control_Data.rx_start = 0;
                Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index;
                Usart1_Control_Data.rx_index = 0;   //�õ�һ֡���ݺ�ʱ����������
                return ;   //ֱ�ӷ��ز���������
            }
        }
        Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_index] = rxdata;
        Usart1_Control_Data.rx_index++;
        if (Usart1_Control_Data.rx_index > (RxBufMax - 1)) {
            Usart1_Control_Data.rx_index = (RxBufMax - 1);
            Usart1_Control_Data.rx_aframe = 1;  //�������ݳ����Զ���֡
            Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index + 1;
            Usart1_Control_Data.rx_index = 0;   //�õ�һ֡���ݺ�ʱ����������
            Usart1_Control_Data.rx_start = 0;
            Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
        }
    } else { //���յ�һ֡���ݺ���봦����ſ��Լ���������һ֡����
        Usart1_Control_Data.rx_start = 0;
        Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
        return;
    }
}

//=============================================================================
//��������:USART1_Do_Tx
//���ܸ�Ҫ:������һ�����ݷ��ͳ�ȥ��ͨ���жϷ���
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
void USART2_Do_Tx(void )
{
    if (Usart2_Control_Data.tx_index < Usart2_Control_Data.tx_count) {
        USART_SendData(USART2, Usart2_Control_Data.txbuf[Usart2_Control_Data.tx_index]);
        Usart2_Control_Data.tx_index++;
    } else {
        Usart2_Control_Data.tx_count = 0;
        Usart2_Control_Data.tx_index = 0;
    }
}

//=============================================================================
//��������:USART1_Do_Rx
//���ܸ�Ҫ:������һ���յ�����
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
void USART2_Do_Rx(u8 rxdata)
{
    if (0 == Usart2_Control_Data.rx_aframe) {
        if (0 == Usart2_Control_Data.rx_index) { //���յ�һ֡�ĵ�һ�����ݿ�����ʱ��3��ʱ���Զ���֡����
            Usart2_Control_Data.rx_start = 1;
            Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
        } else {
            if (Auto_Frame_Time2 <= 0) { //ʱ�䳬ʱ�Զ���֡
                Usart2_Control_Data.rx_aframe = 1;
                Usart2_Control_Data.rx_start = 0;
                Usart2_Control_Data.rx_count = Usart2_Control_Data.rx_index;
                Usart2_Control_Data.rx_index = 0;   //�õ�һ֡���ݺ�ʱ����������
                return ;   //ֱ�ӷ��ز���������
            }
        }
        Usart2_Control_Data.rxbuf[Usart2_Control_Data.rx_index] = rxdata;
        Usart2_Control_Data.rx_index++;
        if (Usart2_Control_Data.rx_index > (RxBufMax - 1)) {
            Usart2_Control_Data.rx_index = (RxBufMax - 1);
            Usart2_Control_Data.rx_aframe = 1;  //�������ݳ����Զ���֡
            Usart2_Control_Data.rx_count = Usart2_Control_Data.rx_index + 1;
            Usart2_Control_Data.rx_index = 0;   //�õ�һ֡���ݺ�ʱ����������
            Usart2_Control_Data.rx_start = 0;
            Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
        }
    } else { //���յ�һ֡���ݺ���봦����ſ��Լ���������һ֡����
        Usart2_Control_Data.rx_start = 0;
        Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
        return;
    }
}
void wait_tx_count_reset(unsigned short tx_count)
{
    u16 timeout_count;
    timeout_count = 1000;
    do {
        delay_us(5);
        timeout_count--;
    } while ((tx_count != 0) && (timeout_count != 0));
}
void Host_CTR_Special_CMD(Usart_Type *usart, COMM_RecControl_Union_Type *recdata)
{
	  u8 add_checksum;
    u8 err_code = 0;
    u8 not_ctr_servo_flag = 0;
    u16 datalenth = 0;
    UL save_cmd_to_flash;
	  u8 reset_mcu_flag;
	
    datalenth = 9;
		reset_mcu_flag = 0;
        switch (recdata->control.funcodeL) {
            case 0xFF:
                not_ctr_servo_flag = 1;
						    if((recdata->control.recbuf[1] == 'D')&&(recdata->control.recbuf[2] == 'L')){
									save_cmd_to_flash.c[3] = 'D';
									save_cmd_to_flash.c[2] = 'L';
									save_cmd_to_flash.c[1] = 'D';
									save_cmd_to_flash.c[0] = 'L';
									if(0 == STMFLASH_Write(FLASH_START_ADDR, FLASH_SAVE_SIZE, sizeof(long), (uint8_t *)&save_cmd_to_flash)){
										reset_mcu_flag = 1;
									}else{
										if(0 == STMFLASH_Write(FLASH_START_ADDR, FLASH_SAVE_SIZE, sizeof(long), (uint8_t *)&save_cmd_to_flash)){
											reset_mcu_flag = 1;
										}
									}
								}
                break;
            default:
                not_ctr_servo_flag = 1;
                err_code = 0x01;
                break;
        }
    if (err_code == 0) {
            not_ctr_servo_flag = not_ctr_servo_flag;
    } else {
        recdata->control.funcodeH = 0x80 | recdata->control.funcodeH;
        datalenth++;
    }
    wait_tx_count_reset(usart->tx_count);
    usart->tx_count = 0;
    usart->txbuf[usart->tx_count++] = 0xAA;
    usart->txbuf[usart->tx_count++] = 0xCC;
    usart->txbuf[usart->tx_count++] = (datalenth >> 8) & 0xFF;
    usart->txbuf[usart->tx_count++] = datalenth & 0XFF;
    usart->txbuf[usart->tx_count++] = recdata->control.funcodeH;
    usart->txbuf[usart->tx_count++] = recdata->control.funcodeL;
    usart->txbuf[usart->tx_count++] = recdata->control.comm_num;
    usart->txbuf[usart->tx_count++] = recdata->control.recbuf[0];
    if (err_code != 0) {
        usart->txbuf[usart->tx_count++] = err_code;
    }
    add_checksum = Get_Add_Check(&usart->txbuf[2], usart->tx_count - 2);
    usart->txbuf[usart->tx_count++] = add_checksum;
    usart->txbuf[usart->tx_count++] = 0XDD;
    usart->txbuf[usart->tx_count++] = 0XEE;
    usart->tx_index = 0;
		USART_SendData(usart->huart, usart->txbuf[usart->tx_index++]);
    usart->rx_aframe = 0;   //��պ�������ͨѶ������ͨѶ����
    usart->rx_count = 0;
		if(reset_mcu_flag == 1){
			reset_mcu_flag = 0;
			delay_ms(100);
			NVIC_SystemReset();
		}
}
void Host_CTR_Write_CMD(Usart_Type *usart, COMM_RecControl_Union_Type *recdata)
{
    u8 add_checksum;
    u8 err_code = 0;
    u16 datalenth = 0;

    datalenth = 9;
    switch (recdata->control.funcodeL) {
        case 0x91:
            if (recdata->control.recbuf[0] == 0x13) {
                belt11.comm_ctr_start = 1;
                belt11.comm_ctr_run_speed = recdata->control.recbuf[2] * 10;
                belt11.comm_ctr_run_time = recdata->control.recbuf[3] * 200;
                if (belt11.comm_ctr_run_time == 0) {
                    belt11.comm_ctr_run_time = belt11.actual_time;
										belt11.comm_run_always_flag = 1;
                }
                if (belt11.comm_ctr_run_dir != recdata->control.recbuf[1]) {
                    if (belt11.belt_actual_state == 1) {
                        Belt11_Speed(0, 0, 0); //
                        delay_ms(500);
                        belt11.belt_actual_state = 0;
                        belt11.start_signal = 0;
                        belt11.start_ok = 0;
                        belt11.stop_ok = 0;
                    }
                }
                belt11.comm_ctr_run_dir = recdata->control.recbuf[1];
                if (belt11.comm_ctr_run_dir == 0x01) {
                    Belt11_SetDir(BELT_LEFT);
                } else if (belt11.comm_ctr_run_dir == 0x02) {
                    Belt11_SetDir(BELT_FIGRT);
                }

            } else if (recdata->control.recbuf[0] == 0x14) {
                belt12.comm_ctr_start = 1;
                belt12.comm_ctr_run_speed = recdata->control.recbuf[2] * 10;
                belt12.comm_ctr_run_time = recdata->control.recbuf[3] * 200;
                if (belt12.comm_ctr_run_time == 0) {
                    belt12.comm_ctr_run_time = belt12.actual_time;
										belt12.comm_run_always_flag = 1;
                }
                if (belt12.comm_ctr_run_dir != recdata->control.recbuf[1]) {
                    if (belt12.belt_actual_state == 1) {
                        Belt12_Speed(0, 0, 0); //
                        delay_ms(500);
                        belt12.belt_actual_state = 0;
                        belt12.start_signal = 0;
                        belt12.start_ok = 0;
                        belt12.stop_ok = 0;
                    }
                }
                belt12.comm_ctr_run_dir = recdata->control.recbuf[1];
                if (belt12.comm_ctr_run_dir == 0x01) {
                    Belt12_SetDir(BELT_LEFT);
                } else if (belt12.comm_ctr_run_dir == 0x02) {
                   Belt12_SetDir(BELT_FIGRT);
                }
            }
            break;
        case 0x92:
            if (recdata->control.recbuf[0] == 0x13) {
                belt11.stop_signal = 1;
                belt11.start_signal = 0;
                belt11.start_ok = 0;
                belt11.comm_ctr_start = 0;
								belt11.comm_run_always_flag = 0;
            } else if (recdata->control.recbuf[0] == 0x14) {
                belt12.stop_signal = 1;
                belt12.start_signal = 0;
                belt12.start_ok = 0;
                belt12.comm_ctr_start = 0;
								belt12.comm_run_always_flag = 0;
            }
            break;
        default:
            err_code = 0x01;
            break;
    }
    if (err_code == 0) {

    } else {
        recdata->control.funcodeH = 0x80 | recdata->control.funcodeH;
        datalenth++;
    }
    wait_tx_count_reset (usart->tx_count);
    usart->tx_count = 0;
    usart->txbuf[usart->tx_count++] = 0xAA;
    usart->txbuf[usart->tx_count++] = 0xCC;
    usart->txbuf[usart->tx_count++] = (datalenth >> 8) & 0xFF;
    usart->txbuf[usart->tx_count++] = datalenth & 0XFF;
    usart->txbuf[usart->tx_count++] = recdata->control.funcodeH;
    usart->txbuf[usart->tx_count++] = recdata->control.funcodeL;
    usart->txbuf[usart->tx_count++] = recdata->control.comm_num;
    usart->txbuf[usart->tx_count++] = recdata->control.recbuf[0];
    if (err_code != 0) {
        usart->txbuf[usart->tx_count++] = err_code;
    }
    add_checksum = Get_Add_Check(&usart->txbuf[2], usart->tx_count - 2);
    usart->txbuf[usart->tx_count++] = add_checksum;
    usart->txbuf[usart->tx_count++] = 0XDD;
    usart->txbuf[usart->tx_count++] = 0XEE;
    usart->tx_index = 0;
    USART_SendData(usart->huart, usart->txbuf[usart->tx_index++]);
    usart->rx_aframe = 0;   //��պ�������ͨѶ������ͨѶ����
    usart->rx_count = 0;
}
void Host_CTR_Read_CMD(Usart_Type *usart, COMM_RecControl_Union_Type *recdata)
{
    u8 add_checksum;
    static u16 datalenth;
    u8  databuf[20];
    u16 i, j;
    u8 err_code = 0;

    datalenth = 9;  //�̶�����
    i = 0;
    switch (recdata->control.funcodeL) {
        case 0x91:
            if (recdata->control.recbuf[0] == 0x13) {
                databuf[i++] = belt11.comm_actual_state;
            } else if (recdata->control.recbuf[0] == 0x14) {
                databuf[i++] = belt12.comm_actual_state;
            }
            break;
//          case 0x92:
//              break;
        case 0xA4:
//              databuf[i++] = recdata->control.recbuf[0];
            databuf[i++] = (SOFTWARE_VERSIONS_H >> 8) & 0XFF;
            databuf[i++] = SOFTWARE_VERSIONS_H & 0xFF;
            databuf[i++] = (SOFTWARE_VERSIONS_M >> 8) & 0XFF;
            databuf[i++] = SOFTWARE_VERSIONS_M & 0xFF;;
            databuf[i++] = (SOFTWARE_VERSIONS_L >> 8) & 0XFF;
            databuf[i++] = SOFTWARE_VERSIONS_L & 0xFF;;
            break;
        case 0xA5:
//              databuf[i++] = recdata->control.recbuf[0];
            databuf[i++] = (HARDWARE_VERSIONS_H >> 8) & 0XFF;
            databuf[i++] = HARDWARE_VERSIONS_H & 0xFF;;
            databuf[i++] = (HARDWARE_VERSIONS_M >> 8) & 0XFF;
            databuf[i++] = HARDWARE_VERSIONS_M & 0xFF;;
            databuf[i++] = (HARDWARE_VERSIONS_L >> 8) & 0XFF;
            databuf[i++] = HARDWARE_VERSIONS_L & 0xFF;;
            break;
        default:
            err_code = 0x01;
//              databuf[i++] = recdata->control.recbuf[0];
//            recdata->control.funcodeH = recdata->control.funcodeH|0X80;
            break;
    }

    if (err_code != 0) {
        recdata->control.funcodeH = recdata->control.funcodeH | 0X80;
        databuf[i++] = err_code;
    }

    datalenth = datalenth + i;
    wait_tx_count_reset (usart->tx_count);
    usart->tx_count = 0;
    usart->txbuf[usart->tx_count++] = 0xAA;
    usart->txbuf[usart->tx_count++] = 0xCC;
    usart->txbuf[usart->tx_count++] = (datalenth >> 8) & 0xFF;
    usart->txbuf[usart->tx_count++] = datalenth & 0xFF;;
    usart->txbuf[usart->tx_count++] = recdata->control.funcodeH;
    usart->txbuf[usart->tx_count++] = recdata->control.funcodeL;
    usart->txbuf[usart->tx_count++] = recdata->control.comm_num;
    usart->txbuf[usart->tx_count++] = recdata->control.recbuf[0];
    for (j = 0; j < i; j++) {
        usart->txbuf[usart->tx_count++] = databuf[j];
    }
    add_checksum = Get_Add_Check(&usart->txbuf[2], usart->tx_count - 2);
    usart->txbuf[usart->tx_count++] = add_checksum;
    usart->txbuf[usart->tx_count++] = 0XDD;
    usart->txbuf[usart->tx_count++] = 0XEE;
    usart->tx_index = 0;
    USART_SendData(usart->huart, usart->txbuf[usart->tx_index++]);
    usart->rx_aframe = 0;   //��պ�������ͨѶ������ͨѶ����
    usart->rx_count = 0;
}
//=============================================================================
//��������:Execute_Host_Comm
//���ܸ�Ҫ:ִ����λ������������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
u8  Execute_Host_Comm(Usart_Type *usart, COMM_RecControl_Union_Type *recdata)
{
    u8 res;
    switch (recdata->control.funcodeH) {
        case 0x01:
            Host_CTR_Write_CMD(usart, recdata);
            break;
        case 0x03:
            Host_CTR_Read_CMD(usart, recdata);
            break;
				 case 0x10:
					  Host_CTR_Special_CMD(usart, recdata);
            break;	
        default:
            break;
    }
    return res;
}

//=============================================================================
//��������:Respond_Host_Comm
//���ܸ�Ҫ:��Ӧ��λ���ķ�����������������Ѿ��Ӵ���һ��������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
static void Respond_Host_Comm(Usart_Type *usart)
{
    u16 i;
    u16 add_checksum;
    if (usart->rx_count < 8) {
        return;
    }
    /****/
    if (((usart->rxbuf[0] != 0XAA) || (usart->rxbuf[1] != 0XBB)) || \
        ((usart->rxbuf[2] * 256 + usart->rxbuf[3]) != usart->rx_count - 2)) {
        return ;
    }
    if ((usart->rxbuf[usart->rx_count - 2] != 0XDD) || (usart->rxbuf[usart->rx_count - 1] != 0XEE)) {
        return ;
    }
    add_checksum = Get_Add_Check(&usart->rxbuf[2], usart->rx_count - 5);
    if (usart->rxbuf[usart->rx_count - 3] == add_checksum) {
        for (i = 0; i < 7; i++) {
            MCU_Slave_RecC.rectemplate_buf[i] = usart->rxbuf[i];
        }//�����ݸ��Ƹ�����ͨѶ�ṹ��,������ȷ���Ȼ�Ӧ����
        for (i = 0; i < (usart->rxbuf[2] * 256 + usart->rxbuf[3]) - 8; i++) {
            MCU_Slave_RecC.rectemplate_buf[i + 7] = usart->rxbuf[i + 7];
        }//�����ݸ��Ƹ�����ͨѶ�ṹ��,������ȷ���Ȼ�Ӧ����
        Execute_Host_Comm(usart, &MCU_Slave_RecC);
//        Usart1_Control_Data.active_send_msg_time = ACTIVE_SEND_MSG_TIME;
    } else { //checksum���󲻷�������
        return ;
    }
}
//=============================================================================
//��������:Respond_Host_Comm
//���ܸ�Ҫ:��Ӧ��λ���ķ�����������������Ѿ��Ӵ���һ��������
//����˵��:��
//��������:��
//ע��    :��
//=============================================================================
void Communication_Process(void)
{
    if (1 == Usart1_Control_Data.rx_aframe) {
        Respond_Host_Comm(&Usart1_Control_Data);
        Usart1_Control_Data.rx_count = 0;
        Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
        Usart1_Control_Data.rx_aframe = 0;
    }
    if (1 == Usart2_Control_Data.rx_aframe) {
        Respond_Host_Comm(&Usart2_Control_Data);
        Usart2_Control_Data.rx_count = 0;
        Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
        Usart2_Control_Data.rx_aframe = 0;
    }
}



