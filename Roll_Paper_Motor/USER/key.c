#include"HeadType.h"	
#define KEY_SHORT_TIME 		20
#define KEY_LONG_TIME			300
u8 Key_ScanNum;

u8 Key_Scan(void)
{
	 u8 key_num;
	 static u8 key1_triggerstate,key2_triggerstate,key3_triggerstate,key4_triggerstate;
	 static u16 key1_timercount,key2_timercount,key3_timercount,key4_timercount;
	  key_num = 0;
	 //key1
		if(READ_DEVICE1_KEY == READLOW){
			if(key1_triggerstate == 0){
				key1_triggerstate = 1;
			}else{
				key1_timercount++;
			}
		}else{
				if(key1_triggerstate == 1){
					if(key1_timercount <KEY_SHORT_TIME){
						key_num &=0xfe;
					}else if((key1_timercount >=KEY_SHORT_TIME)&&(key1_timercount <KEY_LONG_TIME)){
							key_num |=0x01;
					}else{
							key_num |=0x11;
					}
					key1_triggerstate =0;				
				}
				key1_timercount = 0;
		}
		//key2
		if(READ_DEVICE2_KEY == READLOW){
			if(key2_triggerstate == 0){
				key2_triggerstate = 1;
			}else{
				key2_timercount++;
			}
		}else{
				if(key2_triggerstate == 1){
					if(key2_timercount <KEY_SHORT_TIME){
						key_num &=0xfd;
					}else if((key2_timercount >=KEY_SHORT_TIME)&&(key2_timercount <KEY_LONG_TIME)){
							key_num |=0x02;
					}else{
							key_num |=0x22;
					}
					key2_triggerstate =0;					
				}
				key2_timercount = 0;
		}
		//key3
		if(READ_DEVICE3_KEY == READLOW){
			if(key3_triggerstate == 0){
				key3_triggerstate = 1;
			}else{
				key3_timercount++;
			}
		}else{
				if(key3_triggerstate == 1){
					if(key3_timercount <KEY_SHORT_TIME){
						key_num &=0xfb;
					}else if((key3_timercount >=KEY_SHORT_TIME)&&(key3_timercount <KEY_LONG_TIME)){
							key_num |=0x04;
					}else{
							key_num |=0x44;
					}
					key3_triggerstate =0;					
				}
				key3_timercount = 0;
		}
		//key4
		if(READ_DEVICE4_KEY == READLOW){
			if(key4_triggerstate == 0){
				key4_triggerstate = 1;
			}else{
				key4_timercount++;
			}
		}else{
				if(key4_triggerstate == 1){
					if(key4_timercount <KEY_SHORT_TIME){
						key_num &=0xf7;
					}else if((key4_timercount >=KEY_SHORT_TIME)&&(key4_timercount <KEY_LONG_TIME)){
							key_num |=0x08;
					}else{
							key_num |=0x88;
					}
					key4_triggerstate = 0;
				}
				key4_timercount = 0;
		}
	 return key_num;
}




