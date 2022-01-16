// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Display/Display.h"
#include "src/Hardware/FDrive.h"
#include "Hardware/HAL/HAL.h"


#define MAIN_PROGRAM_START_ADDRESS  0x8020000


typedef void(*pFunction)();


int main()
{
    HAL::Init();

    Display::Init();
   
    FDrive::Init();

    FDrive::AttemptUpdate();
    
    
    CPU::DeInit();

    __disable_irq();
    // Теперь переходим на основную программу
    pFunction JumpToApplication;
    JumpToApplication = reinterpret_cast<pFunction>(*reinterpret_cast<__IO uint *>(MAIN_PROGRAM_START_ADDRESS + 4)); //-V2571
    __set_MSP(*(__IO uint *)MAIN_PROGRAM_START_ADDRESS);
    __enable_irq();
    JumpToApplication();

    return 0;
}
