/**
  ******************************************************************************
  * @file    STM32F4xx_IAP/src/flash_if.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    10-October-2011
  * @brief   This file provides all the memory related operation functions.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/** @addtogroup STM32F4xx_IAP
  * @{
  */

/* Includes ------------------------------------------------------------------*/
#include "flash_if.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static uint32_t GetSector(uint32_t Address);
#if APP_USE_IAP
const u8 verify_sector[16 * 1024] __attribute__ ((at(0x08008000)));
#endif
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Unlocks Flash for write access
  * @param  None
  * @retval None
  */
void FLASH_If_Init(void)
{
    FLASH_Unlock();

    /* Clear pending flags (if any) */
    FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
                    FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR | FLASH_FLAG_PGSERR);
}

/**
  * @brief  This function does an erase of all user flash area
  * @param  StartSector: start of user flash area
  * @retval 0: user flash area successfully erased
  *         1: error occurred
  */
uint32_t FLASH_If_Erase(uint32_t StartSector)
{
    uint32_t UserStartSector = FLASH_Sector_1, i = 0;

    /* Get the sector where start the user flash area */
    UserStartSector = GetSector(APPLICATION_ADDRESS);
#if (FLASH_512K == 1)
    for (i = UserStartSector; i <= FLASH_Sector_7; i += 8) {
#else
    for (i = UserStartSector; i <= FLASH_Sector_11; i += 8) {
#endif
        /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
           be done by word */
        if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE) {
            /* Error occurred while page erase */
            return (1);
        }
    }

    return (0);
}

/**
  * @brief  This function writes a data buffer in flash (data are 32-bit aligned).
  * @note   After writing data buffer, the flash content is checked.
  * @param  FlashAddress: start address for writing data buffer
  * @param  Data: pointer on data buffer
  * @param  DataLength: length of data buffer (unit is 32-bit word)
  * @retval 0: Data successfully written to Flash memory
  *         1: Error occurred while writing data in Flash memory
  *         2: Written Data in flash memory is different from expected one
  */
uint32_t FLASH_If_Write(__IO uint32_t* FlashAddress, uint32_t* Data, uint32_t DataLength)
{
    uint32_t i = 0;

    for (i = 0; (i < DataLength) && (*FlashAddress <= (USER_FLASH_END_ADDRESS - 4)); i++) {
        /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
           be done by word */
        if (FLASH_ProgramWord(*FlashAddress, *(uint32_t*)(Data + i)) == FLASH_COMPLETE) {
            /* Check the written value */
            if (*(uint32_t*)*FlashAddress != *(uint32_t*)(Data + i)) {
                /* Flash content doesn't match SRAM content */
                return (2);
            }
            /* Increment FLASH destination address */
            *FlashAddress += 4;
        } else {
            /* Error occurred while writing data in Flash memory */
            return (1);
        }
    }

    return (0);
}

/**
  * @brief  Returns the write protection status of user flash area.
  * @param  None
  * @retval 0: No write protected sectors inside the user flash area
  *         1: Some sectors inside the user flash area are write protected
  */
uint16_t FLASH_If_GetWriteProtectionStatus(void)
{
    uint32_t UserStartSector = FLASH_Sector_1;

    /* Get the sector where start the user flash area */
    UserStartSector = GetSector(APPLICATION_ADDRESS);

    /* Check if there are write protected sectors inside the user flash area */
    if ((FLASH_OB_GetWRP() >> (UserStartSector / 8)) == (0xFFF >> (UserStartSector / 8))) {
        /* No write protected sectors inside the user flash area */
        return 1;
    } else {
        /* Some sectors inside the user flash area are write protected */
        return 0;
    }
}

/**
  * @brief  Disables the write protection of user flash area.
  * @param  None
  * @retval 1: Write Protection successfully disabled
  *         2: Error: Flash write unprotection failed
  */
uint32_t FLASH_If_DisableWriteProtection(void)
{
    __IO uint32_t UserStartSector = FLASH_Sector_1, UserWrpSectors = OB_WRP_Sector_1;

    /* Get the sector where start the user flash area */
    UserStartSector = GetSector(APPLICATION_ADDRESS);

    /* Mark all sectors inside the user flash area as non protected */
    UserWrpSectors = 0xFFF - ((1 << (UserStartSector / 8)) - 1);

    /* Unlock the Option Bytes */
    FLASH_OB_Unlock();

    /* Disable the write protection for all sectors inside the user flash area */
    FLASH_OB_WRPConfig(UserWrpSectors, DISABLE);

    /* Start the Option Bytes programming process. */
    if (FLASH_OB_Launch() != FLASH_COMPLETE) {
        /* Error: Flash write unprotection failed */
        return (2);
    }

    /* Write Protection successfully disabled */
    return (1);
}

/**
  * @brief  Gets the sector of a given address
  * @param  Address: Flash address
  * @retval The sector of a given address
  */
static uint32_t GetSector(uint32_t Address)
{
    uint32_t sector = 0;

    if ((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0)) {
        sector = FLASH_Sector_0;
    } else if ((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1)) {
        sector = FLASH_Sector_1;
    } else if ((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2)) {
        sector = FLASH_Sector_2;
    } else if ((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3)) {
        sector = FLASH_Sector_3;
    } else if ((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4)) {
        sector = FLASH_Sector_4;
    } else if ((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5)) {
        sector = FLASH_Sector_5;
    } else if ((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6)) {
        sector = FLASH_Sector_6;
    } else if ((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7)) {
        sector = FLASH_Sector_7;
    } else if ((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8)) {
        sector = FLASH_Sector_8;
    } else if ((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9)) {
        sector = FLASH_Sector_9;
    } else if ((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10)) {
        sector = FLASH_Sector_10;
    } else { /*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
        sector = FLASH_Sector_11;
    }
    return sector;
}

//��ȡָ����ַ�İ���(16λ����)
//faddr:����ַ
//����ֵ:��Ӧ����.
u32 STMFLASH_ReadWord(u32 faddr)
{
    return *(vu32*)faddr;
}
//��ȡĳ����ַ���ڵ�flash����
//addr:flash��ַ
//����ֵ:0~11,��addr���ڵ�����
uint16_t STMFLASH_GetFlashSector(u32 addr)
{
    if (addr < ADDR_FLASH_SECTOR_1)return FLASH_Sector_0;
    else if (addr < ADDR_FLASH_SECTOR_2)return FLASH_Sector_1;
    else if (addr < ADDR_FLASH_SECTOR_3)return FLASH_Sector_2;
    else if (addr < ADDR_FLASH_SECTOR_4)return FLASH_Sector_3;
    else if (addr < ADDR_FLASH_SECTOR_5)return FLASH_Sector_4;
    else if (addr < ADDR_FLASH_SECTOR_6)return FLASH_Sector_5;
    else if (addr < ADDR_FLASH_SECTOR_7)return FLASH_Sector_6;
    else if (addr < ADDR_FLASH_SECTOR_8)return FLASH_Sector_7;
    else if (addr < ADDR_FLASH_SECTOR_9)return FLASH_Sector_8;
    else if (addr < ADDR_FLASH_SECTOR_10)return FLASH_Sector_9;
    else if (addr < ADDR_FLASH_SECTOR_11)return FLASH_Sector_10;
    return FLASH_Sector_11;
}
//��ָ����ַ��ʼд��ָ�����ȵ�����
//�ر�ע��:��ΪSTM32F4������ʵ��̫��,û�취���ر�����������,���Ա�����
//         д��ַ�����0XFF,��ô���Ȳ������������Ҳ�������������.����
//         д��0XFF�ĵ�ַ,�����������������ݶ�ʧ.����д֮ǰȷ��������
//         û����Ҫ����,��������������Ȳ�����,Ȼ����������д.
//�ú�����OTP����Ҳ��Ч!��������дOTP��!
//OTP�����ַ��Χ:0X1FFF7800~0X1FFF7A0F
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ4�ı���!!)
//pBuffer:����ָ��
//NumToWrite:��(32λ)��(����Ҫд���32λ���ݵĸ���.)
uint32_t STMFLASH_Write(uint32_t FlashbaseAddr, uint32_t RomAddr, uint16_t NumToWrite,uint8_t *pRomData)
{
    FLASH_Status status = FLASH_COMPLETE;
    uint32_t startaddress = 0;
	  uint32_t FlashAddress;
	  uint32_t i = 0;
	  uint32_t datasource;
	  
	  startaddress = FlashbaseAddr+RomAddr;              //д�����ʼ��ַ
    if (startaddress < STM32_FLASH_BASE || startaddress % 4){
			return 1; //�Ƿ���ַ
		}
    FLASH_Unlock();                                 //����
    FLASH_DataCacheCmd(DISABLE);//FLASH�����ڼ�,�����ֹ���ݻ���

    startaddress = FlashbaseAddr+RomAddr;              //д�����ʼ��ַ
    if (startaddress < 0X1FFF0000) {    //ֻ�����洢��,����Ҫִ�в�������!!
         status = FLASH_EraseSector(STMFLASH_GetFlashSector(startaddress), VoltageRange_3); //VCC=2.7~3.6V֮��!!
        if (status != FLASH_COMPLETE) {
									FLASH_DataCacheCmd(ENABLE);   //FLASH��������,�������ݻ���
									FLASH_Lock();//����
									return 2;//����������
        }
    }		
		
    if (status == FLASH_COMPLETE) {
			  i = NumToWrite / 4;//����4�ı��������鲹��
        datasource = (uint32_t)pRomData;
        FlashAddress = startaddress;
			   while (i-- > 0) {
            if (FLASH_ProgramWord( FlashAddress, *(uint32_t *)datasource) != FLASH_COMPLETE) {
              FLASH_DataCacheCmd(ENABLE);   //FLASH��������,�������ݻ���
							FLASH_Lock();//����    
							return 3;  //д���쳣,��У�����Ӧ����ѭ��������
            }
            if (*(uint32_t *)FlashAddress != *(uint32_t *)datasource) {
              FLASH_DataCacheCmd(ENABLE);   //FLASH��������,�������ݻ���
							FLASH_Lock();//���� 
							return 4;
            }
            datasource += 4;
            FlashAddress += 4;
        }
    }
    FLASH_DataCacheCmd(ENABLE);   //FLASH��������,�������ݻ���
    FLASH_Lock();//����
		return 0;
}

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToRead:��(4λ)��
void STMFLASH_Read(u32 ReadAddr, u32 *pBuffer, u32 NumToRead)
{
    u32 i;
    for (i = 0; i < NumToRead; i++) {
        pBuffer[i] = STMFLASH_ReadWord(ReadAddr); //��ȡ4���ֽ�.
        ReadAddr += 4; //ƫ��4���ֽ�.
    }
}


/**
  * @}
  */

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
