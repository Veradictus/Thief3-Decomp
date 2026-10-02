// Game/Unsorted_10C16740_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

float appFrand();

class Class_10C16740
{
public:
    void FUN_10c16740(float Value);
    void FUN_10c16770(float Value);
    void FUN_10c167a0(float Value);
    void FUN_10c167d0(float Value);

    char Unknown00[0x34];
    float Unknown34;
    float Unknown38;
    float Unknown3C;
    float Unknown40;
    float Unknown44;
    float Unknown48;
    float Unknown4C;
    float Unknown50;
};

// FUNCTION: 0x10C167A0 ?FUN_10c167a0@Class_10C16740@@QAEXM@Z
void Class_10C16740::FUN_10c167a0(float Value)
{
    if (Unknown44 != Value)
    {
        float Random = appFrand() * Value;
        Unknown44 = Value;
        Unknown48 = Random;
    }
}

// FUNCTION: 0x10C167D0 ?FUN_10c167d0@Class_10C16740@@QAEXM@Z
void Class_10C16740::FUN_10c167d0(float Value)
{
    if (Unknown50 != Value)
    {
        float Random = appFrand() * Value;
        Unknown50 = Value;
        Unknown4C = Random;
    }
}
