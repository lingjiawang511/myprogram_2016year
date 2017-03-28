#ifndef __HT1621B_H_
#define __HT1621B_H_


#include"delay.h"

//这里是符号对应的显示顺序，也就对应了在HT1621B数据寄存器内的位置
//#define    _lcd_BUSY     0       
//#define    _lcd_AC      1       
//#define    _lcd_PLUS     2       
//#define    _lcd_F1      3
//#define    _lcd_ERROR    4
//#define    _lcd_DC      5
//#define    _lcd_MINUS     6
//#define    _lcd_F2      7
#define    _lcd_DP1     4        
#define    _lcd_DP2     12 
#define    _lcd_DP3     16+4 
#define    _lcd_COL1     16+12    
#define    _lcd_COL2     32+0
#define    _lcd_COL3     32+1
#define    _lcd_W1       32+3
#define    _lcd_W5       32+4
#define    _lcd_W4       32+5
#define    _lcd_W3       32+6
#define    _lcd_W2       32+7
#define    _lcd_L1       32+8
#define    _lcd_L2       32+9
#define    _lcd_L3       32+10
#define    _lcd_L4       32+11
#define    _lcd_DP5      48+3
#define    _lcd_DP6      48+11
#define    _lcd_DP7      64+3
#define    _lcd_g        64+4
#define    _lcd_kg       64+5
#define    _lcd_Nm       64+6
#define    _lcd_mV       64+7
#define    _lcd_mm       64+8
#define    _lcd_ue       64+9
#define    _lcd_kpa      64+10
#define    _lcd_Mpa      64+11
#define    _lcd_DP8      80+3
#define    _lcd_DP9      80+11
#define    _lcd_0C       96+3
/*
#define    _lcd_MHZ      74
#define    _lcd_KW    75
#define    _lcd_MA    76
#define    _lcd_MV    77
#define    _lcd_KHZ    78
#define    _lcd_W     79
#define    _lcd_NG    80
#define    _lcd_OK    81
#define    _lcd_RX    82
#define    _lcd_TX    83
#define    _lcd_FM    84
#define    _lcd_PM    85
#define    _lcd_AM    86
#define    _lcd_CARD   87
#define    _lcd_AT3    88
#define    _lcd_AT2    89
#define    _lcd_AT1    90
#define    _lcd_AT0    91
#define    _lcd_LOCK   95
#define    _lcd_BELL   103
#define    _lcd_COLON2   111
#define    _lcd_BAT    119
#define    _lcd_MAX    124
#define    _lcd_MIN    125
#define    _lcd_CH    126
#define    _lcd_FAULT   127
*/
/*这里是IO口定义，可以根据需要修改
p0.3 = data;
p0.0 = cs;
p0.1 = rd
p0.2 = wr
*/

//下面是根据我的测试板情况定义的，用户可以需要修改
#define CS_LOW    P0 &= 0xFE
#define CS_HIGH   P0 |= 0x01
#define RD_LOW    P0 &= 0xFD
#define RD_HIGH   P0 |= 0x02
#define WR_LOW    P0 &= 0xFB
#define WR_HIGH   P0 |= 0x04

#define DATA_LOW  P0 &= 0xF7
#define DATA_HIGH P0 |= 0x08

extern u16 xdata lcd_buffer[8];
extern u8 Foold_Lcd_TimeCount;

void lcd_IOInit(void);
void send_lcd_command(u8 command);
void send_lcd_data(u8 address,u8 Data);
void flood_lcd_data(void);
void lcd_init(void);
void lcd_char(u8 name,u8 display);
void lcd_clr();
void lcd_number(u8 number,u8 position,u8 display);
void lcd_test(void);


#endif

