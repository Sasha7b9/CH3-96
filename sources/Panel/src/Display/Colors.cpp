// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Colors.h"
#include "Display/Display.h"
#include "Display/Primitives.h"
#include "Settings.h"

Color Color::WHITE(0);

Color Color::BACK(1);
Color Color::FILL(2);

Color Color::BACK_1(3);
Color Color::BACK_2(4);
Color Color::BACK_3(5);

Color Color::BACK_UNSELECT(6);
Color Color::BACK_SELECT(7);

Color Color::BACK_STAT(8);
Color Color::BACK_VALUE(9);

Color Color::TYPE_RED(10);
Color Color::TYPE_GREEN(11);
Color Color::TYPE_BLUE(12);


uint &Color::Value() const
{
    return glob_set.colors[index];
}
