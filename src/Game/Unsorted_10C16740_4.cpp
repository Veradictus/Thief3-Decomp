// Game/Unsorted_10C16740_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

float appFrand();

class Class_10C16740
{
public:
    void FUN_10c16740(float Value);
    void FUN_10c16770(float Value);
    void FUN_10c16800(float Value);

    char Unknown00[0x34];
    float Unknown34;
    float Unknown38;
    float Unknown3C;
    float Unknown40;
    char Unknown44[0x10];
    float Unknown54;
    float Unknown58;
};

// FUNCTION: 0x10C16800 ?FUN_10c16800@Class_10C16740@@QAEXM@Z
void Class_10C16740::FUN_10c16800(float Value)
{
    if (Unknown58 != Value)
    {
        float Random = appFrand() * Value;
        Unknown58 = Value;
        Unknown54 = Random;
    }
}
