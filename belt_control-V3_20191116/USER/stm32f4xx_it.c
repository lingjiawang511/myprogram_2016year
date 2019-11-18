/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include"HeadType.h"
#include "usart.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1) {
    }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1) {
    }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1) {
    }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1) {
    }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}
//=============================================================================
//????????:TIM2_IRQHandler
//??????:TIM2 ?��????
//???????:??
//????????:??
//=============================================================================
void TIM2_IRQHandler(void)
{
    static u8 key = 0;
    if ( TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET ) {
        Led_Flash();
        key = Key_Scan();
        if (key > 0) {
            Key_ScanNum = key;
            key = 0;
        }
        belt11_time_control();
        belt12_time_control();
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
    }
}
//=============================================================================
//????????:TIM3_IRQHandler
//??????:TIM3 ?��????
//???????:??
//????????:??
//=============================================================================
void TIM3_IRQHandler(void)
{
    if ( TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET ) {
        if (1 == Usart1_Control_Data.rx_start) {
            if (Auto_Frame_Time1 > 0) {
                Auto_Frame_Time1--;
            } else {
                Auto_Frame_Time1 = 0;
                Usart1_Control_Data.rx_aframe = 1;
                Usart1_Control_Data.rx_count = Usart1_Control_Data.rx_index;
                Usart1_Control_Data.rx_start = 0;
                Usart1_Control_Data.rx_index = 0;
            }
        }
        if (1 == Usart2_Control_Data.rx_start) {
            if (Auto_Frame_Time2 > 0) {
                Auto_Frame_Time2--;
            } else {
                Auto_Frame_Time2 = 0;
                Usart2_Control_Data.rx_aframe = 1;
                Usart2_Control_Data.rx_count = Usart2_Control_Data.rx_index;
                Usart2_Control_Data.rx_start = 0;
                Usart2_Control_Data.rx_index = 0;
            }
        }

        TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
    }
}
void USART1_IRQHandler(void)
{
    if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) || USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET) { //�������û������һֱ���жϵ�����
        USART1_Do_Rx(USART_ReceiveData(USART1));
        USART_ClearFlag(USART1, USART_FLAG_RXNE);
    }
    if (USART_GetFlagStatus(USART1, USART_FLAG_TC)) {
        USART1_Do_Tx();
        USART_ClearFlag(USART1, USART_FLAG_TC);
    }
    if (USART_GetFlagStatus(USART1, USART_FLAG_LBD)) {
        USART_ClearFlag(USART1, USART_FLAG_LBD);
    }
    if (USART_GetFlagStatus(USART1, USART_FLAG_ORE)) {
        USART_ClearFlag(USART1, USART_FLAG_ORE);
    }
		if (USART_GetFlagStatus(USART1, USART_FLAG_TXE)) {
        USART_ClearFlag(USART1, USART_FLAG_TXE);
    }
}
void USART2_IRQHandler(void)
{
    if (USART_GetFlagStatus(USART2, USART_FLAG_RXNE) || USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET) { //�������û������һֱ���жϵ�����
        USART2_Do_Rx(USART_ReceiveData(USART2));
        USART_ClearFlag(USART2, USART_FLAG_RXNE);
    }
    if (USART_GetFlagStatus(USART2, USART_FLAG_TC)) {
        USART2_Do_Tx();
        USART_ClearFlag(USART2, USART_FLAG_TC);
    }
    if (USART_GetFlagStatus(USART2, USART_FLAG_LBD)) {
        USART_ClearFlag(USART2, USART_FLAG_LBD);
    }
    if (USART_GetFlagStatus(USART2, USART_FLAG_ORE)) {
        USART_ClearFlag(USART2, USART_FLAG_ORE);
    }
		if (USART_GetFlagStatus(USART2, USART_FLAG_TXE)) {
        USART_ClearFlag(USART2, USART_FLAG_TXE);
    }
}
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
