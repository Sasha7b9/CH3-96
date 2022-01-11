// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings.h"
#include "Menu/Menu.h"
#include "Menu/MenuItemsDef.h"
#include "Menu/Pages/PageService.h"
#include "Menu/Pages/Modes/Modes.h"
#include "Menu/Pages/Other/PageInfo.h"


static void OnPress_Information()
{
    Menu::SetOpenedPage(PageInfo::self);
}

DEF_BUTTON(bInformation, "����", "����� ��������� ����������", OnPress_Information);


static void OnPress_ResetSettings()
{
    TimeMeasure::Set(TimeMeasure::_1ms);
    NumberPeriods::Set(NumberPeriods::_1);
    PeriodTimeLabels::Set(PeriodTimeLabels::T_8);

    Channel::A->mod.typeMeasure.value = TypeMeasure::Frequency;
    Channel::A->mod.modeFrequency.value = ModeFrequency::Frequency;
    
    if(FreqMeter::modeTest.IsEnabled())
    {
        FreqMeter::modeTest.Switch();
    }
    LevelSynch::Set(0);
    
    Channel::SetCurrent(Channel::A);

    Menu::SetOpenedPage(Channel::A->pageModes);
    
    Channel::Current()->OnChanged_TypeMeasure(); //-V760

    Channel::Current()->LoadToFPGA();

    Channel::Current()->OnChanged_TypeMeasure();

    Channel::Current()->LoadToFPGA();
    
    LevelSynch::Set(0);
    
    FreqMeter::HardwareReset();
}

DEF_BUTTON(bResetSettings, "�����", "����� �������� � ��������� �� ���������", OnPress_ResetSettings);


static void OnPress_Language()
{
    glob_set.language = LANG_IS_RU ? Language::EN : Language::RU;
}

DEF_BUTTON(bLanguage, "����", "����� ����� ����������", OnPress_Language);


static void OnPress_ShowStatistics()
{
    glob_set.showStatistics = !glob_set.showStatistics;
}

DEF_BUTTON(bShowStatistics, "����������", "���������� ��������� ����������", OnPress_ShowStatistics);


static void OnPress_StyleGUI()
{
    glob_set.styleGUI.Switch();
}


DEF_BUTTON(bStyleGUI, "���������", "����� ���������� ������������", OnPress_StyleGUI);


static Item *items[7] =
{
    &bInformation,
    &bResetSettings,
    &bLanguage,
    nullptr,    // &bStyleGUI,
    nullptr,    // &bShowStatistics,
    nullptr,
    nullptr
};

void PageService::UseReset()
{
    OnPress_ResetSettings();
}

static Page pageService(items, nullptr);

Page *PageService::self = &pageService;
