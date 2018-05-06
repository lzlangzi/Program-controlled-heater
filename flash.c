#include "include.h"

void Store()
{
    

    u8 hz_ch = hz + 48; 
    
    

    
//    FLASH_EraseByte(0x4008);//����ָ����ַ�Ŀռ�
//    FLASH_ProgramByte(0x4008, temp);//д��ָ����ַ�Ŀռ�
    
    FLASH_EraseByte(0x4000);//����ָ����ַ�Ŀռ�
    FLASH_ProgramByte(0x4000, hz_ch);//д��ָ����ַ�Ŀռ�

}

void Read_dat()
{
    FLASH_DeInit();
    FLASH_Unlock(FLASH_MEMTYPE_DATA);//����
   // if(FLASH_ReadByte(0x4008) == '1')//��ָ����ַ�Ŀռ��������
    hz = FLASH_ReadByte(0x4000) -48;
}






/*******************************************************************************
****��������:
****��������:����д���Block�ֽ�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:
          BlockStartAddress    �ֽڱ�д���Block�׵�ַ
          FLASH_MemType        FLASH Memory��������
          FLASH_ProgMode       FLASH ���ģʽ
          Buffer               Ҫд��flash eeprom ���ֽ�����
          BlockNum             Ҫд��flash eeprom ��Block����
****���ڲ���:��
****˵��:ÿ���ͺŵ�EEPROM�Ĵ�С��һ�������ô˺�����ʱ��Ҫע�⽫Ҫд�����ֽ�����
         �Ĵ�С�Ƿ񳬹����ͺŵ�EEPROM�ĵ�ַ��
         ��������EEPROM���ͺ���STM8S208, STM8S207, STM8S007, STM8AF52Ax, STM8AF62Ax 
         EEPROM�ĵ�ַ�Ǵ�0x004000��0x0047ff����2048Byte,ÿ��Block��128Byte,һ��16��Block.
         ��������EEPROM���ͺ���STM8S105, STM8S005, STM8AF626x
         EEPROM�ĵ�ַ�Ǵ�0x004000��0x0043ff����1024Byte,ÿ��Block��128Byte,һ��8��Block.
         С������EEPROM���ͺ���STM8S103, STM8S003, STM8S903 
         EEPROM�ĵ�ַ�Ǵ�0x004000��0x00427f����1024Byte,ÿ��Block��64Byte,һ��10��Block.
********************************************************************************/
void WriteMultiBlockByte(u8 BlockStartAddress,FLASH_MemType_TypeDef FLASH_MemType, 
                FLASH_ProgramMode_TypeDef FLASH_ProgMode, uint8_t *Buffer,uint8_t BlockNum)
{
  uint8_t  BlockNum_Temp;
  /* ���� flash data eeprom memory */
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  /* �ȴ� Data EEPROM area ������־λ��λ*/
  while (FLASH_GetFlagStatus(FLASH_FLAG_DUL) == RESET)
       ;
  for(BlockNum_Temp=BlockStartAddress;BlockNum_Temp<BlockNum;BlockNum_Temp++)
  {
    if(BlockNum_Temp>FLASH_DATA_BLOCKS_NUMBER)
      break;
    FLASH_ProgramBlock(BlockNum_Temp, FLASH_MemType, FLASH_ProgMode,Buffer+BlockNum_Temp*FLASH_BLOCK_SIZE);
    FLASH_WaitForLastOperation(FLASH_MemType);
  }
  
  FLASH_Lock(FLASH_MEMTYPE_DATA);/*������Ҫ����*/

}
/*******************************************************************************
****��������:
****��������:��������Block�ֽ�
****�汾:V1.0
****����:14-2-2014
****��ڲ���:
         BlockStartAddress    ��Block�׵�ַ
         BlockNum             ������Block
         ReadBlockByte[]      ��Ŷ����ֽڵ�����
****���ڲ���:��
****˵��:ÿ���ͺŵ�EEPROM�Ĵ�С��һ�������ô˺�����ʱ��Ҫע�⽫Ҫд�����ֽ�����
         �Ĵ�С�Ƿ񳬹����ͺŵ�EEPROM�ĵ�ַ��
         ��������EEPROM���ͺ���STM8S208, STM8S207, STM8S007, STM8AF52Ax, STM8AF62Ax 
         EEPROM�ĵ�ַ�Ǵ�0x004000��0x0047ff����2048Byte,ÿ��Block��128Byte,һ��16��Block.
         BlockNum @ 1~16
         ��������EEPROM���ͺ���STM8S105, STM8S005, STM8AF626x
         EEPROM�ĵ�ַ�Ǵ�0x004000��0x0043ff����1024Byte,ÿ��Block��128Byte,һ��8��Block.
         BlockNum @ 1~8
         С������EEPROM���ͺ���STM8S103, STM8S003, STM8S903 
         EEPROM�ĵ�ַ�Ǵ�0x004000��0x00427f����1024Byte,ÿ��Block��64Byte,һ��10��Block.
         BlockNum @ 1~10
********************************************************************************/
void ReadMultiBlockByte(u8 BlockStartAddress,uint8_t BlockNum,
                        uint8_t ReadBlockByte[])
{
  uint32_t add, start_add, stop_add;
  start_add = FLASH_DATA_START_PHYSICAL_ADDRESS+(u32)((BlockNum-1)*FLASH_BLOCK_SIZE);
  stop_add = FLASH_DATA_START_PHYSICAL_ADDRESS + (u32)(BlockNum*FLASH_BLOCK_SIZE);
 
  for (add = start_add; add < stop_add; add++)
      ReadBlockByte[add-FLASH_DATA_START_PHYSICAL_ADDRESS]=FLASH_ReadByte(add);
 
  
}

/******************* (C) COPYRIGHT 2014 LENCHIMCU.TAOBAO.COM ******************/