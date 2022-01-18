// 2022/01/18 16:47:30 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "SCPI/BufferSCPI.h"
#include "SCPI/SCPI.h"
#include <cstdlib>
#include <cstring>



BufferSCPI::BufferSCPI(int s)
{
    Malloc(s);
}


BufferSCPI::~BufferSCPI()
{
    Free();
}


void BufferSCPI::Realloc(int _size)
{
    Free();
    Malloc(_size);
}


void BufferSCPI::Fill(uint8 value)
{
    if (size)
    {
        std::memset(data, value, static_cast<uint>(size));
    }
}


void BufferSCPI::Free()
{
    std::free(data);
    data = nullptr;
    size = 0U;
}


void BufferSCPI::Malloc(int s)
{
    if (s > 0)
    {
        data = static_cast<uint8 *>(std::malloc(static_cast<uint>(s)));
        size = (data) ? s : 0;

        if(!data)
        {
//            LOG_ERROR("Нет памяти");
        }
    }
    else
    {
        data = nullptr;
        size = 0U;
    }
}


uint8 *BufferSCPI::Process(const StructSCPI strct[])
{
    while (!strct->IsEmpty())
    {
        pchar end = SCPI::SU::BeginWith(data, strct->key);

        if (end)
        {
            if (strct->IsNode())
            {
                return ProcessNode(end, strct);
            }
            else if (strct->IsLeaf())
            {
                return ProcessLeaf(end, strct);
            }
        }

        strct++;
    }

    badSymbols.Append(*buffer);     // Перебрали все ключи в strct и не нашли ни одного соответствия. Поэтому
                                    //помещаем начальный разделитель в бракованные символы

    return buffer + 1;
}
