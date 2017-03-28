#ifndef __ANALOG_H_
#define __ANALOG_H_
#include"delay.h"

#define  DAC0DataBuf   IDA0 
#define  DAC1DataBuf   IDA1
#define SYSCLK       49000000                 // SYSCLK frequency (Hz)

#define MDCLK        2457600              // Modulator Clock (Hz)
#define OWR          10                   // desired Output Word Rate in Hz

#define VREF         250L                 // External VREF (x 10^-2 V)





void DAC_Init();
void DAC_Dispose(u16 databuf);










#endif