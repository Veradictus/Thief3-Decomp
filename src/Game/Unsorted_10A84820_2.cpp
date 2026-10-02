// Game/Unsorted_10A84820_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A174E0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3(int Name);
};

Class_10A174E0* FUN_10a18230();

class Class_10E5D498
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual bool FUN_10a84b50();

    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10A84B50 ?FUN_10a84b50@Class_10E5D498@@UAE_NXZ
bool Class_10E5D498::FUN_10a84b50()
{
    Class_10A174E0* Object = FUN_10a18230();
    int Name = Unknown04;
    int Expected = Unknown08;
    return Object->Virtual3(Name) == Expected;
}
