// Game/Unsorted_10A80BA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C1F0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual int FUN_10a80c10();
    virtual void Virtual7();
    virtual int Virtual8();
    virtual int FUN_10a80c40();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual int Virtual22();
};

// FUNCTION: 0x10A80C10 ?FUN_10a80c10@Class_10E6C1F0@@UAEHXZ
int Class_10E6C1F0::FUN_10a80c10()
{
    if ((Virtual22() & 2) && Virtual8())
        return 0;
    return 1;
}

// FUNCTION: 0x10A80C40 ?FUN_10a80c40@Class_10E6C1F0@@UAEHXZ
int Class_10E6C1F0::FUN_10a80c40()
{
    if (!(Virtual22() & 4) && !(Virtual22() & 1))
        return 1;
    return 0;
}
