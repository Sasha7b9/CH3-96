// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings.h"
#include "Hardware/FPGA.h"
#include "Menu/Pages/Channels/Channels.h"
#include "Utils/Math.h"


Settings glob_set =
{
    0,                              // size
    {
        MAKE_COLOR(0,   0,   0),    // BLACK
        MAKE_COLOR(255, 255, 255),  // WHITE
        MAKE_COLOR(0,   255, 255),  // YELLOW
        MAKE_COLOR(0,   0,   255),  // BLUE
        MAKE_COLOR(255, 0,   0),    // RED
        MAKE_COLOR(0,   255, 0),    // GREEN
        MAKE_COLOR(25,  25,  25),   // GRAY_10
        MAKE_COLOR(127, 127, 127),  // GRAY_50
        MAKE_COLOR(51,  51,  51),   // GRAY_20
        MAKE_COLOR(0,   127, 0),    // GREEN_50
        MAKE_COLOR(0,   64,  0),    // GREEN_25
        MAKE_COLOR(0,   25,  0),    // GREEN_10
        MAKE_COLOR(0,   51,  0),    // GREEN_20
        MAKE_COLOR(0,   13,  0),    // GREEN_5
        MAKE_COLOR(0,   38,  0),    // GREEN_15
        MAKE_COLOR(0,   31,  0),    // GREEN_12
        MAKE_COLOR(191, 191, 191),  // GRAY_75
        MAKE_COLOR(0,   25,  0),    // BACKGROUND_1
        MAKE_COLOR(0,   64,  0),    // BACKGROUND_2
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(0,   0,   0),
        MAKE_COLOR(255, 0,   0),    // TYPE_RED
        MAKE_COLOR(0,   255, 0),    // TYPE_GREEN
        MAKE_COLOR(0,   0,   255)   // TYPE_BLUE
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
