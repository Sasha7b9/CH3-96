// 2022/01/12 14:09:50 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Other/PageTuneColor.h"
#include "Menu/Menu.h"
#include "Menu/MenuItemsDef.h"
#include "Menu/Pages/Other/PageColors.h"


static void OnPress_Exit()
{
    Menu::SetOpenedPage(PageColors::self);
}


DEF_BUTTON(bExit,
    "Выход", "Exit",
    "Переход на страницу ЦВЕТА", "Go to the COLORS page",
    OnPress_Exit
);


DEF_COLOR_GOVERNOR(gRed,
    "", "",
    Color::RED
);


DEF_COLOR_GOVERNOR(gGreen,
    "", "",
    Color::GREEN
);


DEF_COLOR_GOVERNOR(gBlue,
    "", "",
    Color::BLUE
);


static Item *items[7] =
{
    &bExit,
    &gRed,
    &gGreen,
    &gBlue,
    nullptr
};


static Page page(items, nullptr, nullptr, true);

Page *PageTuneColor::self = &page;
