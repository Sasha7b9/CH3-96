// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Colors.h"
#include "Display/Display.h"
#include "Display/Primitives.h"
#include "Settings.h"


Color Color::BLACK(0);
Color Color::WHITE(1);
Color Color::YELLOW(2);
Color Color::BLUE(3);
Color Color::RED(4);
Color Color::GREEN(5);
Color Color::GRAY_10(6);
Color Color::GRAY_50(7);
Color Color::GRAY_20(8);
Color Color::GREEN_50(9);
Color Color::GREEN_25(10);
Color Color::GREEN_10(11);
Color Color::GREEN_20(12);
Color Color::GREEN_5(13);
Color Color::GREEN_15(14);
Color Color::GREEN_12(15);
Color Color::GRAY_75(16);

Color Color::BACKGROUND_1(17);
Color Color::BACKGROUND_2(18);

Color Color::TYPE_RED(29);
Color Color::TYPE_GREEN(30);
Color Color::TYPE_BLUE(31);


uint Color::Value() const
{
    return glob_set.colors[index];
}


void Color::SetValue(uint value) const
{
    glob_set.colors[index] = value;
}


void Color::SetValue(uint8 red, uint8 green, uint8 blue) const
{
    glob_set.colors[index] = ((uint)((red) | ((green) << 8) | ((blue) << 16)));
}


uint &Color::RefValue()
{
    return glob_set.colors[index];
}


void Color::SetRED(uint8 red)
{
    RefValue() = MAKE_COLOR(red, GetGREEN(), GetBLUE());
}


void Color::SetGREEN(uint8 green)
{
    RefValue() = MAKE_COLOR(GetRED(), green, GetBLUE());
}


void Color::SetBLUE(uint8 blue)
{
    RefValue() = MAKE_COLOR(GetRED(), GetGREEN(), blue);
}
