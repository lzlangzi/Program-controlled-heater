
#include "include.h"  
  
  
void store(u8 hz);
{
  FLASH_DeInit();
  FLASH_Unlock(FLASH_MEMTYPE_DATA);
  FLASH_EraseByte(0x4000);
  FLASH_ProgramByte(0x4000, hz);
  hz = FLASH_ReadByte(0x4000);   //∂¡»°
}