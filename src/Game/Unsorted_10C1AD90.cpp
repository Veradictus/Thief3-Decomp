// Game/Unsorted_10C1AD90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E98F90
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual bool FUN_10c1ad90(int A);

    int Unknown04;
    char Unknown08[0x40];
    int Unknown48;
};

// FUNCTION: 0x10C1AD90 ?FUN_10c1ad90@Class_10E98F90@@UAE_NH@Z
bool Class_10E98F90::FUN_10c1ad90(int A)
{
    if (A == Unknown48)
        return true;
    return Unknown04 == A;
}
