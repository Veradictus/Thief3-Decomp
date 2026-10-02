// Game/Unsorted_10BDF3B0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E94578
{
public:
    virtual void Virtual0();

    bool FUN_10bc40e0();
    void FUN_10bc5b50();
};

class Class_10E95170 : public Class_10E94578
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual void FUN_10bdf3f0();

    char Unknown04[0x3C];
    int Unknown40;
};

// FUNCTION: 0x10BDF3F0 ?FUN_10bdf3f0@Class_10E95170@@UAEXXZ
void Class_10E95170::FUN_10bdf3f0()
{
    if (Unknown40 == 3)
    {
        FUN_10bc5b50();
        return;
    }
    if (FUN_10bc40e0())
        FUN_10bc5b50();
}
