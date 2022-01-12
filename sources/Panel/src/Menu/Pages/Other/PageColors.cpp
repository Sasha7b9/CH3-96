// 2022/01/12 11:54:35 (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Menu/Pages/Other/PageColors.h"
#include "Menu/Menu.h"
#include "Menu/MenuItemsDef.h"
#include "Menu/Pages/PageService.h"
#include "Display/Primitives.h"
#include "Settings.h"


static void OnPress_Exit()
{
    Menu::SetOpenedPage(PageService::self);
}


DEF_BUTTON(bExit,
    "Выход", "Exit",
    "Переход на страницу СЕРВИС", "Go to the SERVICE page",
    OnPress_Exit
);


static void OnChanged_Color()
{
    extern Choice cColor;
    extern GovernorChannelColor gRed;
    extern GovernorChannelColor gGreen;
    extern GovernorChannelColor gBlue;

    static uint *colors[2] = {
        &COLOR(Color::BACKGROUND_1.value),
        &COLOR(Color::BACKGROUND_2.value)
    };

    uint *color = colors[cColor.Value()];

    gRed.SetValue(RED_FROM_COLOR(*color));
    gGreen.SetValue(GREEN_FROM_COLOR(*color));
    gBlue.SetValue(BLUE_FROM_COLOR(*color));
}


DEF_CHOICE_2(cColor,
    "Выбор настраиваемого цвета", "Choosing a custom color",
    "Фон 1",  "Фон 2",
    "Back 1", "Back 2",
    OnChanged_Color
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
    &cColor,
    &gRed,
    &gGreen,
    &gBlue,
    nullptr
};


static Page page(items, nullptr, nullptr, true);


Page *PageColors::self = &page;


void PageColors::Init()
{
    OnChanged_Color();
}
