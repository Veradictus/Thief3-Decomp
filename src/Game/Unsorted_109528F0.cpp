// Game/Unsorted_109528F0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10955C30
{
public:
    void FUN_10956270();

    char Unknown00[0xC];
    bool Unknown0C;
    char Unknown0D[0x2B];
};

class Class_109528B0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual bool Virtual7(int A);

    void FUN_10953450();

    char Unknown04[0x8C];
    Class_10955C30 Unknown90[9];
};

// FUNCTION: 0x10953450 ?FUN_10953450@Class_109528B0@@QAEXXZ
void Class_109528B0::FUN_10953450()
{
    for (int i = 0; i < 9; i++)
    {
        if (Unknown90[i].Unknown0C && !Virtual7(i))
            Unknown90[i].FUN_10956270();
    }
}
