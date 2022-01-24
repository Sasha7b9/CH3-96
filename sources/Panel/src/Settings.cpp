// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Settings.h"
#include "Hardware/FPGA.h"
#include "Menu/Pages/Channels/Channels.h"
#include "Utils/Math.h"
#include "Display/Colors.h"


static ColorScheme def_colors[3] =
{
    {
        Color::Make(248, 248, 248),     // WHITE            0

        Color::Make(0,   0,   0),       // BACK             1
        Color::Make(248, 248, 248),     // FILL             2

        Color::Make(0,   24,  0),       // BACK_1           3
        Color::Make(0,   64,  0),       // BACK_2           4
        Color::Make(0,   56,  0),       // BACK_3           5

        Color::Make(24,  24,  24),      // BACK_UNSELECT    6
        Color::Make(192, 192, 192),     // BACK_SELECT      7

        Color::Make(128, 128, 128),     // BACK_STAT        8

        Color::Make(248, 0,   0),       // TYPE_RED         9
        Color::Make(0,   248, 0),       // TYPE_GREEN       10
        Color::Make(0,   0,   248)      // TYPE_BLUE        11
    },
    {
        Color::Make(248, 248, 248),     // WHITE            0

        Color::Make(112, 8,   8),       // BACK             1
        Color::Make(248, 248, 248),     // FILL             2

        Color::Make(0,   0,   248),     // BACK_1           3
        Color::Make(0,   0,   0),       // BACK_2           4
        Color::Make(0,   0,   160),     // BACK_3           5

        Color::Make(248, 24,  0),       // BACK_UNSELECT    6
        Color::Make(192, 192, 192),     // BACK_SELECT      7

        Color::Make(128, 128, 128),     // BACK_STAT        8

        Color::Make(248, 0,   0),       // TYPE_RED         9
        Color::Make(0,   248, 0),       // TYPE_GREEN       10
        Color::Make(0,   0,   248)      // TYPE_BLUE        11
    },
    {
        Color::Make(248, 248, 248),     // WHITE            0

        Color::Make(0,   0,   0),       // BACK             1
        Color::Make(248, 248, 248),     // FILL             2

        Color::Make(0,   24,  0),       // BACK_1           3
        Color::Make(0,   64,  0),       // BACK_2           4
        Color::Make(0,   48,  0),       // BACK_3           5

        Color::Make(24,  24,  24),      // BACK_UNSELECT    6
        Color::Make(192, 192, 192),     // BACK_SELECT      7

        Color::Make(128, 128, 128),     // BACK_STAT        8

        Color::Make(248, 0,   0),       // TYPE_RED         9
        Color::Make(0,   248, 0),       // TYPE_GREEN       10
        Color::Make(0,   0,   248)      // TYPE_BLUE        11
    }
};


static Settings def_set =
{
    0,                                  // size
    {
        def_colors[0], def_colors[1], def_colors[2]
    },
    {
        {0, 1}, {0, 1}                          // levelSynch
    },
    {
        TypeSynch::Manual, TypeSynch::Manual    // typeSynch
    },
    false,
    StyleGUI(StyleGUI::Modern),
    Language::RU,
    0                                           // colorScheme
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

        LIMITATION(LEVEL_SYNCH(CURRENT_CHANNEL), MIN, MAX);

        if (prev != LEVEL_SYNCH(CURRENT_CHANNEL))
        {
            if (delta < 0) { FPGA::GovernorData::DecreaseN(); }
            else { FPGA::GovernorData::IncreaseN(); }

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

        LIMITATION(LEVEL_SYNCH(CURRENT_CHANNEL), MIN, MAX);

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


void Settings::LoadDefaultColorScheme()
{
    glob_set.schemes[glob_set.colorScheme] = def_colors[glob_set.colorScheme];
}
