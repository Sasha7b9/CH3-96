// (c) Aleksandr Shevchenko e-mail : Sasha7b9@tut.by
#include "defines.h"
#include "Tests.h"
#include "Utils/ValueSTRICT.h"
#include <cstdlib>


#define NUM_CYCLES  1000


namespace Tests
{
    static void AllTests(const ValueSTRICT &value);

    static void TestEqualSub(const ValueSTRICT &value);
    static void TestSub(const ValueSTRICT &value1, const ValueSTRICT &value2);
}


void Tests::ValuesSTRICT()
{
    for (int i = 0; i < NUM_CYCLES; i++)
    {
        AllTests(ValueSTRICT(Utils::RandDouble()));

        TestSub(ValueSTRICT(Utils::RandDouble()), ValueSTRICT(Utils::RandDouble()));
    }
}


void Tests::AllTests(const ValueSTRICT &value)
{
    TestEqualSub(value);
}


static void Tests::TestEqualSub(const ValueSTRICT &value)
{
    ValueSTRICT one = value;
    ValueSTRICT two = value;


    ValueSTRICT result(0);

    {
        one.SetSign(1);
        two.SetSign(1);

        result = one;
        result.Sub(two);
        if (!result.IsZero())
        {
            FailExit();
        }
    }

    {
        one.SetSign(1);
        two.SetSign(-1);

        result = one;

        result.Sub(two);

        if (result != one * 2)
        {
            FailExit();
        }
    }

    {
        one.SetSign(-1);
        two.SetSign(1);

        result = one;
        result.Sub(two);

        if (result != one * 2)
        {
            FailExit();
        }
    }

    {
        one.SetSign(-1);
        two.SetSign(-1);

        result = one;
        result.Sub(two);

        if (!result.IsZero())
        {
            FailExit();
        }
    }
}


static void Tests::TestSub(const ValueSTRICT &value1, const ValueSTRICT &value2)
{
    ValueSTRICT one = value1;

    one.Sub(value2);

    double result1 = value1.ToDouble() - value2.ToDouble();
    double result2 = one.ToDouble();

    if (!Utils::EqualsDouble(result1, result2))
    {
        FailExit();
    }
}
