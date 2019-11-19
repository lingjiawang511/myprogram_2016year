#include"HeadType.h"

#define DEVICE1_KEY_IO                  GPIO_Pin_15
#define DEVICE1_KEY_PORT                GPIOE

#define SWITCH1_IO                          GPIO_Pin_12
#define SWITCH1_PORT                        GPIOD
#define SWITCH2_IO                          GPIO_Pin_13
#define SWITCH2_PORT                        GPIOD
#define SWITCH3_IO                          GPIO_Pin_14
#define SWITCH3_PORT                        GPIOD
#define SWITCH4_IO                          GPIO_Pin_15
#define SWITCH4_PORT                        GPIOD

#define READ_DEVICE1_KEY                GPIO_ReadInputDataBit(DEVICE1_KEY_PORT,DEVICE1_KEY_IO) //���ص���һ���ֽڣ�������һ��λ
#define READ_SWITCH1                    GPIO_ReadInputDataBit(SWITCH1_PORT,SWITCH1_IO) //���ص���һ���ֽڣ�������һ��λ
#define READ_SWITCH2                    GPIO_ReadInputDataBit(SWITCH2_PORT,SWITCH2_IO) //���ص���һ���ֽڣ�������һ��λ
#define READ_SWITCH3                    GPIO_ReadInputDataBit(SWITCH3_PORT,SWITCH3_IO) //���ص���һ���ֽڣ�������һ��λ
#define READ_SWITCH4                    GPIO_ReadInputDataBit(SWITCH4_PORT,SWITCH4_IO) //���ص���һ���ֽڣ�������һ��λ


#define KEY_SHORT_TIME          10
#define KEY_LONG_TIME           300
u8 Key_ScanNum;

//=============================================================================
//��������: KEY_GPIO_Config
//���ܸ�Ҫ:LED����������
//��������:��
//��������:��
//ע��    :��
//=============================================================================
void KEY_GPIO_Config(void)
{
    //����һ��GPIO_InitTypeDef ���͵Ľṹ�壬���ֽ�GPIO_InitStructure
    GPIO_InitTypeDef  GPIO_InitStructure;
    //ʹ��GPIOC������ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    //ѡ��Ҫ�õ�GPIO����
    GPIO_InitStructure.GPIO_Pin = SWITCH1_IO | SWITCH2_IO | SWITCH3_IO | SWITCH4_IO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100M
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(GPIOD, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

    GPIO_InitStructure.GPIO_Pin = DEVICE1_KEY_IO;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100M
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
    GPIO_Init(DEVICE1_KEY_PORT, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4

}

u8 Key_Scan(void)
{
    u8 key_num;
    static u8 key1_triggerstate;
    static u16 key1_timercount;
    static u8 longlongkey_flag = 0;
    key_num = 0;
    //key1
    if (READ_DEVICE1_KEY == READLOW) {
        if (longlongkey_flag == 0) {
            if (key1_triggerstate == 0) {
                key1_triggerstate = 1;
            } else {
                key1_timercount++;
                if (key1_timercount >= KEY_LONG_TIME) {
                    key_num |= 0x11;
                    longlongkey_flag = 1;
                }
            }
        }
    } else {
        if (longlongkey_flag == 1) {
            longlongkey_flag = 0;
            key1_timercount = 0;
            key1_triggerstate = 0;
        } else {
            if (key1_triggerstate == 1) {
                if (key1_timercount < KEY_SHORT_TIME) {
                    key_num &= 0xfe;
                } else if ((key1_timercount >= KEY_SHORT_TIME) && (key1_timercount < KEY_LONG_TIME)) {
                    key_num |= 0x01;
                } else {
                    key_num = 0;
                }
                key1_triggerstate = 0;
            }
            key1_timercount = 0;
        }
    }

    return key_num;
}
u16 switch_init_time(void)
{
    u16 belt_delay_time = 0;
    if (READ_SWITCH1 == 0) {
        delay_ms(10);
        if (READ_SWITCH1 == 0) {
            belt_delay_time += BELT_STOP_DELAY;
        }
    }
    if (READ_SWITCH2 == 0) {
        delay_ms(10);
        if (READ_SWITCH2 == 0) {
            belt_delay_time += BELT_STOP_DELAY * 2;
        }
    }
    if (READ_SWITCH3 == 0) {
        delay_ms(10);
        if (READ_SWITCH3 == 0) {
            belt_delay_time += BELT_STOP_DELAY * 4;
        }
    }
    if (READ_SWITCH4 == 0) {
        delay_ms(10);
        if (READ_SWITCH4 == 0) {
            belt_delay_time += BELT_STOP_DELAY * 8;
        }
    }
    return belt_delay_time;
}


