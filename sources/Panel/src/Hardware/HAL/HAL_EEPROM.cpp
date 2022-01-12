// 2022/01/12 10:19:53 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Hardware/HAL/HAL.h"
#include "Settings.h"


#define ADDR_SECTOR_0   ((uint)0x08000000)  // 16k  Основная прошивка
#define ADDR_SECTOR_1   ((uint)0x08004000)  // 16k
#define ADDR_SECTOR_2   ((uint)0x08008000)  // 16k
#define ADDR_SECTOR_3   ((uint)0x0800c000)  // 16k
#define ADDR_SECTOR_4   ((uint)0x08010000)  // 64k
#define ADDR_SECTOR_5   ((uint)0x08020000)  // 128k
#define ADDR_SECTOR_6   ((uint)0x08040000)  // 128k
#define ADDR_SECTOR_7   ((uint)0x08060000)  // 128k
#define ADDR_SECTOR_SETTINGS ADDR_SECTOR_7
#define SIZE_SECTOR_SETTINGS (128 * 1024)

#define CLEAR_FLASH_FLAGS \
    __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_EOP    |  /* end of operation flag              */   \
                           FLASH_FLAG_OPERR  |  /* operation error flag               */   \
                           FLASH_FLAG_WRPERR |  /* write protected error flag         */   \
                           FLASH_FLAG_PGAERR |  /* programming alignment error flag   */   \
                           FLASH_FLAG_PGPERR |  /* programming parallelism error flag */   \
                           FLASH_FLAG_PGSERR);  /* programming sequence error flag    */


// Возвращает первый адрес, значение в котором равно 0xffffffff (можно записывать). Поиск начинается с адреса start,
// продолжается в участке памяти размером sizeFull. Кратно размеру sizeObject
static uint FindFirstFreeRecord(uint start, uint sizeSector, uint sizeRecord);


void HAL_EEPROM::LoadSettings(Settings *settings)
{
    uint address = FindLastOccupiedRecord(ADDR_SECTOR_SETTINGS, SIZE_SECTOR_SETTINGS, sizeof(Settings));

    if (address)                                            // Если нашли сохранённую запись
    {
        *settings = *(reinterpret_cast<CalibrationSettings *>(address));      // То запишем её в целевой объект //-V2571
    }
}


void HAL_EEPROM::SaveSettings(Settings *settings)
{

}
