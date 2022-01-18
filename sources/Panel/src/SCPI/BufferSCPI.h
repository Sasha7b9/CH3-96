// 2022/01/18 16:47:22 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once


/*
    Хранит принятые данные
*/


struct StructSCPI;


class BufferSCPI
{
public:

    BufferSCPI(int size = 0);

    ~BufferSCPI();

    void Append(uint8 *data, int size);

    void Realloc(int size);

    void Fill(uint8 value);

    uint8 *data;

    int Size() const { return size; }

    char *DataChar() { return reinterpret_cast<char *>(data); }

    // Переводим символы до первого разделительного символа в верхний регистр, если не находимся в режиме приёма байт
    void ToUpper();

    uint8 *Process(const StructSCPI structs[]);

    // Удалить из буфера все данные до end включительно
    void RemoveFromBegin(uint8 *end);

private:

    int size;

    void Free();

    void Malloc(int size);
};
