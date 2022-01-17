// 2022/01/17 15:29:42 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/FLASH.h"
#include "Hardware/HAL/HAL.h"



void FLASH_::Prepare()
{
    HAL_EEPROM::EraseSector(ADDR_SECTOR_PROGRAM_TEMP);
}


void FLASH_::WriteData(uint, void *, int)
{

}
