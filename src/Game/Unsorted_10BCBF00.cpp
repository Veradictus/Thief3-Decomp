// Game/Unsorted_10BCBF00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA82D0
{
public:
    int FUN_10aa82d0();
};

class Class_10BF7F90 : public Class_10AA82D0
{
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    Class_10BF7F90* FUN_10bc4160();
};

class Class_10E95288 : public Class_10BC4160
{
public:
    void FUN_10be02e0();
};

float FUN_10c00490();

class Class_10E92730 : public Class_10E95288
{
public:
    virtual void Virtual1();
    virtual void FUN_10bcbf00();

    char Unknown04[0x60];
    float Unknown64;
};

// FUNCTION: 0x10BCBF00 ?FUN_10bcbf00@Class_10E92730@@UAEXXZ
void Class_10E92730::FUN_10bcbf00()
{
    if (FUN_10bc4160()->FUN_10aa82d0() == 0)
    {
        double Remaining = Unknown64;
        Unknown64 = Remaining - FUN_10c00490();
        if (Unknown64 < 0.0f)
            FUN_10be02e0();
    }
}
