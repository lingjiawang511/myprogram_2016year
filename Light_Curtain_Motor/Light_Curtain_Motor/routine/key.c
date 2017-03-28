#include"key.h"
#include"HT1621B.H" 
u16 xdata Key1TimerCount=0,Key2TimerCount=0,Key3TimerCount=0,Key4TimerCount=0;
bit Key1TriggerFlag,Key2TriggerFlag,Key3TriggerFlag,Key4TriggerFlag,KeyTriggerOK;
u8 KeyNum;

void Timer0Init(void)		//5毫秒@12.000MHz
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
    CKCON &=0XF8;       //设置定时器时钟选择
    CKCON |=0X02;       //设置定时器时钟system/48=1.02MHz
	TL0 = TimerLow;		//设置定时初值
	TH0 = TimerHigh;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    ET0=1;
    EA=1;
}
/*****************************************************
按键初始化程序
******************************************************/
void KeyInit()
{      
    P1MDIN|=0X3D;
    P1MDOUT&=0xD3;  
    P1SKIP&=0xD3;
    Key1=1;
    Key2=1;
    Key3=1;
    Key4=1;
    Key1TimerCount=0; 
    Key2TimerCount=0; 
    Key3TimerCount=0; 
    Key4TimerCount=0; 
    KeyTriggerOK=0;
    Timer0Init();
}
/*****************************************************
按键扫描，按键值存入KeyNum，有按键按下时KeyTriggerOK=1;
必须处理了按键程序才可以复位KeyNum和KeyTriggerOK。四个
按键，理论上只考虑两个组合此程序KeyNum有2*4*7=56种组合；
******************************************************/
void Keyscan()
{
static u8 xdata KeyNumTemp;
   if(Key1==0||Key2==0||Key3==0||Key4==0) 
   {
       if(Key1==0){
              Key1TriggerFlag=1;
              KeyNumTemp|=KeyUp;
       }
       else{
              if(Key1TimerCount<=KeyShort){  
                   KeyNumTemp&=~KeyUp;
              }
             else if((KeyShort<Key1TimerCount)&&(Key1TimerCount<KeyLong)){
                   KeyNumTemp|=KeyUp;
              }
             else{
                   KeyNumTemp&=~KeyUp;
                   KeyNumTemp|=KeyUpLong;
             }
           Key1TimerCount=0;
           Key1TriggerFlag=0;
       }         
      if(Key2==0){
             Key2TriggerFlag=1;
             KeyNumTemp|=KeyDown;
       }
       else{
              if(Key2TimerCount<=KeyShort){  
                   KeyNumTemp&=~KeyDown;
              }
             else if((KeyShort<Key2TimerCount)&&(Key2TimerCount<KeyLong)){
                   KeyNumTemp|=KeyDown;
              }
             else{
               KeyNumTemp&=~KeyDown;
               KeyNumTemp|=KeyDownLong;
             }
            Key2TimerCount=0;
            Key2TriggerFlag=0;
       }
       if(Key3==0){
             Key3TriggerFlag=1;
             KeyNumTemp|=KeyEnter;
       }
       else{
              if(Key3TimerCount<=KeyShort){  
                   KeyNumTemp&=~KeyEnter;
              }
             else if((KeyShort<Key3TimerCount)&&(Key3TimerCount<KeyLong)){
                   KeyNumTemp|=KeyEnter;
              }
             else{
               KeyNumTemp&=~KeyEnter;
               KeyNumTemp|=KeyEnterLong;
             }
             Key3TimerCount=0;
             Key3TriggerFlag=0;
       }
       if(Key4==0){
             Key4TriggerFlag=1;
             KeyNumTemp|=KeyBack;
       }
       else{
              if(Key4TimerCount<=KeyShort){  
                   KeyNumTemp&=~KeyBack;
              }
             else if((KeyShort<Key4TimerCount)&&(Key4TimerCount<KeyLong)){
                   KeyNumTemp|=KeyBack;
              }
             else{
               KeyNumTemp&=~KeyBack;
               KeyNumTemp|=KeyBackLong;
             }
           Key4TimerCount=0;
           Key4TriggerFlag=0;
       }
   }
   else{
     KeyNum=KeyNumTemp;
     KeyNumTemp=0; 
     if(KeyNum!=0)
        KeyTriggerOK=1;
    }
}
void timer0() interrupt  1 
{
	TL0 = TimerLow;		//设置定时初值
	TH0 = TimerHigh;		//设置定时初值
    Foold_Lcd_TimeCount++;
    Keyscan();
    if(Key1TriggerFlag)
        Key1TimerCount++;
    if(Key2TriggerFlag)
        Key2TimerCount++;
    if(Key3TriggerFlag)
        Key3TimerCount++;
    if(Key4TriggerFlag)
        Key4TimerCount++;
}