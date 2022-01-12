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
    "Переход на страницу ЦВЕТА", "Go ot the COLORS page",
    OnPress_Exit
);


static Item *items[7] =
{
    &bExit,
    nullptr
};


static Page page(items, nullptr, nullptr, true);

Page *PageTuneColor::self = &page;
