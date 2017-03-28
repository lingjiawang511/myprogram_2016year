#include"Analog.h"

/*******************************************************************
(DA1<<8)+DA0=16位DA 由于DA0太小，电阻不好配放减小倍电流，电阻放大一倍
DA1和DA0是电流型输入，转换为16位0-5电压型输出R1=4.98K,R0=19.5*2A
9.1K并联11K电阻刚好等于4.98K
********************************************************************/
void DAC_Init()
{
    P1MDIN &=0X3f;       //configured P1.6andP1.7 as an analog
    P1SKIP |=0xc0;       // P1.6andP1.7 is skipped by the Crossbar
    while(AD0BUSY);
  //  REF0CN =0x03;	/*内部偏压发生器和电压基准缓冲器工作，基准从VREF引脚输出*/
    ADC0CF |=0X04;      //select the external VERF for the ADC compare source
    IDA0CN &=0X70;
    IDA0CN |=0XF9;      //LOW 2BIT 00/0.25MA 0A/0.5MA 02/1MA 03/2MA
    IDA1CN &=0X70;
    IDA1CN |=0XFA;      //LOW 2BIT 00/0.25MA 0A/0.5MA 02/1MA 03/2MA
}
void ADC0_Init (void)
{
    unsigned ADC0_decimation;
    REF0CN &= ~0x01;                       // disable internal vref
    /*
       REF0CN |= 0x01;                        // (enable if using internal vref)
    */
    ADC0CN = 0x17;                         // Bipolar output codes, GAIN=128
    /*
       ADC0CF = 0x00;                         // interrupts upon SINC3 filter output
                                              // and uses internal VREF
    */
    ADC0CF = 0x04;                         // interrupts upon SINC3 filter output
    // and uses external VREF
    // Generate MDCLK for modulator.
    // Ideally MDCLK = 2.4576
    ADC0CLK = (SYSCLK/MDCLK)-1;
    // Ideally, MDCLK = 2.4576 MHz
//   ADC0DEC = 0x7FF;                     // set slowest OWR
    // program decimation rate for desired OWR
    ADC0_decimation = (unsigned long) SYSCLK/ (unsigned long) OWR /
                      (unsigned long) (ADC0CLK+1)/(unsigned long)128;
    ADC0_decimation--;
    ADC0DEC = ADC0_decimation;
    ADC0BUF = 0x00;                        // Turn off Input Buffers
    // Select Mux inputs
//   ADC0MUX = 0x08;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => AIN0.0
    // AIN- => AGND
//   ADC0MUX = 0x00;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => AIN0.0
    // AIN- => AIN0.0
    ADC0MUX = 0x01;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => AIN0.0
    // AIN- => AIN0.1
//   ADC0MUX = 0x10;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => AIN0.1
    // AIN- => AIN0.0
//   ADC0MUX = 0x32;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => AIN0.3
    // AIN- => AIN0.2
//   ADC0MUX = 0x54;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => AIN0.5
    // AIN- => AIN0.4
//   ADC0MUX = 0x76;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => AIN0.7
    // AIN- => AIN0.6
//   ADC0MUX = 0xff;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => Temp+
    // AIN- => Temp-
    // ADC0MUX = 0x88;                        // Input pin selection:
    // Setup for differential measurements
    // AIN+ => AGND
    // AIN- => AGND
    ADC0MD = 0x81;      // Start internal calibration
    while(AD0CALC != 1);// Wait until calibration is complete,Take A Long Time In Gain=128

    EIE1   |= 0x08;   // Enable ADC0 Interrupts
    ADC0MD  = 0x80;    // Enable the ADC0 (IDLE Mode)

    ADC0MD &= ~0x07;  // clear bits (put ADC0 in IDLE
    AD0INT = 0;       // clear pending sample indication
    ADC0MD = 0x83;    // Start continuous conversions
}

void DAC_Dispose(u16 databuf)
{
    DAC0DataBuf=databuf&0x00ff;  
    DAC0DataBuf=(databuf>>8)&0x00ff;   
}