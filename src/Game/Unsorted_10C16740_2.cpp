// Game/Unsorted_10C16740_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

float appFrand();

class Class_10C16740
{
public:
    void FUN_10c16740(float Value);
    void FUN_10c16770(float Value);

    char Unknown00[0x34];
    float Unknown34;
    float Unknown38;
    float Unknown3C;
    float Unknown40;
};

// FUNCTION: 0x10C16740 ?FUN_10c16740@Class_10C16740@@QAEXM@Z
void Class_10C16740::FUN_10c16740(float Value)
{
    if (Unknown34 != Value)
    {
        float Random = appFrand() * Value;
        Unknown34 = Value;
        Unknown38 = Random;
    }
}

// FUNCTION: 0x10C16770 ?FUN_10c16770@Class_10C16740@@QAEXM@Z
void Class_10C16740::FUN_10c16770(float Value)
{
    if (Unknown40 != Value)
    {
        float Random = appFrand() * Value;
        Unknown40 = Value;
        Unknown3C = Random;
    }
}
