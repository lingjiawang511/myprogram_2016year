#ifndef __KEY_H_
#define __KEY_H_

#include"delay.h"

#define TimerHigh (65500-5000)/256
#define TimerLow  (65500-5000)%256
sbit Key1=P1^2;
sbit Key2=P1^3;
sbit Key3=P1^4;
sbit Key4=P1^5;
enum{
    KeyNo=0,
    KeyUp=0x01,
    KeyDown=0x02,
    KeyEnter=0x04,
    KeyBack=0x8,
  //  KeyCentre=5,
    KeyUpLong=0x10,
    KeyDownLong=0x20,
    KeyEnterLong=0x40,
    KeyBackLong=0x80,
  //  KeyCentreLong=15,
};

enum{
    KeyShort=30,
    KeyLong=100
};


extern u8 KeyNum;
extern bit KeyTriggerOK;
void Timer0Init(void);		//5∫¡√Î@12.000MHz
void KeyInit();
void Keyscan();

#endif