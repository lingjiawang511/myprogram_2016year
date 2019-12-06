#include"HeadType.h"
#include "flash_if.h"

/*串口1管脚重映射*/
#define USART1REMAP 0


Usart_Type Usart1_Control_Data;
Usart_Type Usart2_Control_Data;
Answer_Type      PC_Answer;
char Auto_Frame_Time1;
char Auto_Frame_Time2;
COMM_RecControl_Union_Type   MCU_Slave_RecC;

Belt_Work_Type belt;                            //皮带控制变量

//=============================================================================
//函数名称:Init_USART1
//功能概要:USART1 初始化串口相关参数
//参数说明:无
//函数返回:无
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
//函数名称:USART1_Interrupts_Config
//功能概要:USART1 中断优先级配置
//参数说明:无
//函数返回:无
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
//函数名称:USART2_Interrupts_Config
//功能概要:USART2 中断优先级配置
//参数说明:无
//函数返回:无
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
//函数名称:USART1_Config
//功能概要:USART1 初始化配置,工作模式配置。57600 8-N-1
//参数说明:无
//函数返回:无
//=============================================================================
#if USART1REMAP  //如果USART1使用了映射

void USART1_Config(void )
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;  //定义串口初始化结构体

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);

    /*  USART1_TX -> PB6 */

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;        //选中串口默认输出管脚
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //定义输出最大速率
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//定义管脚9的模式
    GPIO_Init(GPIOB, &GPIO_InitStructure);           //调用函数，把结构体参数输入进行初始化

    /*  USART1_RX ->  PB7*/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = 19200; //波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位
    USART_InitStructure.USART_StopBits = USART_StopBits_1;    //停止位1位
    USART_InitStructure.USART_Parity = USART_Parity_No;       //校验位 无
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无流控制
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;       //使能接收和发送引脚

    USART_Init(USART1, &USART_InitStructure); //将以上赋完值的结构体带入库函数USART_Init进行初始化
    USART_ClearFlag(USART1, USART_FLAG_TC);
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    USART_ITConfig(USART1, USART_IT_TC, ENABLE);
    /* Enable the EXTI Interrupt */
    USART_Cmd(USART1, ENABLE);//开启USART1，注意与上面RCC_APB2PeriphClockCmd()设置的区别
    USART1_Interrupts_Config();
    Init_USART1();
}
#else
void USART1_Config(void)
{
    //gpio，usart初始化结构体定义
    //当gpio复用时（开启外设时），需要初始化同时gpio和ppp外设，并对他们使能和开启时钟
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    //开启gpio和外设时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //使能GPIOA时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //使能USART1时钟
    //串口1对应引脚复用映射
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //GPIOA9复用为USART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //GPIOA10复用为USART1

    //USART1端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9，PA10

    //USART初始化
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
    USART_Cmd(USART1, ENABLE);//开启USART1，注意与上面RCC_APB2PeriphClockCmd()设置的区别

    USART1_Interrupts_Config();
    Init_USART1();
}

#endif
//=============================================================================
//函数名称:USART2_Config
//功能概要:USART2 初始化配置,工作模式配置。57600 8-N-1
//参数说明:无
//函数返回:无
//=============================================================================
void USART2_Config(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    /* Enable the USART2 Pins Software Remapping */
    RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    //串口1对应引脚复用映射
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIOA9复用为USART1
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIOA10复用为USART1

    //USART1端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //GPIOA9与GPIOA10
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;   //速度50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9，PA10

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
//函数名称:fputc
//功能概要:重定向c库函数printf到USART
//参数说明:无
//函数返回:无
//注意   :由printf调用,需要勾选Use Microlib
//=============================================================================

int fputc(int ch, FILE *f)
{
//将Printf内容发往串口
    USART_SendData(USART1, (unsigned char) ch);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    return (ch);
}
//=============================================================================
//函数名称:USART1_Putc
//功能概要:将USART1_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意   :无
//=============================================================================
void USART1_Putc(unsigned char c)
{
    USART_SendData(USART1, c);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET );
}

//=============================================================================
//函数名称:USART1_Putc
//功能概要:将USART1_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART1_Puts(char * str)
{
    while (*str) {
        USART_SendData(USART1, *str++);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
    }
}
//=============================================================================
//函数名称:USART1_Putc
//功能概要:将USART1_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意   :无
//=============================================================================
void USART2_Putc(unsigned char c)
{
    USART_SendData(USART2, c);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET );
}

//=============================================================================
//函数名称:USART1_Putc
//功能概要:将USART1_Putc（）内容打印到串口
//参数说明:无
//函数返回:无
//注意    :无
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
//函数名称:USART1_Do_Tx
//功能概要:将串口一的数据发送出去，通过中断发送
//参数说明:无
//函数返回:无
//注意    :无
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
//函数名称:USART1_Do_Rx
//功能概要:处理串口一接收的数据
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART1_Do_Rx(u8 rxdata)
{
    if (0 == Usart1_Control_Data.rx_aframe) {
        if (0 == Usart1_Control_Data.rx_index) { //接收第一帧的第一个数据开启定时器3做时间自动成帧处理
            Usart1_Control_Data.rx_start = 1;
            Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
        } else {
            if (Auto_Frame_Time1 <= 0) { //时间超时自动成帧
                Usart1_Control_Data.rx_aframe = 1;
                Usart1_Control_Data.rx_start = 0;
                Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index;
                Usart1_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
                return ;   //直接返回不接受数据
            }
        }
        Usart1_Control_Data.rxbuf[Usart1_Control_Data.rx_index] = rxdata;
        Usart1_Control_Data.rx_index++;
        if (Usart1_Control_Data.rx_index > (RxBufMax - 1)) {
            Usart1_Control_Data.rx_index = (RxBufMax - 1);
            Usart1_Control_Data.rx_aframe = 1;  //接收数据长度自动成帧
            Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index + 1;
            Usart1_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
            Usart1_Control_Data.rx_start = 0;
            Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
        }
    } else { //接收到一帧数据后必须处理完才可以继续接受下一帧数据
        Usart1_Control_Data.rx_start = 0;
        Auto_Frame_Time1 = AUTO_FRAME_TIMEOUT1;
        return;
    }
}

//=============================================================================
//函数名称:USART1_Do_Tx
//功能概要:将串口一的数据发送出去，通过中断发送
//参数说明:无
//函数返回:无
//注意    :无
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
//函数名称:USART1_Do_Rx
//功能概要:处理串口一接收的数据
//参数说明:无
//函数返回:无
//注意    :无
//=============================================================================
void USART2_Do_Rx(u8 rxdata)
{
    if (0 == Usart2_Control_Data.rx_aframe) {
        if (0 == Usart2_Control_Data.rx_index) { //接收第一帧的第一个数据开启定时器3做时间自动成帧处理
            Usart2_Control_Data.rx_start = 1;
            Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
        } else {
            if (Auto_Frame_Time2 <= 0) { //时间超时自动成帧
                Usart2_Control_Data.rx_aframe = 1;
                Usart2_Control_Data.rx_start = 0;
                Usart2_Control_Data.rx_count = Usart2_Control_Data.rx_index;
                Usart2_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
                return ;   //直接返回不接受数据
            }
        }
        Usart2_Control_Data.rxbuf[Usart2_Control_Data.rx_index] = rxdata;
        Usart2_Control_Data.rx_index++;
        if (Usart2_Control_Data.rx_index > (RxBufMax - 1)) {
            Usart2_Control_Data.rx_index = (RxBufMax - 1);
            Usart2_Control_Data.rx_aframe = 1;  //接收数据长度自动成帧
            Usart2_Control_Data.rx_count = Usart2_Control_Data.rx_index + 1;
            Usart2_Control_Data.rx_index = 0;   //得到一帧数据后及时把索引清零
            Usart2_Control_Data.rx_start = 0;
            Auto_Frame_Time2 = AUTO_FRAME_TIMEOUT2;
        }
    } else { //接收到一帧数据后必须处理完才可以继续接受下一帧数据
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
    usart->rx_aframe = 0;   //清空和主机的通讯，避免通讯错误
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
    usart->rx_aframe = 0;   //清空和主机的通讯，避免通讯错误
    usart->rx_count = 0;
}
void Host_CTR_Read_CMD(Usart_Type *usart, COMM_RecControl_Union_Type *recdata)
{
    u8 add_checksum;
    static u16 datalenth;
    u8  databuf[20];
    u16 i, j;
    u8 err_code = 0;

    datalenth = 9;  //固定部分
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
    usart->rx_aframe = 0;   //清空和主机的通讯，避免通讯错误
    usart->rx_count = 0;
}
//=============================================================================
//函数名称:Execute_Host_Comm
//功能概要:执行上位机发出的命令
//参数说明:无
//函数返回:无
//注意    :无
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
//函数名称:Respond_Host_Comm
//功能概要:响应上位机的发出的数据命令，数据已经从串口一接收完整
//参数说明:无
//函数返回:无
//注意    :无
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
        }//把数据复制给主机通讯结构体,数据正确，先回应主机
        for (i = 0; i < (usart->rxbuf[2] * 256 + usart->rxbuf[3]) - 8; i++) {
            MCU_Slave_RecC.rectemplate_buf[i + 7] = usart->rxbuf[i + 7];
        }//把数据复制给主机通讯结构体,数据正确，先回应主机
        Execute_Host_Comm(usart, &MCU_Slave_RecC);
//        Usart1_Control_Data.active_send_msg_time = ACTIVE_SEND_MSG_TIME;
    } else { //checksum错误不返回数据
        return ;
    }
}
//=============================================================================
//函数名称:Respond_Host_Comm
//功能概要:响应上位机的发出的数据命令，数据已经从串口一接收完整
//参数说明:无
//函数返回:无
//注意    :无
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



