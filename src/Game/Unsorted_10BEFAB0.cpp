// Game/Unsorted_10BEFAB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BF02A0
{
public:
    float FUN_10bf02a0();

    char Unknown00[0x154];
    float* Unknown154;
};

float appFrand();

class Class_10BBDB40
{
public:
    float FUN_10bbdc80();
};

class Class_10DBD510
{
public:
    Class_10BBDB40* FUN_10dbd510(int Id);
};

struct Struct_10BEFAB0
{
    char Unknown00[8];
    Class_10DBD510* Unknown08;
};

class Class_10BEFAB0
{
public:
    float FUN_10befab0();

    char Unknown00[4];
    Struct_10BEFAB0* Unknown04;
};

// FUNCTION: 0x10BEFAB0 ?FUN_10befab0@Class_10BEFAB0@@QAEMXZ
float Class_10BEFAB0::FUN_10befab0()
{
    float Min = Unknown04->Unknown08->FUN_10dbd510(0x1007e9)->FUN_10bbdc80();
    float Max = Unknown04->Unknown08->FUN_10dbd510(0x1007ea)->FUN_10bbdc80();
    return Min + (Max - Min) * appFrand();
}

// FUNCTION: 0x10BF02A0 ?FUN_10bf02a0@Class_10BF02A0@@QAEMXZ
float Class_10BF02A0::FUN_10bf02a0()
{
    float Sum = 0.0f;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 10; j++)
            Sum += Unknown154[i * 10 + j];
    }
    return Sum;
}
