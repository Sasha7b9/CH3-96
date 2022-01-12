// 2022/01/12 11:54:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Other/PageColors.h"
#include "Menu/Menu.h"
#include "Menu/MenuItemsDef.h"
#include "Menu/Pages/PageService.h"


static void Draw_Colors()
{

}


void PageColors::UpdateInput()
{
}


static void OnPress_Exit()
{
    Menu::SetOpenedPage(PageService::self);
}


DEF_BUTTON(bExit,
    "Выход", "Exit",
    "Переход на страницу СЕРВИС", "Go to the SERVICE page",
    OnPress_Exit
);


static Item *items[7] =
{
    &bExit,
    nullptr
};


static Page page(items, nullptr, Draw_Colors);


Page *PageColors::self = &page;
