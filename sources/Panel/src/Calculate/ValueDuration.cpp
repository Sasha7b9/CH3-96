// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Log.h"
#include "Calculate/ValueFPGA.h"
#include "Menu/Pages/Modes/Modes.h"
#include "Utils/Math.h"
#include "Utils/StringUtils.h"
#include <cstdio>


ValueDuration::ValueDuration() : ValueFPGA()
{
    mainUnits.Set("s");
}


ValueDuration_Ndt_1ns::ValueDuration_Ndt_1ns(uint timer, uint cal1, uint cal2) : ValueDuration()
{
    if (cal1 == cal2)
    {
        SetInfiniteValue();
        return;
    }

    float v = (float)(100 * timer) / (float)(cal2 - cal1);

    SetValue("%.1f ns", v);
}


ValueDuration_Phase_FillFactor::ValueDuration_Phase_FillFactor(uint period, uint duration) : ValueDuration()
{
    if (period == 0)
    {
        SetInfiniteValue();
        return;
    }

    ValueSTRICT val(0);

    if (ModeDuration::Current().IsPhase())
    {
        mainUnits.Set("$");

        val.FromINT64((int64)duration);
        val.Mul(360);
        val.Div(period);

        if (period == duration)
        {
            val.FromINT64(0);
        }
    }
    else
    {
        mainUnits.Set("");

        val.FromINT64((int64)duration);
        val.Div(period);
    }

    SetValue(val, duration, ModeDuration::Current().IsFillFactor());
}


ValueDuration_Ndt_StartStop::ValueDuration_Ndt_StartStop(uint counter) : ValueDuration()
{
    counter /= 2;

    ValueSTRICT val(counter);

    val.Div(PeriodTimeLabels::Current().ToZeros());

    SetValue(val, counter);
}


char *ValueDuration_Phase_FillFactor::GetSuffixUnit(int order) const
{
    return GetSuffixUnitRelated(order);
}
