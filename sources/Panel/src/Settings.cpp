#include "defines.h"
#include "Settings.h"
#include "Hardware/FPGA.h"
#include "Menu/Pages/Settings/PagesSettings.h"
#include "Utils/Math.h"


Settings set =
{
    Channel::A,                                 // currentChannel
    {
        {0, 1}, {0, 1}                          // levelSynch
    },
    { 
        TypeSynch::Manual, TypeSynch::Manual    // typeSynch
    },
    false
};


#define DEFINE_ARGUMENT char argument[6] = {0, 0, 0, 0, 0, 0}


const ModeFront ModeFront::empty(ModeFront::Count);


void InputCouple::Load()
{
    char command[4] = { 0, 0, 1, 1 };

    DEFINE_ARGUMENT;

    if(Current().IsDC())
    {
        argument[5] = 1;
    }

    FPGA::WriteCommand(command, argument);
}


InputCouple &InputCouple::Current()
{
    if(CURRENT_CHANNEL_IS_A)
    {
        return PageSettingsA::couple;
    }
    else if(CURRENT_CHANNEL_IS_B)
    {
        return PageSettingsB::couple;
    }
    
    static InputCouple couple(InputCouple::AC);
    
    return couple;
}


void InputCouple::Set(InputCouple::E v)
{
    if(CURRENT_CHANNEL_IS_A)
    {
        PageSettingsA::couple.value = (uint8)v;
        Load();
    }
    else if(CURRENT_CHANNEL_IS_B)
    {
        PageSettingsB::couple.value = (uint8)v;
        Load();
    }
}


const ModeFilter &ModeFilter::Current()
{
    static const ModeFilter mode(ModeFilter::Count);

    static const ModeFilter *modes[Channel::Count] = { &PageSettingsA::modeFilter, &PageSettingsB::modeFilter, &mode, &mode };

    return *modes[CURRENT_CHANNEL];
}


void ModeFilter::Set(ModeFilter::E v)
{
    static ModeFilter mode(ModeFilter::Count);

    static ModeFilter *modes[Channel::Count] = { &PageSettingsA::modeFilter, &PageSettingsB::modeFilter, &mode, &mode };

    modes[CURRENT_CHANNEL]->value = (uint8)v;

    LoadToFPGA();
}


void LevelSynch::Change(int delta)
{
    if (CURRENT_CHANNEL_IS_A_OR_B)
    {
        int prev = LEVEL_SYNCH(CURRENT_CHANNEL);

        LEVEL_SYNCH(CURRENT_CHANNEL) += delta;

        int MIN = -800;
        int MAX = 800;

        if (TypeSynch::Current().IsHoldoff())
        {
            MIN = 1;
        }

        LIMITATION(LEVEL_SYNCH(CURRENT_CHANNEL), MIN, MAX);

        if (prev != LEVEL_SYNCH(CURRENT_CHANNEL))
        {
            if (delta < 0) { FPGA::DecreaseN(); }
            else           { FPGA::IncreaseN(); }

            FPGA::WriteDataGovernor();
        }
    }
}


const ModeFront &ModeFront::Current()
{
    static const ModeFront *modes[Channel::Count] = { &PageSettingsA::modeFront, &PageSettingsB::modeFront, &empty, &empty };

    return *modes[CURRENT_CHANNEL];
}


void ModeFront::LoadToFPGA()
{
    char command[4] = { 0, 1, 0, 0 };

    DEFINE_ARGUMENT;

    if (!Current().IsFront())
    {
        argument[5] = 1;
    }

    FPGA::WriteCommand(command, argument);
}
