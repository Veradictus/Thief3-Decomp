// Game/Unsorted_10ACA550.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10ACA600
{
public:
    int FUN_10aca600();

    char Unknown00[8];
    float Unknown08;
};

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10ACA620
{
public:
    void FUN_10aca620();

    char Unknown00[4];
    int Unknown04;
    float Unknown08;
};

// FUNCTION: 0x10ACA600 ?FUN_10aca600@Class_10ACA600@@QAEHXZ
int Class_10ACA600::FUN_10aca600()
{
    if (Unknown08 > DAT_10eafbdc)
        return 1;
    return 0;
}

// FUNCTION: 0x10ACA620 ?FUN_10aca620@Class_10ACA620@@QAEXXZ
void Class_10ACA620::FUN_10aca620()
{
    if (Unknown08 > DAT_10eafbdc)
    {
        Unknown08 = 0.0f;
        DAT_10f46da0->Virtual5(0xb, Unknown04, -1, 0);
    }
}
