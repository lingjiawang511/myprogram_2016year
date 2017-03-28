#include"delay.h"
#include"intrins.h"

void Delay_500ns(u16 delay)
{
       while(delay--)    //49Mhz,1Tmodule
        {
         _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); _nop_(); 
         _nop_(); _nop_();
            
        }
}

void Delay_ms(u16 delay)
{
    while(delay--)
      Delay_500ns(2000);
}