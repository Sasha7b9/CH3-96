// 2022/01/11 09:34:24 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Other/PageInfo.h"
#include "Menu/Menu.h"
#include "Menu/Pages/PageService.h"
#include "Menu/MenuItemsDef.h"
#include "Display/Primitives.h"
#include "Display/Text.h"
#include "Display/Display.h"
#include "Settings.h"


using namespace Primitives;


static void Draw_Info()
{
    Rectangle(470, 225).FillRounded(5, 5, 1, Color::GREEN_20, Color::WHITE);

    int dy = 5;

    Text(NAME_MODEL).Write(0, 30 + dy, Display::PHYSICAL_WIDTH, Color::WHITE);

    Text("---------------------------------------------").Write(40, 75 + dy);

    Text(String("%s : %s",
        LANG_IS_RU ? "Программное обеспечение" : "Software",
        STR_NUM_VERSION)).Write(50, 120 + dy);

    Text(String("CRC32 : %s", STR_CRC32)).Write(50, 160 + dy);
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


static Item* items[7] =
{
    &bExit,
    nullptr
};


static Page pageInfo(items, nullptr, Draw_Info);


Page* PageInfo::self = &pageInfo;
