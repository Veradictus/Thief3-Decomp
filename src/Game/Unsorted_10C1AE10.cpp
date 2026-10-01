// Game/Unsorted_10C1AE10.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C1AE50
{
    char Unknown00[0x30];
    int Unknown30;
};

class Class_10E98D50
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
    virtual bool FUN_10c1ae50(int A);

    int Unknown04;
    char Unknown08[0x40];
    Struct_10C1AE50* Unknown48;
};

// FUNCTION: 0x10C1AE50 ?FUN_10c1ae50@Class_10E98D50@@UAE_NH@Z
bool Class_10E98D50::FUN_10c1ae50(int A)
{
    if (Unknown48 && Unknown48->Unknown30 == A)
        return true;
    return Unknown04 == A;
}
