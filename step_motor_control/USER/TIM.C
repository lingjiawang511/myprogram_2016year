#include"HeadType.h"

//=============================================================================
//��������:TIM4_Interrupts_Config
//���ܸ�Ҫ:TIM4 �ж����ȼ�����
//����˵��:��
//��������:��
//=============================================================================
static void TIM2_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}

//=============================================================================
//��������:TIM4_Interrupts_Config
//���ܸ�Ҫ:TIM4 �ж����ȼ�����
//����˵��:��
//��������:��
//=============================================================================
static void TIM4_Interrupts_Config(void)
{
     NVIC_InitTypeDef NVIC_InitStructure; 
    
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    
     NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
     NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
     NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
     NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
     NVIC_Init(&NVIC_InitStructure);
}


//=============================================================================
//��������:TIM4_Config
//���ܸ�Ҫ:TIM4 ��ʱ������
//����˵��:��
//��������:��
//=============================================================================
void TIM4_Config(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
		TIM_DeInit(TIM4);
		TIM_TimeBaseStructure.TIM_Period = 199;    //0.2MS
		TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
		TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
			
		TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
		TIM_ClearFlag(TIM4, TIM_FLAG_Update);
		TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
		TIM_Cmd(TIM4, DISABLE );    //��ʼ����������ʱ��
		//TIM_Cmd(TIM4, ENABLE ); 
		TIM4_Interrupts_Config();
}

/****************************
**TIM2��ͨ��1ʹ�õ�����ģʽ
**TIM3ʹ���ſ�ģʽ�������PWM
**
****************************/
//TIM2per:��װֵ
//Compare1:�Ƚϲ���1��Ԥװ��ֵ
void Motor_Init(u16 TIM2per, u16 TIM3per, u16 TIM3Compare1)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);//ʹ�ܶ�ʱ��2��ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//ʹ�ܶ�ʱ��3��ʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//ʹ�ܸ���IOʱ��
  
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_6;//PA0
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA,&GPIO_InitStruct);
  
  //TIM2�����ڵ�������
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//û��ʱ�ӷָ�
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
  TIM_TimeBaseInitStruct.TIM_Prescaler = 7200;//Ԥ��Ƶֵ,ÿ100us����һ��
  TIM_TimeBaseInitStruct.TIM_Period = TIM2per;//��װֵ
  TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
  
  TIM_SelectOnePulseMode(TIM2,TIM_OPMode_Single);//����TIM2�ڵ�����ģʽ�����ǵ�һ�����壬����һ�������¼�ֹͣ
  TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);//ʹ�ܶ�ʱ��2��ͨ��1Ԥװ�ؼĴ���
  TIM_SelectOutputTrigger(TIM2,TIM_TRGOSource_OC1Ref);
  
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//�����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//OC1���ʹ��
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ��
  TIM_OCInitStruct.TIM_Pulse = 1 ;//�Ƚϲ���1��Ԥװ��ֵ����������� = �Զ���װֵ - �Ƚϲ���Ĵ�����ֵ��
  TIM_OC1Init(TIM2,&TIM_OCInitStruct);                 //Tpusel = TIM_TimeBaseInitStruct.TIM_Period - TIM_OCInitStruct.TIM_Pulse;
  
  TIM_Cmd(TIM2,DISABLE);//�Ȳ�ʹ����TIM2
  TIM2_Interrupts_Config();
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
  
  //TIM3�����ڴ�ģʽ���ſ�ģʽ�µ�PWM���ģʽ
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;//û��ʱ�ӷָ�
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���ģʽ
  TIM_TimeBaseInitStruct.TIM_Prescaler = 720;//Ԥ��Ƶֵ��10us����һ��
  TIM_TimeBaseInitStruct.TIM_Period = TIM3per;//��װֵ
  TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
  
  TIM_SelectSlaveMode(TIM3, TIM_SlaveMode_Gated);//TIM3Ϊ�ſ�ģʽ
  TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);//ʹ��TIM3������ģʽ
  TIM_SelectInputTrigger(TIM3,TIM_TS_ITR1);//�ڲ���������TIM2����
  
  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;//�����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;//OC1���ʹ��
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;//��Ч��ƽΪ��
  TIM_OCInitStruct.TIM_Pulse = TIM3Compare1;//�Ƚϲ���1��Ԥװ��ֵ
  TIM_OC1Init(TIM3,&TIM_OCInitStruct);
  
  TIM_Cmd(TIM3,ENABLE);//ʹ��TIM3
}

//����PWM�����
//Cycle:Ϊ����,��λ(us)
//Pulse_Num:Ϊ���������С��3200��
void TIM2_TIM3_PWM(u16 Cycle, u16 Pulse_Num)
{
  u16 TIM3per = 0;
  u32 Time = 0;
  //�ı�TIM3����װֵ�ı�����Ƶ��������������ռ�ձ�Ϊ50%
  //�ı�TIM2��Ԥ��Ƶ������װֵ�ı��������
  TIM_Cmd(TIM2,DISABLE);//�Ȳ�ʹ����TIM2  
  Time = Cycle * Pulse_Num;
  Time /= 100;              //Ԥ��ƵΪ7200,100us����һ��
  TIM3per = Cycle/10;       //Ԥ��ƵΪ720,10us����һ��
  
  TIM_SetAutoreload(TIM2, Time+1);//����TIM2����װֵ
  TIM_SetAutoreload(TIM3, TIM3per-1);//����TIM3����װֵ
  TIM_SetCompare1(TIM3,TIM3per/2);//����ռ�ձ�Ϊ50%
  TIM_Cmd(TIM2,ENABLE);//ʹ��TIM2  
}








