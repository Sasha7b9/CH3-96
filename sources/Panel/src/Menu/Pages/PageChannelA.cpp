#include "defines.h"
#include "PageChannelA.h"
#include "Menu/MenuItems.h"
#include "Display/Primitives.h"
#include "Display/Text.h"
#include "Menu/MenuItemsDef.h"
#include "Menu/Pages/PageModesA.h"
#include "Settings.h"
#include "FreqMeter/FreqMeter.h"
#include <cstring>

using namespace Display::Primitives;
using namespace Display;

extern Switch sSync;
extern Item *items[7];

InputCouple     PageChannelA::couple(InputCouple::AC);
InputImpedance  PageChannelA::impedance(InputImpedance::_1MOmh);
ModeFilter      PageChannelA::modeFilter(ModeFilter::Off);
ModeFront       PageChannelA::modeFront(ModeFront::Front);
Divider         PageChannelA::divider(Divider::_1);
TypeSynch       PageChannelA::typeSynch(TypeSynch::Manual);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Couple()
{
    InputCouple::Load();
}

/// ����� ���������(���������) ����� �������� ������
DEF_SWITCH_UGO_2(sCouple,
    "\x7C \x7D", "����",
    "�������� ����", "�������� ����",
    "\x7C", "\x7D",
    PageChannelA::couple, OnPress_Couple
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Impedance()
{
    FreqMeter::LoadImpedance();
}

/// ��������� �������� ������������� �������� ������
DEF_SWITCH_UGO_2(sImpedance,
    "R��", "������� ������������� ������",
    "1 ���", "50 ��",
    "1���", "50��",
    PageChannelA::impedance, OnPress_Impedance
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Filter()
{
    ModeFilter::Load();
}

/// ���������(����������) ���
DEF_SWITCH_UGO_2(sLowpassFilter,
    "���", "���������/���������� ������� ��",
    "����.", "���.",
    "���", "",
    PageChannelA::modeFilter, OnPress_Filter
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Front()
{
    FreqMeter::LoadModeFront();
}

/// ����� ������ ������������� �������� ������
DEF_SWITCH_UGO_2(sFront,
    "\x8D \x8E", "����� ���� �������������",
    "�����", "����",
    "\x8D", "\x8E",
    PageChannelA::modeFront, OnPress_Front
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Divider()
{
    FreqMeter::LoadDivider();
}

/// ���������(����������) �������� �������� ����������
DEF_SWITCH_UGO_2(sDivider,
    "\x7E\x7F\x7E \x7E\x7F\x8F", "���/���� �������� ��������",
    "1:1", "1:10",
    "", "1:10",
    PageChannelA::divider, OnPress_Divider
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_TimeLabels()
{
    switch (PageModes::periodTimeLabels.value)
    {
        case PeriodTimeLabels::T_3:
            PageModesB::periodTimeLabelsB.value = PeriodTimeLabelsB::T_3;
            PageModesC::periodTimeLabelsC.value = PeriodTimeLabelsC::T_3;
            break;
        case PeriodTimeLabels::T_4:
            PageModesB::periodTimeLabelsB.value = PeriodTimeLabelsB::T_4;
            PageModesC::periodTimeLabelsC.value = PeriodTimeLabelsC::T_4;
            break;
        case PeriodTimeLabels::T_5:
            PageModesB::periodTimeLabelsB.value = PeriodTimeLabelsB::T_5;
            PageModesC::periodTimeLabelsC.value = PeriodTimeLabelsC::T_5;
            break;
        case PeriodTimeLabels::T_6:
            PageModesB::periodTimeLabelsB.value = PeriodTimeLabelsB::T_6;
            PageModesC::periodTimeLabelsC.value = PeriodTimeLabelsC::T_6;
            break;
        case PeriodTimeLabels::T_7:
            PageModesB::periodTimeLabelsB.value = PeriodTimeLabelsB::T_7;
            PageModesC::periodTimeLabelsC.value = PeriodTimeLabelsC::T_7;
            break;
        case PeriodTimeLabels::T_8:
            PageModesB::periodTimeLabelsB.value = PeriodTimeLabelsB::T_8;
            PageModesC::periodTimeLabelsC.value = PeriodTimeLabelsC::T_8;
            break;
    }
    FreqMeter::LoadPeriodTimeLabels();
}

/// ����� ������� ����� �������
DEF_SWITCH_6(sPeriodTimeLabels,
    "�����", "������������ ��������� �����",
    "10-3", "10-4", "10-5", "10-6", "10-7", "10-8",
    PageModes::periodTimeLabels,  OnPress_TimeLabels
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_TimeMeasure()
{
    switch (PageModes::timeMeasure.value)
    {
        case TimeMeasure::_1ms:
            PageModesB::timeMeasureB.value = TimeMeasureB::_1ms;
            PageModesC::timeMeasureC.value = TimeMeasureC::_1ms;
            PageModesD::timeMeasureD.value = TimeMeasureD::_1ms;
            PageModesB::numberPeriods.value = NumberPeriods::_1;
            PageModesC::numberPeriods.value = NumberPeriods::_1;
            PageModes::numberPeriods.value = NumberPeriods::_1;
            break;
        case TimeMeasure::_10ms:
            PageModesB::timeMeasureB.value = TimeMeasureB::_10ms;
            PageModesC::timeMeasureC.value = TimeMeasureC::_10ms;
            PageModesD::timeMeasureD.value = TimeMeasureD::_10ms;
            PageModesB::numberPeriods.value = NumberPeriods::_10;
            PageModesC::numberPeriods.value = NumberPeriods::_10;
            PageModes::numberPeriods.value = NumberPeriods::_10;
            break;
        case TimeMeasure::_100ms:
            PageModesB::timeMeasureB.value = TimeMeasureB::_100ms;
            PageModesC::timeMeasureC.value = TimeMeasureC::_100ms;
            PageModesD::timeMeasureD.value = TimeMeasureD::_100ms;
            PageModesB::numberPeriods.value = NumberPeriods::_100;
            PageModesC::numberPeriods.value = NumberPeriods::_100;
            PageModes::numberPeriods.value = NumberPeriods::_100;
            break;
        case TimeMeasure::_1s:
            PageModesB::timeMeasureB.value = TimeMeasureB::_1s;
            PageModesC::timeMeasureC.value = TimeMeasureC::_1s;
            PageModesD::timeMeasureD.value = TimeMeasureD::_1s;
            PageModesB::numberPeriods.value = NumberPeriods::_1K;
            PageModesC::numberPeriods.value = NumberPeriods::_1K;
            PageModes::numberPeriods.value = NumberPeriods::_1K;
            break;
        case TimeMeasure::_10s:
            PageModesB::timeMeasureB.value = TimeMeasureB::_10s;
            PageModesC::timeMeasureC.value = TimeMeasureC::_10s;
            PageModesD::timeMeasureD.value = TimeMeasureD::_10s;
            PageModesB::numberPeriods.value = NumberPeriods::_10K;
            PageModesC::numberPeriods.value = NumberPeriods::_10K;
            PageModes::numberPeriods.value = NumberPeriods::_10K;
            break;
        case TimeMeasure::_100s:
            PageModesB::timeMeasureB.value = TimeMeasureB::_100s;
            PageModesC::timeMeasureC.value = TimeMeasureC::_100s;
            PageModesD::timeMeasureD.value = TimeMeasureD::_100s;
            PageModes::numberPeriods.value = NumberPeriods::_100K;
            PageModesB::numberPeriods.value = NumberPeriods::_100K;
            PageModesC::numberPeriods.value = NumberPeriods::_100K;
            break;
        case TimeMeasure::_1000s:
            PageModesB::timeMeasureB.value = TimeMeasureB::_1000s;
            PageModesC::timeMeasureC.value = TimeMeasureC::_1000s;
            PageModesD::timeMeasureD.value = TimeMeasureD::_1000s;
            PageModes::numberPeriods.value = NumberPeriods::_1000K;
            PageModesB::numberPeriods.value = NumberPeriods::_1000K;
            PageModesC::numberPeriods.value = NumberPeriods::_1000K;
            break;
    }
    FreqMeter::LoadTimeMeasure();
}

/// ����� ������� ���������
DEF_SWITCH_7(sTimeMeasure,
    "�����", "����� �����",
    "1ms", "10ms", "100ms", "1s", "10s", "100s", "1000s",
    PageModes::timeMeasure, OnPress_TimeMeasure
);

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
static void OnPress_Sync()
{
    if (PageChannelA::typeSynch == TypeSynch::Holdoff)
    {
        items[0] = &sSync;
        items[1] = &sTimeMeasure;
        items[2] = &sPeriodTimeLabels;
        items[3] = nullptr;
        items[4] = nullptr;
        items[5] = nullptr;
    }
    else
    {
        items[0] = &sCouple;
        items[1] = &sImpedance;
        items[2] = &sLowpassFilter;
        items[3] = &sFront;
        items[4] = &sDivider;
        items[5] = &sSync;
        
    }
    TYPE_SYNCH_A = (TypeSynch::E)PageChannelA::typeSynch.value;
    FreqMeter::LoadTypeSynch();
}

/// ����� ������ ������������� ���, ���
DEF_SWITCH_UGO_2(sSync,
    "�����", "����� ������ ������������",
    "����", "Holdoff",
    "����", "Holdoff",
    PageChannelA::typeSynch, OnPress_Sync
);

static Item *items[7] =
{
    &sCouple,
    &sImpedance,
    &sLowpassFilter,
    &sFront,
    &sDivider,
    &sSync,
    nullptr
};

static Page pageChannelA(items);

Page *PageChannelA::self = &pageChannelA;

Switch *PageChannelA::switchTypeSynch = &sSync;

void PageChannelA::FixPress()
{
    OnPress_Sync();
}
