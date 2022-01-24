// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Colors.h"
#include "Display/Display.h"
#include "Display/Primitives.h"
#include "Settings.h"

Color Color::EMPTY(0);
Color Color::FILL(1);

Color Color::BACK(2);

Color Color::MENU_UNSELECT(3);
Color Color::MENU_SELECT(4);

Color Color::TYPE_RED(5);
Color Color::TYPE_GREEN(6);
Color Color::TYPE_BLUE(7);

Color Color::WHITE(8);


uint &Color::Value() const
{
    return ColorScheme::Current().colors[index];
}


ColorScheme &ColorScheme::Current()
{
    return glob_set.schemes[glob_set.colorScheme];
}
