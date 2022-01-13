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
    glob_set.Save();
}


DEF_BUTTON(bExit,
    "Выход", "Exit",
    "Переход на страницу СЕРВИС", "Go to the SERVICE page",
    OnPress_Exit
);


extern Choice cColor;
extern GovernorChannelColor gRed;
extern GovernorChannelColor gGreen;
extern GovernorChannelColor gBlue;

static Color colors[2] =
{
    Color::BACKGROUND_1,
    Color::BACKGROUND_2
};


static void OnChanged_Color()
{
    Color color = colors[cColor.Value()];

    gRed.SetValue(color.GetRED());
    gGreen.SetValue(color.GetGREEN());
    gBlue.SetValue(color.GetBLUE());
}


static void OnChanged_Red(uint8)
{
    colors[cColor.Value()].SetRED((uint8)gRed.Value());
}


static void OnChanged_Green(uint8)
{
    colors[cColor.Value()].SetGREEN((uint8)gGreen.Value());
}


static void OnChanged_Blue(uint8)
{
    colors[cColor.Value()].SetBLUE((uint8)gBlue.Value());
}


DEF_CHOICE_2(cColor,
    "Выбор настраиваемого цвета", "Choosing a custom color",
    "Фон 1",  "Фон 2",
    "Back 1", "Back 2",
    OnChanged_Color
);


DEF_COLOR_GOVERNOR(gRed,
    GovernorChannelColor::Red,
    "", "",
    OnChanged_Red
);


DEF_COLOR_GOVERNOR(gGreen,
    GovernorChannelColor::Green,
    "", "",
    OnChanged_Green
);


DEF_COLOR_GOVERNOR(gBlue,
    GovernorChannelColor::Blue,
    "", "",
    OnChanged_Blue
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
