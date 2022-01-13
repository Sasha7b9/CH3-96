// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#pragma once
#include "defines.h"


struct Color
{
    static Color GRAY_20;   // 20% серого
    static Color GRAY_50;   // 50% серого
    static Color GRAY_75;   // 75% серого
    static Color GREEN_5;
    static Color GREEN_10;
    static Color GREEN_12;
    static Color GREEN_15;
    static Color GREEN_20;
    static Color GREEN_25;

    static Color WHITE;             // Белый

    static Color BACK_UNSELECT;     // Фон невыделенного итема
    static Color BACK;              // Чёрный фон
    static Color FILL;              // Цвет белых надписей
    static Color BACKGROUND_1;
    static Color BACKGROUND_2;
    static Color TYPE_RED;          // Красный компонент для настройки
    static Color TYPE_GREEN;        // Зелёный компонент для настройки
    static Color TYPE_BLUE;         // Синий компонент для настройки

    static const int Count = 32;

    explicit Color(uint8 i) : index(i) {};

    void SetAsCurrent() const;
    static Color GetCurrent();

    uint8 Index() const { return index;  }

    void SetValue(uint value) const { Value() = value; }
    void SetValue(uint8 red, uint8 green, uint8 blue) const { Value() = Make(red, green, blue); }

    // Ссылка на значение
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
