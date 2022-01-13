// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings.h"
#include "Hardware/FPGA.h"
#include "Menu/Pages/Channels/Channels.h"
#include "Utils/Math.h"
#include "Display/Colors.h"
#include <string.h>


static Settings def_set =
{
    0,                                  // size
    {
        Color::Make(255, 255, 255),     // WHITE            0

        Color::Make(0,   0,   0),       // BACK             1
        Color::Make(255, 255, 255),     // FILL             2

        Color::Make(0,   25,  0),       // BACK_1           3
        Color::Make(0,   64,  0),       // BACK_2           4
        Color::Make(0,   51,  0),       // BACK_3           5

        Color::Make(25,  25,  25),      // BACK_UNSELECT    6
        Color::Make(191, 191, 191),     // BACK_SELECT      7

        Color::Make(127, 127, 127),     // BACK_STAT        8
        Color::Make(51,  51,  51),      // BACK_VALUE       9

        Color::Make(255, 0,   0),       // TYPE_RED         10
        Color::Make(0,   255, 0),       // TYPE_GREEN       11
        Color::Make(0,   0,   255)      // TYPE_BLUE        12
    },
    {
        {0, 1}, {0, 1}                          // levelSynch
    },
    { 
        TypeSynch::Manual, TypeSynch::Manual    // typeSynch
    },
    false,
    StyleGUI(StyleGUI::Modern),
    Language::RU
};


Settings glob_set = def_set;


void InputCouple::LoadToFPGA()
{
    if (CURRENT_CHANNEL_IS_A_OR_B)
    {
        Command command(Command::Couple);

        if (Channel::Current()->set.couple.IsDC())
        {
            command.SetBit(9);
        }

        FPGA::WriteCommand(command);
    }
}


void LevelSynch::Change(int delta)
{
    if (CURRENT_CHANNEL_IS_A_OR_B)
    {
        int prev = LEVEL_SYNCH(Channel::Current());

        LEVEL_SYNCH(CURRENT_CHANNEL) += delta;

        int MIN = -800;
        int MAX = 800;

        if (Channel::Current()->set.typeSynch.IsHoldoff())
        {
            MIN = 1;
        }

        LIMITATION(LEVEL_SYNCH(CURRENT_CHANNEL), MIN, MAX); //-V2516

        if (prev != LEVEL_SYNCH(CURRENT_CHANNEL))
        {
            if (delta < 0) { FPGA::GovernorData::DecreaseN(); }
            else           { FPGA::GovernorData::IncreaseN(); }

            FPGA::GovernorData::Write();
        }
    }
}

void LevelSynch::Set(int num)
{
    if (CURRENT_CHANNEL_IS_A_OR_B)
    {
        int prev = LEVEL_SYNCH(Channel::Current());

        LEVEL_SYNCH(CURRENT_CHANNEL) = num;

        int MIN = -800;
        int MAX = 800;

        if (Channel::Current()->set.typeSynch.IsHoldoff())
        {
            MIN = 1;
        }

        LIMITATION(LEVEL_SYNCH(CURRENT_CHANNEL), MIN, MAX); //-V2516

        if (prev != LEVEL_SYNCH(CURRENT_CHANNEL))
        {
            FPGA::GovernorData::SetN(num);
            FPGA::GovernorData::Write();
        }
    }
}


void ModeFront::LoadToFPGA()
{
    if (CURRENT_CHANNEL_IS_A_OR_B)
    {
        Command command(Command::ModeFront);

        if (!Channel::Current()->set.modeFront.IsFront())
        {
            command.SetBit(9);
        }

        FPGA::WriteCommand(command);
    }
}


void TypeSynch::LoadToFPGA()
{
    if (CURRENT_CHANNEL_IS_A_OR_B)
    {
        Command command(Command::TypeSynch);

        if (Channel::Current()->set.typeSynch.IsHoldoff())
        {
            command.SetBit(9);
        }

        FPGA::WriteCommand(command);
    }
}


void ModeFilter::LoadToFPGA()
{
    if (CURRENT_CHANNEL_IS_A_OR_B)
    {
        Command command(Command::ModeFilter);

        if (Channel::Current()->set.modeFilter.IsOff())
        {
            command.SetBit(9);
        }

        FPGA::WriteCommand(command);
    }
}


void Divider::LoadToFPGA()
{
    if (CURRENT_CHANNEL_IS_A_OR_B)
    {
        Command command(Command::Divider);

        if (!Channel::Current()->set.divider.Is1())
        {
            command.SetBit(9);
        }

        FPGA::WriteCommand(command);
    }
}


void Settings::Load()
{
    HAL_EEPROM::LoadSettings(this);
}


void Settings::Save()
{
    HAL_EEPROM::SaveSettings(this);
}


void Settings::LoadDefaultColors()
{
    memcpy(&glob_set.colors[0], &def_set.colors, sizeof(uint) * Color::COUNT);
}
