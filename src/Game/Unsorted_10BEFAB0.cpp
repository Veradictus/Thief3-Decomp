// Game/Unsorted_10BEFAB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BF02A0
{
public:
    float FUN_10bf02a0();

    char Unknown00[0x154];
    float* Unknown154;
};

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
