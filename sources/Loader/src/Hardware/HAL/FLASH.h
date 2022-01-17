// 2022/01/17 15:29:54 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


namespace FLASH_
{
    static const uint ADDR_SECTOR_PROGRAM_0 = 0x80200000;
    static const uint ADDD_SECTOR_PROGRAM_TEMP = ADDR_SECTOR_PROGRAM_0 + 1024 * 128;

    void Prepare();

    void WriteData(uint address, void *buffer, int numBytes);
}
