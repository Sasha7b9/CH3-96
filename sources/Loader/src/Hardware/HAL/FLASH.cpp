// 2022/01/17 15:29:42 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/FLASH.h"
#include "Hardware/HAL/HAL.h"



void FLASH_::Prepare()
{
    uint8 *address = (uint8 *)ADDR_SECTOR_PROGRAM_TEMP;

    for (int i = 0; i < 128 * 1024; i++)
    {
        if (address[i] != 0xFF)
        {
            HAL_EEPROM::EraseSector(ADDR_SECTOR_PROGRAM_TEMP);
            break;
        }
    }

    
}


void FLASH_::WriteData(uint, void *, int)
{

}
