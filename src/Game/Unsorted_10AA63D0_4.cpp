// Game/Unsorted_10AA63D0_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA66B0_Unknown10
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual int Virtual6(int B);
};

class Class_10E6D8F0
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
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual int FUN_10aa6680(int Index, int B);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[4];
    Class_10AA66B0_Unknown10** Unknown10;
};

// FUNCTION: 0x10AA6680 ?FUN_10aa6680@Class_10E6D8F0@@UAEHHH@Z
int Class_10E6D8F0::FUN_10aa6680(int Index, int B)
{
    if (Index < Unknown08)
    {
        Class_10AA66B0_Unknown10* Item = Unknown10[Index];
        if (Item)
            return Item->Virtual6(B);
    }
    return 0;
}
