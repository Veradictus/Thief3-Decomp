// Game/Unsorted_10956840.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_1092bdb0(void* Memory);

class Class_10956F20
{
public:
    void FUN_10956f20(int Index);

    char Unknown00[0x29C];
    void* Unknown29C[1];
};

class Class_10956DB0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(int);

    void FUN_10956db0();

    char Unknown04[0x290];
    char Unknown294;
    int Unknown298;
    int Unknown29C[9];
};

// FUNCTION: 0x10956DB0 ?FUN_10956db0@Class_10956DB0@@QAEXXZ
void Class_10956DB0::FUN_10956db0()
{
    for (int i = 0; i < 9; i++)
        Unknown29C[i] = 0;
    Unknown298 = 0;
    Virtual5(0);
    Unknown294 = 0;
}

// FUNCTION: 0x10956F20 ?FUN_10956f20@Class_10956F20@@QAEXH@Z
void Class_10956F20::FUN_10956f20(int Index)
{
    if (Unknown29C[Index])
    {
        FUN_1092bdb0(Unknown29C[Index]);
        Unknown29C[Index] = 0;
    }
}
