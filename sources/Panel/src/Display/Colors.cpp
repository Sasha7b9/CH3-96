// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Colors.h"
#include "Display/Display.h"
#include "Display/Primitives.h"
#include "Settings.h"

Color Color::WHITE(0);

Color Color::YELLOW(2);
Color Color::BLUE(3);
Color Color::RED(4);
Color Color::GREEN(5);
Color Color::BACK_UNSELECT(6);
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

Color Color::BACK(17);
Color Color::FILL(18);
Color Color::BACKGROUND_1(19);
Color Color::BACKGROUND_2(20);

Color Color::TYPE_RED(29);
Color Color::TYPE_GREEN(30);
Color Color::TYPE_BLUE(31);


uint &Color::Value() const
{
    return glob_set.colors[index];
}
