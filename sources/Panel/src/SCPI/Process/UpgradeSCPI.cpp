// 2022/01/18 16:01:27 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "SCPI/SCPI.h"


static pchar FuncErase(pchar);
static pchar FuncWrite(pchar);


const StructSCPI SCPI::upgrade[] =
{
    SCPI_LEAF(":ERASE", FuncErase),
    SCPI_LEAF(":WRITE", FuncWrite),
    SCPI_EMPTY()
};


static pchar FuncErase(pchar)
{
    return nullptr;
}


static pchar FuncWrite(pchar)
{
    return nullptr;
}
