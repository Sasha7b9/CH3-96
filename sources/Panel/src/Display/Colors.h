// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "defines.h"


struct Color
{
    static Color WHITE;             // �����

    static Color BACK_UNSELECT;     // ��� ������������� �����
    static Color BACK_SELECT;       // ��� ����������� �����
    static Color BACK_STAT;         // ���� ���� ��� ������� ����������
    static Color BACK_VALUE;
    static Color BACK;              // ׸���� ���
    static Color FILL;              // ���� ����� ��������
    static Color BACK_1;            // ������ ���� ����
    static Color BACK_2;            // ������ ���� ����
    static Color BACK_3;            // ���� ���� ��������
    static Color TYPE_RED;          // ������� ��������� ��� ���������
    static Color TYPE_GREEN;        // ������ ��������� ��� ���������
    static Color TYPE_BLUE;         // ����� ��������� ��� ���������

    static const int Count = 32;

    explicit Color(uint8 i) : index(i) {};

    void SetAsCurrent() const;
    static Color GetCurrent();

    uint8 Index() const { return index;  }

    void SetValue(uint value) const { Value() = value; }
    void SetValue(uint8 red, uint8 green, uint8 blue) const { Value() = Make(red, green, blue); }

    // ������ �� ��������
    uint &Value() const;

    void SetRED(uint8 red) { SetValue(red, GetGREEN(), GetBLUE()); }

    void SetGREEN(uint8 green) { SetValue(GetRED(), green, GetBLUE()); }

    void SetBLUE(uint8 blue) { SetValue(GetRED(), GetGREEN(), blue); }

    uint8 GetRED() const { return ((uint8)(Value() & 0xFF)); }

    uint8 GetGREEN() const { return ((uint8)((Value() >> 8) & 0xFF)); }

    uint8 GetBLUE() const { return ((uint8)((Value() >> 16) & 0xFF)); }

    static uint Make(uint8 r, uint8 g, uint8 b) { return ((uint)((r) | ((g) << 8) | ((b) << 16))); }

private:

    uint8 index;
};


#ifdef WIN32

    #define MAKE_COLOR(r, g, b)     ((uint)((b) | ((g) << 8) | ((r) << 16)))

    #define RED_FROM_COLOR(color)   ((uint8)(((color) >> 16) & 0xFF))
    #define GREEN_FROM_COLOR(color) ((uint8)(((color) >> 8) & 0xFF))
    #define BLUE_FROM_COLOR(color)  ((uint8)((color) & 0xFF))

#endif
